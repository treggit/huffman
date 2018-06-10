//
// Created by Anton Shelepov on 05.06.18.
//

#ifndef HUFFMAN_LIB_HUFFMAN_CODE_H
#define HUFFMAN_LIB_HUFFMAN_CODE_H

#include "huffman_tree.h"
#include "frequency.h"

struct huffman_encoder {

    explicit huffman_encoder(frequency& count);
    std::vector<char> encode(char const* chars, size_t len, bool is_last = true);
    huffman_tree::encoded_tree get_service();
    huffman_code match(char ch);

private:
    huffman_tree tree;

    char unpacked;
    size_t unpacked_bits;

    const size_t UNPACKED_BITS_INITIAL = sizeof(unpacked) * BIT_CAP;
};

#endif //HUFFMAN_LIB_HUFFMAN_CODE_H
