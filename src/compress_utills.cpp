//
// Created by Anton Shelepov on 05.06.18.
//

#include <iostream>
#include "compress_utills.h"
#include "packager.h"


void encode(std::string const& filename, std::string const& filename_encoded) {
    std::cout << "Starting encoding " << filename << "...\n";
    huffman_encoder encoder;
    buffered_reader reader(filename);
    precalc_frequency(reader, encoder);
    reader.reset_unread_bytes();

    encoder.init();
    std::cout << "Tree was built\n";

    buffered_writer writer(filename_encoded, true);
    put_service(writer, encoder);
    char unpacked = 0;
    size_t unpacked_bits = BIT_CAP * sizeof(unpacked);
    char buffer[BUFFER_SIZE];

    std::cout << "Reading from " << filename << "\n";
    while (reader.can_read()) {
        size_t len = reader.read(buffer, BUFFER_SIZE);
        std::vector<huffman_code> encoded_seq = encoder.encode(buffer, len);
        std::vector<char> packed = pack(unpacked, unpacked_bits, encoded_seq, !reader.can_read());
        writer.write(packed.data(), packed.size());
    }
    std::cout << "File " << filename << " encoded successfully, saved to " << filename_encoded << "\n";
}

void precalc_frequency(buffered_reader& reader, huffman_encoder& encoder) {
    char buffer[BUFFER_SIZE];
    while (reader.can_read()) {
        size_t len = reader.read(buffer, BUFFER_SIZE);
        encoder.update_frequency(buffer, len);
    }
}

void put_service(buffered_writer& writer, huffman_encoder& encoder) {
    huffman_tree::encoded_tree service = encoder.get_service();
    writer.put_char(static_cast<char>(service.size >> 8));
    writer.put_char(static_cast<char>(service.size));
    writer.write(service.edges.data(), service.edges.size());
    writer.write(service.leaves_ordered.data(), service.leaves_ordered.size());
    writer.put(service.bytes_encoded);
}

void decode(std::string const& filename, std::string const& filename_decoded) {
    std::cout << "Starting decoding " << filename << "...\n";
    huffman_decoder decoder;
    buffered_reader reader(filename);
    decoder.init(extract_service(reader));
    std::cout << "Tree regenerated\n";
    buffered_writer writer(filename_decoded, true);

    char buffer[BUFFER_SIZE];
    std::cout << "Reading from " << filename << "\n";
    size_t bytes_decoded = 0;
    while (reader.can_read() && bytes_decoded < decoder.get_bytes_expected()) {
        size_t len = reader.read(buffer, BUFFER_SIZE);
        std::vector<char> unpacked = unpack(buffer, len, decoder.get_bytes_expected() - bytes_decoded, decoder);
        bytes_decoded += unpacked.size();
        writer.write(unpacked.data(), unpacked.size());
    }
    if (bytes_decoded != decoder.get_bytes_expected()) {
        throw std::runtime_error("Encoded file was damaged, couldn't decode correctly");
    }
    std::cout << "File " << filename << " decoded successfully, saved to " << filename_decoded << '\n';
}

huffman_tree::encoded_tree extract_service(buffered_reader& reader) {
    huffman_tree::encoded_tree tree;
    tree.size = static_cast<size_t>(reader.get_char());
    tree.size <<= BIT_CAP;
    tree.size |= static_cast<size_t>(reader.get_char());
    tree.edges.resize(calc_tree_size(tree.size));
    tree.leaves_ordered.resize(tree.size);
    reader.read(tree.edges.data(), tree.edges.size());
    reader.read(tree.leaves_ordered.data(), tree.leaves_ordered.size());
    reader.get(tree.bytes_encoded);
    return tree;
}

size_t calc_tree_size(size_t leaves_size) {
    size_t edges_size = 2 * leaves_size / BIT_CAP;
    edges_size += ((2 * leaves_size) % BIT_CAP != 0);
    return edges_size;
}
