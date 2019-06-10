#include <gtest/gtest.h>
#include <increment.h>

TEST(TransformsTest, increment)
{
#ifdef INCREMENT_BY_TWO
  ASSERT_EQ(increment(1), 3);
#else
  ASSERT_EQ(increment(1), 2);
#endif
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
