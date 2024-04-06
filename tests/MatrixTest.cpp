#include <gtest/gtest.h>
#include <vector>
#include "../sources/matrix.hpp"

static size_t square(size_t a) {
    return a * a;
}

static size_t min(size_t a, size_t b) {
    return (a <= b) ? a : b;
}

TEST(MemoryManagementTest, DirectCtr) {
    size_t m1_size = 1000;
    size_t m2_size = 2000;
    Matrix m1(m1_size);
    Matrix m2(m2_size);
    EXPECT_EQ(m1_size, m1.size());
    EXPECT_EQ(m2_size, m2.size());
}

TEST(MemoryManagementTest, DoubleCtr) { 
    size_t test_size = 10;
    std::vector<double> arr = std::vector<double>(10);
    for (size_t i = 0; i < test_size; i++) {
        arr[i] = i;
    }

    Matrix m { arr };

    for (size_t i = 0; i < test_size; i++) {
        EXPECT_EQ(arr[i], m.get(i,i));
    }
}

TEST(MemoryManagementTest, Copy) {
    size_t size = 10;
    Matrix m{ size }; 
    m.set(5, 4, 42);

    Matrix copy{ m };
    Matrix assignment_copy { 10 };

    assignment_copy = m;
    EXPECT_EQ(m.get(5, 4), copy.get(5, 4));
    EXPECT_EQ(m.get(5, 4), assignment_copy.get(5, 4));
}

TEST(MemoryManagementTest, MoveCtr1) {
    size_t size = 10;
    Matrix m{ size }; 
    m.set(1, 1, 42);
    Matrix moved_m = std::move(m);
    EXPECT_EQ(42, moved_m.get(1, 1));
}

TEST(MemoryManagementTest, MoveCtr) {
    std::vector<double> vec = std::vector<double>(10);
    for (size_t i = 0; i < 10; i++) {
        vec[i] = i;
    }
    Matrix init_with_tmp { Matrix { vec } } ;
    for (size_t i = 0; i < 10; i++) {
        EXPECT_EQ(i, init_with_tmp.get(i, i));
    }
}

TEST(PlusOperatorOverloading, PlusTest) {
    size_t test_size = 3;
    Matrix a { test_size };
    Matrix b { test_size };

    int cnt = 0;
    for (size_t i = 0; i < test_size; i++) {
        for (size_t j = 0; j < test_size; j++) {
            a.set(i, j, cnt);
            b.set(i, j, 10 - cnt);
            cnt++;
        }
    }
    Matrix c = a + b;
    for (size_t i = 0; i < test_size; i++) {
        for (size_t j = 0; j < test_size; j++) {
            EXPECT_EQ(10, c.get(i, j));
        }
    }
}

TEST(PlusOperatorOverloading, PlusTestWithDeferentSizes) {
    std::vector<double> vec_a = {2, 2, 2};
    std::vector<double> vec_b = {40, 40, 40, 50};

    Matrix a { vec_a };
    Matrix b { vec_b };

    Matrix c = a + b;
    EXPECT_EQ(min(vec_a.size(), vec_b.size()), c.size());
    for (size_t i = 0; i < min(vec_a.size(), vec_b.size()); i++) {
        for (size_t j = 0; j < min(vec_a.size(), vec_b.size()); j++) {
            if (i == j) {
                EXPECT_EQ(42, c.get(i, j));
            } else {
                EXPECT_EQ(0, c.get(i, j));
            }
        }
    }
}

TEST(PlusOperatorOverloading, ImplicitConversion) {
    std::vector<double> vec_a = {2, 2, 2};
    std::vector<double> vec_b = {40, 40, 40, 50};

    Matrix a { vec_a };

    Matrix c = vec_b + a;
    EXPECT_EQ(min(vec_a.size(), vec_b.size()), c.size());
    for (size_t i = 0; i < min(vec_a.size(), vec_b.size()); i++) {
        for (size_t j = 0; j < min(vec_a.size(), vec_b.size()); j++) {
            if (i == j) {
                EXPECT_EQ(42, c.get(i, j));
            } else {
                EXPECT_EQ(0, c.get(i, j));
            }
        }
    }
}

TEST(PlusOperatorOverloading, PlusAssignmentOperator) {
    std::vector<double> vec_a = {21, 21, 21};
    size_t size = vec_a.size();

    Matrix a { vec_a };
    a += a;

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (i == j) {
                EXPECT_EQ(42, a.get(i, j));
            } else {
                EXPECT_EQ(0, a.get(i, j));
            }
        }
    }
}

TEST(DoubleConversionTest, ConversionToDouble) {
    size_t test_size = 20;
    Matrix m { test_size };

    int cnt = 0;
    for (size_t i = 0; i < test_size; i++) {
        for (size_t j = 0; j < test_size; j++) {
            m.set(i, j, cnt);
            cnt++;
        }
    }

    EXPECT_EQ(square(test_size) * (square(test_size) - 1) / 2, static_cast<double>(m));
}

TEST(MinusOperatorOverloading, MinusOperator) {
    size_t test_size = 3;
    Matrix a { test_size };
    Matrix b { test_size };

    int cnt = 0;
    for (size_t i = 0; i < test_size; i++) {
        for (size_t j = 0; j < test_size; j++) {
            a.set(i, j, cnt);
            b.set(i, j, cnt);
            cnt++;
        }
    }
    Matrix c = a - b;
    for (size_t i = 0; i < test_size; i++) {
        for (size_t j = 0; j < test_size; j++) {
            EXPECT_EQ(0, c.get(i, j));
        }
    }
}

TEST(MinusOperatorOverloading, MinusAssignmentOperator) {
    std::vector<double> vec_a = {21, 21, 21};
    size_t size = vec_a.size();

    Matrix a { vec_a };
    a -= a;

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            EXPECT_EQ(0, a.get(i, j));
        }
    }

}

TEST(ComparisonOperator, Equal) {
    std::vector<double> vec_a = {42, 42, 42};
    size_t size = vec_a.size();

    Matrix a { vec_a };
    Matrix b = a;

    EXPECT_TRUE(a == b);
}

TEST(ComparisonOperator, NotEqual) {
    std::vector<double> vec_a = {42, 42, 42};
    size_t size = vec_a.size();

    Matrix a { vec_a };
    Matrix b = a;
    b *= 42;

    EXPECT_TRUE(a != b);
}

TEST(MultiplicationOperatorOverloadingTest, MultiplicationAssignmentOperator) {
    std::vector<double> vec_a = {2, 2, 2};
    size_t size = vec_a.size();

    Matrix a { vec_a };
    a *= a;

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (i == j) {
                EXPECT_EQ(4, a.get(i, j));
            } else {
                EXPECT_EQ(0, a.get(i, j));
            }
        }
    }

}

TEST(MultiplicationOperatorOverloadingTest, MultiplicationAssignmentOperatorDouble) {
    std::vector<double> vec_a = {2, 2, 2};
    size_t size = vec_a.size();

    Matrix a { vec_a };
    a *= 2;

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (i == j) {
                EXPECT_EQ(4, a.get(i, j));
            } else {
                EXPECT_EQ(0, a.get(i, j));
            }
        }
    }
}
int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}