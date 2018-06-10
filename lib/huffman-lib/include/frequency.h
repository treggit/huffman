//
// Created by Anton Shelepov on 10.06.18.
//

#ifndef HUFFMAN_FREQUENCY_H
#define HUFFMAN_FREQUENCY_H

#include <cstdint>
#include <cstdio>
#include "huffman_tree.h"
#include "huffman_consts.h"

struct frequency {
    frequency();
    frequency(char const* seq, size_t len);
    void update_frequency(char const* seq, size_t len);
    void reset_counter();

    uint64_t counter[huffman_tree::ALPHABET_SIZE];
};

#endif //HUFFMAN_FREQUENCY_H
