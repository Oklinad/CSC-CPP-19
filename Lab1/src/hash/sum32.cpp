#include "sum32.h"


uint32_t sum32(std::istream &is) {
    uint32_t sum = 0;
    uint32_t word = 0;
    unsigned long i = 0;

    char buf;
    while (is.get(buf)) {
        word <<= 8;
        word = word | (uint32_t) (uint8_t) buf;
        if (++i % 4 == 0) {
            sum += word;
            word = 0;
        }
    }

    sum += word;

    return sum;
}
