#include <gtest/gtest.h>
#include <calculator/core.h>

TEST(CalculatorTest, add)
{
  calculator::Add add(1, 2);

  ASSERT_EQ(add.compute(), 3);
  ASSERT_EQ(add.the_ultimate_answer(), 42);
}

TEST(CalculatorTest, sub)
{
  calculator::Sub sub(1, 2);

  ASSERT_EQ(sub.compute(), -1);
  ASSERT_EQ(sub.the_ultimate_answer(), 42);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
