#include "gtest/gtest.h"
#include "../src/register/register.h"

TEST(Construct, Equals) {
    auto reg = new Register<uint16_t>("PC");

    EXPECT_EQ("PC", reg->get_name());
}
