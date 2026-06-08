#include <gtest/gtest.h>
#include "../src/smartArray/SmartArray.h"

TEST(ExampleTest, ReturnValidValue) {
    SmartArray sa;
    EXPECT_EQ(sa.gtestExample(), 52);
}

TEST(ExampleTest, ReturnInvalidValue) {
    SmartArray sa;
    EXPECT_NE(sa.gtestExample(), 50);
}