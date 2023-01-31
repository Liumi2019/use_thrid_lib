#include <gtest/gtest.h>
#include "add.h"

// 简单测试
TEST(myMathAdd, add) {
    EXPECT_EQ(add(1, 3), 1 + 3);
    EXPECT_EQ(add(-1, 3), -1 + 3);
}

// 复杂测试
class myMathTest: public ::testing::Test {
protected:

    void SetUp() override {
        c_ = add(a_, b_);
        c1_ = add(b_, a_);
    }

protected:
    int a_ = 1;
    int b_ = -1;
    int c_;
    int c1_;
};

TEST_F(myMathTest, add) {
    EXPECT_EQ(c_, a_ + b_);
    EXPECT_EQ(c1_, a_ + b_);
}

// 高级主题
testing::AssertionResult IsEven(int n) {
  if ((n % 2) == 0)
    return testing::AssertionSuccess();
  else
    return testing::AssertionFailure() << n << " is odd";
}

TEST(betterErrorMessages, IsEven) {
    EXPECT_TRUE(IsEven(add(1, 2)));
}



