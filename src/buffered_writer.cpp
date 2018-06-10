//
// Created by Anton Shelepov  on 05.06.18.
//

#include "buffered_writer.h"

buffered_writer::buffered_writer(std::string const& filename, bool trunc_mode) {
    if (trunc_mode) {
        out.open(filename, std::ofstream::trunc | std::ofstream::binary);
    }
    else {
        out.open(filename, std::ofstream::binary);
    }
    if (!out.is_open()) {
        throw std::runtime_error("Couldn't open file: " + filename);
    }
    //out.exceptions(std::ofstream::badbit | std::ifstream::failbit);
}

buffered_writer::~buffered_writer() {
    out.close();
}

void buffered_writer::write(char* buffer, size_t len) {
    out.write(buffer, len);
    check();
}

void buffered_writer::put_char(char ch) {
    out.put(ch);
    check();
}

void buffered_writer::check() {
    if (out.fail()) {
        throw std::runtime_error("Couldn't write file");
    }
}
