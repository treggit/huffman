//
// Created by Anton Shelepov on 09.06.18.
//

#include "../lib/gtest/gtest.h"
#include "huffman_encoder.h"
#include "huffman_decoder.h"
#include "packager.h"
#include <algorithm>

#include "randomizer.h"

using namespace std;

string build_string(char* ptr, size_t len) {
    string res;
    if (ptr == nullptr) {
        return res;
    }
    for (char* ch = ptr; ch != ptr + len; ch++) {
        res.push_back(*ch);
    }
    return res;
}

string encode_decode(string const& text) {
    huffman_encoder encoder;
    huffman_decoder decoder;
    encoder.update_frequency(text.data(), text.length());
    encoder.init();
    decoder.init(encoder.get_service());

    char unpacked = 0;
    size_t unpacked_bits = BIT_CAP;

    vector<huffman_code> encoded_seq = encoder.encode(text.data(), text.size());
    vector<char> packed = pack(unpacked, unpacked_bits, encoded_seq);

    vector<char> decoded_seq = unpack(packed.data(), packed.size(), text.size(), decoder);
    return build_string(decoded_seq.data(), decoded_seq.size());
}


TEST(correctness, empty) {
    string empty;
    EXPECT_EQ(empty, encode_decode(empty));
}

TEST(correctness, single) {
    string single = "x";
    EXPECT_EQ(single, encode_decode(single));
}

TEST(correctness, lilechke) {
    string text = "И в пролет не брошусь, и не выпью яду, и курок над виском не смогу нажать...";
    EXPECT_EQ(text, encode_decode(text));
}

TEST(correctness, dzie_moj_kraj) {
    std::string text = "Дзе мой край? Там, дзе вечную песьню пяе Белавежа...";
    EXPECT_EQ(text, encode_decode(text));
}

TEST(correctness, numbers) {
    string text = "32943435434";
    EXPECT_EQ(text, encode_decode(text));
}

struct random {
    char operator()() {
        return static_cast<char>(rnd(0, 255));
    }
};

string gen_random_string(size_t size) {
    string res(size, 0);
    generate_n(res.begin(), size, random);
    return res;
}

TEST(correctness, random_string) {
    setRand();
    string text = gen_random_string(1000000);
    EXPECT_EQ(text, encode_decode(text));
}

TEST(correctness, randomized) {
    setRand();
    size_t repeat = 100;
    while (repeat--) {
        size_t len = rnd(0, 1000);
        string text = gen_random_string(len);
        EXPECT_EQ(text, encode_decode(text));
    }
}