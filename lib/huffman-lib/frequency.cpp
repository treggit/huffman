//
// Created by Anton Shelepov on 10.06.18.
//

#include "include/frequency.h"

frequency::frequency() {
    reset_counter();
}

frequency::frequency(char const* seq, size_t len) {
    reset_counter();
    update_frequency(seq, len);
}

void frequency::update_frequency(char const* seq, size_t len) {
    for (size_t i = 0; i < len; i++) {
        counter[static_cast<unsigned char>(seq[i])]++;
    }
}

void frequency::reset_counter() {
    for (size_t i = 0; i < ALPHABER_SIZE; i++) {
        counter[i] = 0;
    }
}
