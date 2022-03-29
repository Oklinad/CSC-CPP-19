#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "hash/crc32.h"
#include "hash/sum32.h"

enum modes {
    mode_sum32, mode_crc32
};

int main(int argc, char **argv) {
    modes mode;
    const char *file_name;
    std::string help = "HELP:\n"
                       "Utility calculates the hash of the file\n"
                       "usage:\n"
                       "./hasher -h\n"
                       "./hasher <filename> -m <mode>\n"
                       "./hasher -m <mode> <filename>\n\n"
                       "where options are:\n"
                       "  <filename>                Name of the file\n"
                       "  -m <mode>                 Where is the <mode> of {crc32, sum32}\n"
                       "  -h                        Display usage information";

    if (argc == 2 && std::strcmp(argv[1], "-h") == 0) {
        std::cout << help << std::endl;
        return 0;
    } else if (argc == 4) {
        int mode_idx, file_idx;

        if (std::strcmp(argv[1], "-m") == 0) {
            mode_idx = 2;
            file_idx = 3;
        } else if (std::strcmp(argv[2], "-m") == 0) {
            mode_idx = 3;
            file_idx = 1;
        } else {
            std::cerr << "ERROR: incorrect arguments.\n" << help << std::endl;
            return 1;
        }

        if (std::strcmp(argv[mode_idx], "sum32") == 0) {
            mode = mode_sum32;
            file_name = argv[file_idx];
        } else if (std::strcmp(argv[mode_idx], "crc32") == 0) {
            mode = mode_crc32;
            file_name = argv[file_idx];
        } else {
            std::cerr << "ERROR: incorrect mode." << help << std::endl;
            return 1;
        }
    } else {
        std::cerr << "ERROR: incorrect arguments." << help << std::endl;
        return 1;
    }

    std::ifstream file(file_name, std::ios::binary);
    if (!file) {
        std::cerr << "ERROR: cannot open file " << file_name << std::endl;
        return 1;
    }

    if (mode == mode_crc32) {
        std::cout << crc32(file);
    } else {
        std::cout << sum32(file);
    }

    return 0;
}