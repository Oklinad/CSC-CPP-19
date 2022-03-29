#include "gtest/gtest.h"

#include "polynomial/Polynomial.h"

#include <string>


TEST(polynom, example_1) {
    Polynomial<double> a(3);
    a[5] = 42.0;
    EXPECT_EQ(42, a[5]);
}

TEST(polynom, example_2) {
    Polynomial<int> a;
    const Polynomial<int> &b = a;
    a[5] = 42;
    EXPECT_EQ(42, b[5]);
}

TEST(polynom, example_3) {
    Polynomial<int> a;
    a[1] = 1;
    a[3] = 3;
    a[5] = 5;
    a[5] = 0;
    EXPECT_EQ(3, a.degree());
}

TEST(polynom, example_4) {
    Polynomial<int> a;
    a[0] = 3;
    a[1] = 5;
    const Polynomial<int> b = a;

    std::string str;
    for (auto it = b.begin(); it != b.end(); ++it) {
        str += std::to_string(*it) + '\n';
    }

    EXPECT_EQ("3\n5\n", str);
}

TEST(polynom, example_5) {
    Polynomial<double> a(3);
    const auto &b = a;
    const double &c5 = b[5];
    a[4] = 7.0;
    a[5] = 42.0;
    EXPECT_EQ(42.0, c5);
}

TEST(polynom, example_6) {
    Polynomial<int> a{3, 0, 0, 5};
    for (int &coeff : a)
        coeff = 1;
    Polynomial<int> b{1, 1, 1, 1};
    EXPECT_EQ(b, a);
}

TEST(polynom, empty_degree) {
    Polynomial<int> a;
    EXPECT_EQ(-1, a.degree());
}

TEST(polynom, degree) {
    Polynomial<int> a{1, 0, 0, 0};
    EXPECT_EQ(0, a.degree());
}

TEST(polynom, sum_polynom) {
    Polynomial<int> a{3, 0, 0, 5};
    Polynomial<int> b{1, 1, 1};
    Polynomial<int> c{4, 1, 1, 5};
    EXPECT_EQ(c, a + b);
}

TEST(polynom, difference_polynom) {
    Polynomial<int> a{4, 1, 1, 5};
    Polynomial<int> b{1, 1, 1};
    Polynomial<int> c{3, 0, 0, 5};
    EXPECT_EQ(c, a - b);
}

TEST(polynom, mult_polynom) {
    Polynomial<int> a{1, 1};
    Polynomial<int> b{1, 1};
    Polynomial<int> c{1, 2, 1};
    EXPECT_EQ(c, a * b);
}

TEST(polynom, div_polynom) {
    Polynomial<int> a{2, 2, 1};
    Polynomial<int> b{1, 1};
    Polynomial<int> c{1, 1};
    EXPECT_EQ(c, a / b);
}

TEST(polynom, mod_polynom) {
    Polynomial<int> a{2, 2, 1};
    Polynomial<int> b{1, 1};
    Polynomial<int> c{1};
    EXPECT_EQ(c, a % b);
}

TEST(polynom, sum_number) {
    Polynomial<int> a{3, 0, 0, 5};
    int b = 5;
    Polynomial<int> c{8, 0, 0, 5};
    EXPECT_EQ(c, a + b);
}

TEST(polynom, difference_number) {
    Polynomial<int> a{8, 0, 0, 5};
    int b = 5;
    Polynomial<int> c{3, 0, 0, 5};
    EXPECT_EQ(c, a - b);
}

TEST(polynom, mult_number) {
    Polynomial<int> a{3, 0, 0, 5};
    int b = 5;
    Polynomial<int> c{15, 0, 0, 25};
    EXPECT_EQ(c, a * b);
}

TEST(polynom, div_number) {
    Polynomial<int> a{15, 0, 0, 25};
    int b = 5;
    Polynomial<int> c{3, 0, 0, 5};
    EXPECT_EQ(c, a / b);
}

