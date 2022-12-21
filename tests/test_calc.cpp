#include <iostream>
#include "calc.h"
#include "gtest/gtest.h"

TEST(TestCalc, add)
{
    EXPECT_EQ(3, add(1, 2));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}