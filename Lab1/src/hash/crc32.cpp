#include "crc32.h"

uint32_t crc32(std::istream &is) {
    unsigned long crc_table[256];
    unsigned long crc;

    for (int i = 0; i < 256; i++) {
        crc = i;
        for (int j = 0; j < 8; j++) {
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        }
        crc_table[i] = crc;
    }

    crc = 0xFFFFFFFFUL;
    char buf;
    while (is.get(buf)) {
        crc = crc_table[(crc ^ buf) & 0xFF] ^ (crc >> 8);
    }

    return crc ^ 0xFFFFFFFFUL;
}