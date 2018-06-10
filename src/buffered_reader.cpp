
//
// Created by Anton Shelepov on 05.06.18.
//

#include "buffered_reader.h"
#include <iostream>

buffered_reader::buffered_reader(std::string const& filename) {
    in.open(filename, std::ifstream::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Couldn't open file: " + filename);
    }
    //in.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    reset_unread_bytes();
}

buffered_reader::~buffered_reader() {
    in.close();
}

void buffered_reader::reset_ptr() {
    in.seekg(0, std::ifstream::beg);
}

size_t buffered_reader::read(char* buffer, size_t buffer_size) {
    size_t gcount = std::min(buffer_size, unread_bytes);
    in.read(buffer, gcount);
    if (!check()) {
        throw std::runtime_error("Couldn't read file");
    }
    unread_bytes -= gcount;
    if (!check()) {
        throw std::runtime_error("Couldn't write file");
    }
    return gcount;
}

bool buffered_reader::can_read() {
    return (unread_bytes > 0);
}

char buffered_reader::get_char() {
    char c;
    in.get(c);
    if (!check()) {
        throw std::runtime_error("Couldnt read file");
    }
    unread_bytes--;
    return c;
}

bool buffered_reader::check() {
    return !in.fail();
}

void buffered_reader::reset_unread_bytes() {
    in.seekg(0, std::ifstream::end);
    unread_bytes = in.tellg();
    reset_ptr();
}