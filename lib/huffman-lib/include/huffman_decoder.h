//
// Created by Anton Shelepov on 05.06.18.
//

#ifndef HUFFMAN_LIB_HUFFMAN_DECODER_H
#define HUFFMAN_LIB_HUFFMAN_DECODER_H

#include "huffman_tree.h"
#include "frequency.h"

struct huffman_decoder {
    huffman_decoder(huffman_tree::encoded_tree const& encoded);
    void reset_automata();
    void read_bit(bool dir);
    bool matches_any() const;
    char get_decoded_value() const;
    size_t get_bytes_expected() const;
    size_t get_depth() const;
    size_t jump(char path, size_t steps);

private:
    huffman_tree tree;
    huffman_tree::node* automata_ptr;
    size_t bytes_expected;
};


#endif //HUFFMAN_LIB_HUFFMAN_DECODER_H
