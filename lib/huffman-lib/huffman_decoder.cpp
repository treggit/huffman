//
// Created by Anton Shelepov on 05.06.18.
//

#include "include/huffman_decoder.h"

huffman_decoder::huffman_decoder(huffman_tree::encoded_tree const& encoded) {
    tree.decode(encoded);
    bytes_expected = encoded.bytes_encoded;
    reset_automata();
}

void huffman_decoder::reset_automata() {
    automata_ptr = tree.get_root().get();
}

void huffman_decoder::read_bit(bool dir) {
    if (dir == 0) {
        automata_ptr = automata_ptr->left.get();
    }
    else {
        automata_ptr = automata_ptr->right.get();
    }
}

bool huffman_decoder::matches_any() const {
    if (automata_ptr == nullptr) {
        return 0;
    }
    return automata_ptr->is_leaf();
}

char huffman_decoder::get_decoded_value() const {
    if (automata_ptr == nullptr) {
        return 0;
    }
    return automata_ptr->value;
}

size_t huffman_decoder::get_bytes_expected() const {
    if (automata_ptr == nullptr) {
        return 0;
    }
    return bytes_expected;
}

size_t huffman_decoder::get_depth() const {
    if (automata_ptr == nullptr) {
        return 0;
    }
    return automata_ptr->depth;
}

size_t huffman_decoder::jump(char path, size_t steps) {
    if (automata_ptr == nullptr) {
        return 0;
    }
    size_t before_jump = get_depth();
    huffman_tree::node* next_node = automata_ptr->jump[path][steps];
    if (next_node != nullptr) {
        automata_ptr = next_node;
    }
    return get_depth() - before_jump;
}

