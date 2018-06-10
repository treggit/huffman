//
// Created by Anton Shelepov on 05.06.18.
//

#ifndef HUFFMAN_COMPRESS_UTILLS_H
#define HUFFMAN_COMPRESS_UTILLS_H

#include "buffered_reader.h"
#include "buffered_writer.h"

#include "../lib/huffman-lib/include/huffman_encoder.h"
#include "../lib/huffman-lib/include/huffman_decoder.h"
#include "../lib/huffman-lib/include/huffman_code.h"

const size_t BUFFER_SIZE = 4096 * 100;

void encode(std::string const& filename, std::string const& filename_encoded);
void precalc_frequency(buffered_reader& reader, huffman_encoder& encoder);

void put_service(buffered_writer& writer, huffman_encoder& encoder);

void decode(std::string const& filename, std::string const& filename_decoded);
huffman_tree::encoded_tree extract_service(buffered_reader& reader);

#endif //HUFFMAN_COMPRESS_UTILLS_H
