//
// Created by Антон Шелепов on 10.06.18.
//

#ifndef HUFFMAN_HUFFMAN_CODE_H
#define HUFFMAN_HUFFMAN_CODE_H

#include <cstdio>
#include <cstdint>

const size_t BIT_CAP = 8;

struct huffman_code {
    uint64_t value;
    size_t length;
};

#endif //HUFFMAN_HUFFMAN_CODE_H
