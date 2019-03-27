#include "gtest/gtest.h"
#include "../src/register/status-register.h"
#include <memory>
#include <sstream>
#include <iostream>

using namespace std;

string get_bit_pattern(StatusRegister* reg) {
    stringstream stream;
    stream << reg->get_value();

    return stream.str();
}

TEST(StatusRegister, Construct) {
    auto reg = make_unique<StatusRegister>(StatusRegister());
    auto bit_pattern = get_bit_pattern(reg.get());

    EXPECT_EQ("P", reg->get_name());

    EXPECT_EQ("00000000", bit_pattern);

    EXPECT_EQ(false, reg->is_carry_set());
    EXPECT_EQ(false, reg->is_zero_set());
    EXPECT_EQ(false, reg->is_interupt_disable_set());
    EXPECT_EQ(false, reg->is_decimal_set());
    EXPECT_EQ(false, reg->is_break_set());
    EXPECT_EQ(false, reg->is_overflow_set());
    EXPECT_EQ(false, reg->is_negative_set());
}

TEST(StatusRegister, CarryFlag) {
    auto reg = make_unique<StatusRegister>(StatusRegister());
    EXPECT_EQ(false, reg->is_carry_set());

    reg->set_carry(true);
    EXPECT_EQ(true, reg->is_carry_set());

    auto bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00000001", bit_pattern);

    reg->set_carry(false);
    EXPECT_EQ(false, reg->is_carry_set());
    bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00000000", bit_pattern);
}

TEST(StatusRegister, ZeroFlag) {
    auto reg = make_unique<StatusRegister>(StatusRegister());
    EXPECT_EQ(false, reg->is_zero_set());

    reg->set_zero(true);
    EXPECT_EQ(true, reg->is_zero_set());

    auto bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00000010", bit_pattern);

    reg->set_zero(false);
    EXPECT_EQ(false, reg->is_zero_set());
    bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00000000", bit_pattern);
}

TEST(StatusRegister, InteruptDisableFlag) {
    auto reg = make_unique<StatusRegister>(StatusRegister());
    EXPECT_EQ(false, reg->is_interupt_disable_set());

    reg->set_interupt_disable(true);
    EXPECT_EQ(true, reg->is_interupt_disable_set());

    auto bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00000100", bit_pattern);

    reg->set_interupt_disable(false);
    EXPECT_EQ(false, reg->is_interupt_disable_set());
    bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00000000", bit_pattern);
}

TEST(StatusRegister, DecimalFlag) {
    auto reg = make_unique<StatusRegister>(StatusRegister());
    EXPECT_EQ(false, reg->is_decimal_set());

    reg->set_decimal(true);
    EXPECT_EQ(true, reg->is_decimal_set());

    auto bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00001000", bit_pattern);

    reg->set_decimal(false);
    EXPECT_EQ(false, reg->is_decimal_set());
    bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00000000", bit_pattern);
}

TEST(StatusRegister, BreakFlag) {
    auto reg = make_unique<StatusRegister>(StatusRegister());
    EXPECT_EQ(false, reg->is_break_set());

    reg->set_break(true);
    EXPECT_EQ(true, reg->is_break_set());

    auto bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00010000", bit_pattern);

    reg->set_break(false);
    EXPECT_EQ(false, reg->is_break_set());
    bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00000000", bit_pattern);
}

TEST(StatusRegister, OverflowFlag) {
    auto reg = make_unique<StatusRegister>(StatusRegister());
    EXPECT_EQ(false, reg->is_overflow_set());

    reg->set_overflow(true);
    EXPECT_EQ(true, reg->is_overflow_set());

    auto bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("01000000", bit_pattern);

    reg->set_overflow(false);
    EXPECT_EQ(false, reg->is_overflow_set());
    bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00000000", bit_pattern);
}

TEST(StatusRegister, NegativeFlag) {
    auto reg = make_unique<StatusRegister>(StatusRegister());
    EXPECT_EQ(false, reg->is_negative_set());

    reg->set_negative(true);
    EXPECT_EQ(true, reg->is_negative_set());

    auto bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("10000000", bit_pattern);

    reg->set_negative(false);
    EXPECT_EQ(false, reg->is_negative_set());
    bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00000000", bit_pattern);
}

TEST(StatusRegister, AllFlags) {
    auto reg = make_unique<StatusRegister>(StatusRegister());
    EXPECT_EQ(false, reg->is_negative_set());

    reg->set_carry(true);
    reg->set_zero(true);
    reg->set_interupt_disable(true);
    reg->set_decimal(true);
    reg->set_break(true);
    reg->set_overflow(true);
    reg->set_negative(true);

    auto bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("11011111", bit_pattern);

    reg->set_carry(false);
    reg->set_zero(false);
    reg->set_interupt_disable(false);
    reg->set_decimal(false);
    reg->set_break(false);
    reg->set_overflow(false);
    reg->set_negative(false);

    bit_pattern = get_bit_pattern(reg.get());
    EXPECT_EQ("00000000", bit_pattern);
}
