#include "gtest/gtest.h"

#include "hash/crc32.h"
#include "hash/sum32.h"

#include <string>
#include <math.h>


TEST(sum32, empty_str) {
    std::stringstream str;
    str << "";
    EXPECT_EQ(0, sum32(str));
}

TEST(crc32, empty_str) {
    std::stringstream str;
    str << "";
    EXPECT_EQ(0, crc32(str));
}

TEST(sum32, single) {
    std::stringstream str;
    str << "@";
    EXPECT_EQ(64, sum32(str));
}

TEST(crc32, single) {
    std::stringstream str;
    str << "@";
    EXPECT_EQ(2766056989, crc32(str));
}

TEST(sum32, bit_size_32) {
    std::stringstream str;
    str << "@@@@";
    EXPECT_EQ(pow(2, 30) + pow(2, 22) + pow(2, 14) + pow(2, 6), sum32(str));
}

TEST(crc32, bit_size_32) {
    std::stringstream str;
    str << "@@@@";
    EXPECT_EQ(1282344052, crc32(str));
}

TEST(sum32, bit_size_40) {
    std::stringstream str;
    str << "@@@@@";
    EXPECT_EQ(pow(2, 30) + pow(2, 22) + pow(2, 14) + 2 * pow(2, 6), sum32(str));
}

TEST(crc32, bit_size_40) {
    std::stringstream str;
    str << "@@@@@";
    EXPECT_EQ(4093277244, crc32(str));
}

TEST(sum32, space) {
    std::stringstream str;
    char b = 0x20;
    str << b;
    EXPECT_EQ( pow(2, 5), sum32(str));
}

TEST(crc32, space) {
    std::stringstream str;
    char b = 0x20;
    str << b;
    EXPECT_EQ(3916222277, crc32(str));
}
