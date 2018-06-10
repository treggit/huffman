
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
    reset();
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
    check();
    unread_bytes -= gcount;
    return gcount;
}

bool buffered_reader::can_read() {
    return (unread_bytes > 0);
}

char buffered_reader::get_char() {
    char c;
    in.get(c);
    check();
    unread_bytes--;
    return c;
}

void buffered_reader::check() {
    if (in.fail()) {
        throw std::runtime_error("Couldn't read file");
    }
}

void buffered_reader::reset() {
    in.seekg(0, std::ifstream::end);
    unread_bytes = in.tellg();
    reset_ptr();
}