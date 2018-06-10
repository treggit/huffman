//
// Created by Anton Shelepov on 05.06.18.
//

#include "include/huffman_encoder.h"
#include "include/packager.h"

huffman_encoder::huffman_encoder(frequency& count) {
    std::vector<std::pair<char, int64_t>> chars;
    for (size_t i = 0; i < huffman_tree::ALPHABET_SIZE; i++) {
        if (count.counter[i]) {
            chars.push_back({i, count.counter[i]});
        }
    }
    tree.build(chars);
    unpacked = 0;
    unpacked_bits = UNPACKED_BITS_INITIAL;
}

std::vector<char> huffman_encoder::encode(char const* chars, size_t len, bool is_last) {
    std::vector<char> res;
    for (size_t i = 0; i < len; i++) {
        huffman_code code = match(chars[i]);
        while (code.length) {
            complement(unpacked, unpacked_bits, code);
            if (unpacked_bits == 0) {
                res.push_back(unpacked);
                unpacked_bits = UNPACKED_BITS_INITIAL;
                unpacked = 0;
            }
        }
    }
    if (is_last && unpacked_bits != UNPACKED_BITS_INITIAL) {
        res.push_back(unpacked);
    }
    return res;
}

huffman_tree::encoded_tree huffman_encoder::get_service() {
    return tree.encode();
}

huffman_code huffman_encoder::match(char ch) {
    return tree.match_encode(ch);
}
