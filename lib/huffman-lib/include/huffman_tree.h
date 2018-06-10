//
// Created by Anton Shelepov on 04.06.18.
//

#ifndef HUFFMAN_LIB_HUFFMAN_TREE_H
#define HUFFMAN_LIB_HUFFMAN_TREE_H

#include <memory>
#include <vector>
#include <iostream>
#include "huffman_code.h"

struct huffman_tree {

    const huffman_code NOT_USED = {0, 0};
    static const size_t ALPHABET_SIZE = 256;

    struct node;
    typedef std::shared_ptr<node> node_ptr;

    struct node {
        char value;
        node_ptr left, right;
        size_t depth;
        std::vector<std::vector<node_ptr>> jump;


        explicit node(char val, size_t d = 0)
                : value(val), left(nullptr), right(nullptr), depth(d) {}

        explicit node(char val, node_ptr& l, node_ptr& r)
                : value(val), left(std::move(l)), right(std::move(r)), depth(0) {}

        bool is_leaf() {
            return (left == nullptr);
        }

        node_ptr calc_jump(node_ptr& child, size_t prefix, size_t size) {
            return child->jump[prefix][size - 1];
        }

        void init_jumps() {
            jump.resize(ALPHABET_SIZE);
            for (auto& x : jump) {
                x.resize(BIT_CAP + 1, node_ptr(new node(*this)));
            }
        }

        void calc_jumps() {
            init_jumps();
            if (is_leaf()) {
                return;
            }
            for (size_t size = 1; size <= BIT_CAP; size++) {
                for (size_t prefix = 0; prefix < ALPHABET_SIZE; prefix++) {
                    if ((prefix & (1 << (size - 1))) > 0) {
                        jump[prefix][size] = calc_jump(right, prefix, size);
                    }
                    else {
                        jump[prefix][size] = calc_jump(left, prefix, size);
                    }
                }
            }
        }
    };

    struct encoded_tree {
        size_t size;
        std::vector<char> edges;
        std::vector<char> leaves_ordered;
        size_t bytes_encoded;
    };

    huffman_tree();
    void build(std::vector<std::pair<char, int64_t> > const& chars);
    encoded_tree encode();
    void decode(encoded_tree encoded);
    huffman_code match_encode(char ch);
    node_ptr get_root() const;

private:

    void set_codes(node_ptr& v, huffman_code cur_code = {0, 0});

    void encoding_tour(node_ptr& v, encoded_tree& encoded, size_t& bit_ptr);
    node_ptr decoding_tour(encoded_tree& encoded, size_t& bit_ptr, size_t depth = 0);
    void build_jumps(node_ptr& v);

    node_ptr root;
    std::vector<huffman_code> table;
    size_t bytes_encoded;
};

#endif //HUFFMAN_LIB_HUFFMAN_TREE_H
