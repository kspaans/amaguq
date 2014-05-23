#include "gtest/gtest.h"

#include "amaguq.h"

struct ut_list : testing::Test {
};

TEST_F(ut_list, constructor)
{
  atom *b, *c;
  list a(b, c);

  EXPECT_EQ(LIST, a.atype);
  EXPECT_EQ(b, a.car);
  EXPECT_EQ(c, a.cdr);
}

TEST_F(ut_list, print_empty)
{
  list a(nullptr, nullptr);

  EXPECT_EQ("()", a.print());
}
