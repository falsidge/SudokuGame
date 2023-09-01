#include <gtest/gtest.h>

TEST(TestingTesting, StringEqual) {
    EXPECT_EQ("ThisString", "ThisString");
}

TEST(TestingTesting, StringNotEqual) {
    EXPECT_EQ("ThisString1", "ThisString");
}