TEST(polynom, mod_number) {
    Polynomial<int> a{3, 0, 0, 5};
    int b = 5;
    Polynomial<int> c{3, 0, 0, 0};
    EXPECT_EQ(c, a % b);
}

TEST(polynom, eq_sum_polynom) {
    Polynomial<int> a{3, 0, 0, 5};
    Polynomial<int> b{1, 1, 1};
    Polynomial<int> c{4, 1, 1, 5};
    a += b;
    EXPECT_EQ(c, a);
}

TEST(polynom, eq_difference_polynom) {
    Polynomial<int> a{4, 1, 1, 5};
    Polynomial<int> b{1, 1, 1};
    Polynomial<int> c{3, 0, 0, 5};
    a -= b;
    EXPECT_EQ(c, a);
}

TEST(polynom, eq_mult_polynom) {
    Polynomial<int> a{1, 1};
    Polynomial<int> b{1, 1};
    Polynomial<int> c{1, 2, 1};
    a *= b;
    EXPECT_EQ(c, a);
}

TEST(polynom, eq_div_polynom) {
    Polynomial<int> a{2, 2, 1};
    Polynomial<int> b{1, 1};
    Polynomial<int> c{1, 1};
    a /= b;
    EXPECT_EQ(c, a);
}

TEST(polynom, eq_mod_polynom) {
    Polynomial<int> a{2, 2, 1};
    Polynomial<int> b{1, 1};
    Polynomial<int> c{1};
    a %= b;
    EXPECT_EQ(c, a);
}

TEST(polynom, eq_sum_number) {
    Polynomial<int> a{3, 0, 0, 5};
    int b = 5;
    Polynomial<int> c{8, 0, 0, 5};
    a += b;
    EXPECT_EQ(c, a);
}

TEST(polynom, eq_difference_number) {
    Polynomial<int> a{8, 0, 0, 5};
    int b = 5;
    Polynomial<int> c{3, 0, 0, 5};
    a -= b;
    EXPECT_EQ(c, a);
}

TEST(polynom, eq_mult_number) {
    Polynomial<int> a{3, 0, 0, 5};
    int b = 5;
    Polynomial<int> c{15, 0, 0, 25};
    a *= b;
    EXPECT_EQ(c, a);
}

TEST(polynom, eq_div_number) {
    Polynomial<int> a{15, 0, 0, 25};
    int b = 5;
    Polynomial<int> c{3, 0, 0, 5};
    a /= b;
    EXPECT_EQ(c, a);
}

TEST(polynom, eq_mod_number) {
    Polynomial<int> a{3, 0, 0, 5};
    int b = 5;
    Polynomial<int> c{3, 0, 0, 0};
    a %= b;
    EXPECT_EQ(c, a);
}

TEST(polynom, equal_1) {
    Polynomial<int> a{3, 2, 3, 5};
    Polynomial<int> c{3, 2, 3, 5};
    EXPECT_EQ(true, a == c);
}

TEST(polynom, equal_2) {
    Polynomial<int> a{3, 0, 0};
    Polynomial<int> c{3, 0, 0, 0};
    EXPECT_EQ(true, a == c);
}

TEST(polynom, equal_3) {
    Polynomial<int> a{ 3, 5 }, b = a;
    b[5] = 0;
    bool equal = (a == b);
    EXPECT_EQ(true, equal);
}

TEST(polynom, not_equal_1) {
    Polynomial<int> a{3, 0, 0, 2};
    Polynomial<int> c{3, 0, 0, 1};
    EXPECT_EQ(true, a != c);
}

TEST(polynom, not_equal_2) {
    Polynomial<int> a{3, 0, 0};
    Polynomial<int> c{3, 0, 0, 1};
    EXPECT_EQ(true, a != c);
}

TEST(polynom, to_stream) {
    Polynomial<int> a{3, -1, 0, 5, 0};
    std::stringstream str;
    str << a;
    EXPECT_EQ("5*x^{3}-x+3", str.str());
}
