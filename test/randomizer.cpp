//
// Created by Anton Shelepov on 10.06.18.
//

#include <cstdlib>
#include <fstream>

int rnd(int l, int r) {
    int len = rand() % 10;
    unsigned int res = 0;
    int mxlen = 0;
    int tmp_ = r;
    while (tmp_) {
        tmp_ /= 10;
        mxlen++;
    }
    len = std::min(len, mxlen + 1);
    for (int i = 1; i <= len; ++i)
        res = res * 10 + std::rand() % 10;
    return l + res % (r - l + 1);
}

void setRand() {
    std::fstream f__;
    f__.open("cnt.txt", std::ifstream::in);
    int CNT;
    f__ >> CNT;
    srand(CNT);
    rand();
    f__.close();
    f__.open("cnt.txt", std::ofstream::out);
    f__ << CNT + 1;
    f__.close();
}