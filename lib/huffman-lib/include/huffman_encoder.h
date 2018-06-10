//
// Created by Anton Shelepov on 05.06.18.
//

#ifndef HUFFMAN_LIB_HUFFMAN_CODE_H
#define HUFFMAN_LIB_HUFFMAN_CODE_H

#include "huffman_tree.h"

struct huffman_encoder {

    huffman_encoder();
    void init();
    std::vector<huffman_code> encode(char const* chars, size_t len);
    void update_frequency(char const* chars, size_t len);
    huffman_tree::encoded_tree get_service();
    huffman_code match(char ch);

private:
    huffman_tree tree;
    int64_t frequency[huffman_tree::ALPHABET_SIZE];
};

#endif //HUFFMAN_LIB_HUFFMAN_CODE_H
