//
// Created by Anton Shelepov on 04.06.18.
//

#include "include/huffman_tree.h"
#include <queue>
#include <iostream>


huffman_tree::huffman_tree() : root(nullptr) {
    table.assign(ALPHABET_SIZE, NOT_USED);
}

void huffman_tree::build(std::vector<std::pair<char, int64_t> > const& chars) {
    std::priority_queue<std::pair<int64_t, node_ptr>> q;
    bytes_encoded = 0;
    for (auto x : chars) {
        q.push({-x.second, node_ptr(new node(x.first))});
        bytes_encoded += x.second;
    }
    while (q.size() > 1) {
        auto left = q.top();
        q.pop();
        auto right = q.top();
        q.pop();
        q.push({left.first + right.first, node_ptr(new node(0, left.second, right.second))});
    }

    if (!q.empty()) {
        root = q.top().second;
    }
    set_codes(root, {0, bytes_encoded == 1});
}

huffman_tree::encoded_tree huffman_tree::encode() {
    encoded_tree encoded;
    size_t bit_ptr = BIT_CAP - 1;
    if (root != nullptr) {
        encoded.edges.push_back(0);
        encoding_tour(root, encoded, bit_ptr);
        encoded.edges.back() |= (1 << bit_ptr);
    }
    encoded.size = encoded.leaves_ordered.size();
    encoded.bytes_encoded = bytes_encoded;
    return encoded;
}


void huffman_tree::decode(encoded_tree encoded) {
    reverse(encoded.leaves_ordered.begin(), encoded.leaves_ordered.end());
    reverse(encoded.edges.begin(), encoded.edges.end());
    size_t bit_ptr = BIT_CAP - 1;
    root = decoding_tour(encoded, bit_ptr);
    build_jumps(root);
}

huffman_code huffman_tree::match_encode(char ch) {
    return table[ch];
}

huffman_tree::node_ptr huffman_tree::get_root() const {
    return root;
}

void huffman_tree::set_codes(node_ptr& v, huffman_code cur_code) {
    if (v == nullptr) {
        return;
    }
    if (v->is_leaf()) {
        table[v->value] = cur_code;
        return;
    }
    set_codes(v->left, {cur_code.value * 2, cur_code.length + 1});
    set_codes(v->right, {cur_code.value * 2 + 1, cur_code.length + 1});
}

void encode_bit_ptr_handler(size_t& bit_ptr, huffman_tree::encoded_tree& encoded) {
    if (bit_ptr == 0) {
        bit_ptr = BIT_CAP;
        encoded.edges.push_back(0);
    }
    bit_ptr--;
}

void huffman_tree::encoding_tour(node_ptr& v, encoded_tree& encoded, size_t& bit_ptr) {
    if (v == nullptr) {
        return;
    }
    if (v->is_leaf()) {
        encoded.leaves_ordered.push_back(v->value);
        return;
    }
    encode_bit_ptr_handler(bit_ptr, encoded);
    encoding_tour(v->left, encoded, bit_ptr);
    encoded.edges.back() |= (1 << bit_ptr);
    encode_bit_ptr_handler(bit_ptr, encoded);
    encoding_tour(v->right, encoded, bit_ptr);
}

void decode_bit_ptr_handler(size_t& bit_ptr, huffman_tree::encoded_tree& encoded) {
    if (bit_ptr == 0) {
        bit_ptr = BIT_CAP;
        encoded.edges.pop_back();
    }
    bit_ptr--;
}


huffman_tree::node_ptr huffman_tree::decoding_tour(encoded_tree& encoded, size_t& bit_ptr, size_t depth) {
    if (encoded.leaves_ordered.empty()) {
        return nullptr;
    }
    node_ptr cur_node(new node(0, depth));

    if ((encoded.edges.back() & (1 << bit_ptr)) == 0) {
        decode_bit_ptr_handler(bit_ptr, encoded);
        cur_node->left = decoding_tour(encoded, bit_ptr, depth + 1);
        decode_bit_ptr_handler(bit_ptr, encoded);
        cur_node->right = decoding_tour(encoded, bit_ptr, depth + 1);
    }
    else {
        cur_node->value = encoded.leaves_ordered.back();
        encoded.leaves_ordered.pop_back();
    }
    return cur_node;
}

void huffman_tree::build_jumps(huffman_tree::node_ptr& v) {
    if (v == nullptr) {
        return;
    }
    if (v->is_leaf()) {
        v->calc_jumps(v);
        return;
    }
    build_jumps(v->left);
    build_jumps(v->right);
    v->calc_jumps(v);
}
