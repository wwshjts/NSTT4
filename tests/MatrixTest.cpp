#include <gtest/gtest.h>
#include <vector>
#include "../sources/matrix.hpp"

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

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}