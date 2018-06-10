#include <iostream>
#include <iomanip>
#include <cstring>
#include "compress_utills.h"

using namespace std;

void usage_example() {
    cout << "Example usage:\n\thuffman [-e|-d] [SOURCE] [DESTINATION]\n";
}

int main(int argc, char* argv[]) {
    string param = argv[1];

    if ((argc == 2 && param == "--help") || (argc != 4)) {
        usage_example();
        return 0;
    }
    try {
        string filename = argv[2];
        string output = argv[3];
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