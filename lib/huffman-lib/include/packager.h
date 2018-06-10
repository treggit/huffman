//
// Created by Anton Shelepov on 10.06.18.
//

#ifndef HUFFMAN_PACKAGER_H
#define HUFFMAN_PACKAGER_H

#include <cstdio>
#include <vector>
#include "huffman_code.h"
#include "huffman_decoder.h"

template <typename T>
void complement(T& unpacked, size_t& unpacked_bits, huffman_code& code) {
    size_t add = std::min(unpacked_bits, code.length);
    unpacked |= (((code.value >> (code.length - add)) & ((1 << add) - 1)) << (unpacked_bits - add));
    unpacked_bits -= add;
    code.length -= add;
}

template <typename T>
void beat_add(T val, std::vector<char>& res) {
    for (size_t i = sizeof(val); i-- > 0;) {
        res.push_back(static_cast<char>((val >> (BIT_CAP * i))));
    }
}

template <typename T>
std::vector<char> pack(T& unpacked, size_t& unpacked_bits, std::vector<huffman_code>& encoded_seq, bool is_last_block = true) {
    size_t process_ptr = 0;
    std::vector<char> res;
    while (process_ptr != encoded_seq.size()) {
        complement(unpacked, unpacked_bits, encoded_seq[process_ptr]);
        if (unpacked_bits == 0) {
            beat_add(unpacked, res);
            unpacked_bits = BIT_CAP * sizeof(unpacked);
            unpacked = 0;
        }
        process_ptr += (encoded_seq[process_ptr].length == 0);
    }
    if (is_last_block && unpacked_bits != BIT_CAP * sizeof(unpacked)) {
        beat_add(unpacked, res);
    }
    return res;
}

template <typename T>
std::vector<char> unpack(T const* code_seq, size_t len, size_t limit, huffman_decoder& decoder) {
    std::vector<char> res;
    for (size_t i = 0; i < len && res.size() < limit; i++) {
        size_t jump_val = BIT_CAP * sizeof(T);
        while (jump_val && res.size() < limit) {
            size_t shift = jump_val;
            shift = decoder.jump(code_seq[i], shift);
            if (decoder.matches_any()) {
                char decoded = decoder.get_decoded_value();
                decoder.reset_automata();
                res.push_back(decoded);
            }
            jump_val -= shift;
        }
    }
    return res;
}

#endif //HUFFMAN_PACKAGER_H
