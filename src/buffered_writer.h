//
// Created by Anton Shelepov  on 05.06.18.
//

#ifndef SRC_BUFFERED_WRITER_H
#define SRC_BUFFERED_WRITER_H

#include <fstream>
#include <iostream>

struct buffered_writer {
    explicit buffered_writer(std::string const& filename, bool trunc_mode = false);
    ~buffered_writer();
    void write(char* buffer, size_t len);
    void put_char(char ch);
    void check();

    template <typename T>
    void put(T ch) {
        for (size_t i = sizeof(T); i-- > 0;) {
            put_char(static_cast<char> ((ch >> (8 * i))));
        }
        check();
    }

private:
    std::ofstream out;
};


#endif //SRC_BUFFERED_WRITER_H
