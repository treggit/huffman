//
// Created by Anton Shelepov  on 05.06.18.
//

#ifndef SRC_BUFFERED_READER_H
#define SRC_BUFFERED_READER_H

#include <fstream>
#include <iostream>

struct buffered_reader {
    explicit buffered_reader(std::string const& filename);
    ~buffered_reader();
    void reset_ptr();
    size_t read(char* buffer, size_t buffer_size);
    bool can_read();
    char get_char();
    void check();
    void reset_unread_bytes();

    template <typename T>
    void get(T& ch) {
        ch = 0;
        for (size_t i = sizeof(T); i-- > 0;) {
            T c = get_char();
            ch |= (c << (8 * i));
        }
        check();
    }

private:
    std::ifstream in;
    size_t unread_bytes;
};


#endif //SRC_BUFFERED_READER_H
