#include <iostream>
#include <iomanip>
#include <cstring>
#include "compress_utills.h"

using namespace std;

void usage_example() {
    cout << "Example usage:\n\thuffman [-e|-d] [SOURCE] [DESTINATION]\n";
}

string build_string(char* ptr) {
    string res;
    for (char* ch = ptr; ch != ptr + strlen(ptr); ch++) {
        res.push_back(*ch);
    }
    return res;
}

int main(int argc, char* argv[]) {
    if ((argc == 2 && build_string(argv[1]) == "--help") || (argc != 4)) {
        usage_example();
        return 0;
    }
    string param = build_string(argv[1]);
    try {
        string filename = build_string(argv[2]);
        string output = build_string(argv[3]);
        if (param == "-e") {
            encode(filename, output);
        }
        if (param == "-d") {
            decode(filename, output);
        }
    }
    catch (exception& e) {
        cout << e.what() << '\n';
    }
    cout << fixed << setprecision(0) << "TIME = " << clock() / (long double)CLOCKS_PER_SEC * 1000 << " ms\n";
    return 0;
}