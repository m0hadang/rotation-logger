#include <rotation-logger.hh>
#include <gtest/gtest.h>

TEST(HELLO_GOOGLETEST, HELLO_GOOGLETEST) {
  EXPECT_EQ(rotation_logger::Add(1, 2), 3);
}