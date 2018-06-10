//
// Created by Anton Shelepov on 05.06.18.
//

#include "include/huffman_encoder.h"
#include <iostream>

huffman_encoder::huffman_encoder() {
    for (size_t i = 0; i < huffman_tree::ALPHABET_SIZE; i++) {
        frequency[i] = 0;
    }
}

void huffman_encoder::init() {
    std::vector<std::pair<char, int64_t>> chars;
    for (size_t i = 0; i < huffman_tree::ALPHABET_SIZE; i++) {
        if (frequency[i]) {
            chars.push_back({i, frequency[i]});
        }
    }
    tree.build(chars);
}

std::vector<huffman_code> huffman_encoder::encode(char const* chars, size_t len) {
    std::vector<huffman_code> encoded_seq;
    encoded_seq.reserve(len);
    for (size_t i = 0; i < len; i++) {
        encoded_seq.emplace_back(match(chars[i]));
    }
    return encoded_seq;
}

void huffman_encoder::update_frequency(char const* chars, size_t len) {
    for (size_t i = 0; i < len; i++) {
        ++frequency[chars[i]];
    }
}

huffman_tree::encoded_tree huffman_encoder::get_service() {
    return tree.encode();
}

huffman_code huffman_encoder::match(char ch) {
    return tree.match_encode(ch);
}
