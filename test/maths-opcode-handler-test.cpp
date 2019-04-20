#include "gtest/gtest.h"
#include "test-utils.h"

using namespace std;
using namespace emu_6502;

const uint8_t ADC_IMM = 0x69;
const uint8_t ADC_ZPG = 0x65;
const uint8_t ADC_ZPG_X = 0x75;
const uint8_t ADC_ABS = 0x6D;
const uint8_t ADC_ABS_X = 0x7D;
const uint8_t ADC_ABS_Y = 0x79;
const uint8_t ADC_IND_X = 0x61;
const uint8_t ADC_IND_Y = 0x71;

const uint8_t SBC_IMM = 0xE9;
const uint8_t SBC_ZPG = 0xE5;
const uint8_t SBC_ZPG_X = 0xF5;
const uint8_t SBC_ABS = 0xED;
const uint8_t SBC_ABS_X = 0xFD;
const uint8_t SBC_ABS_Y = 0xF9;
const uint8_t SBC_IND_X = 0xE1;
const uint8_t SBC_IND_Y = 0xF1;

const uint8_t DEC_ZPG = 0xC6;
const uint8_t DEC_ZPG_X = 0xD6;
const uint8_t DEC_ABS = 0xCE;
const uint8_t DEC_ABS_X = 0xDE;

const uint8_t INC_ZPG = 0xE6;
const uint8_t INC_ZPG_X = 0xF6;
const uint8_t INC_ABS = 0xEE;
const uint8_t INC_ABS_X = 0xFE;

const uint8_t DEX = 0xCA;
const uint8_t DEY = 0x88;
const uint8_t INX = 0xE8;
const uint8_t INY = 0xC8;

TEST(MathsOpcodeHandlerContainer, ADC_IMM) {
    auto machine = create_machine({ADC_IMM, 36});
    machine->get_cpu().get_a().set_value(36);
    machine->execute();

    ASSERT_EQ(72, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, ADC_IMM_ZeroFlag) {
    auto machine = create_machine({ADC_IMM, 0});
    machine->get_cpu().get_a().set_value(0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, ADC_IMM_CarryFlag) {
    auto machine = create_machine({ADC_IMM, 200});
    machine->get_cpu().get_a().set_value(72);
    machine->execute();

    ASSERT_EQ(16, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, ADC_IMM_ZeroAndCarryFlags) {
    auto machine = create_machine({ADC_IMM, 0xFF});
    machine->get_cpu().get_a().set_value(1);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, ADC_IMM_NegativeFlag) {
    auto machine = create_machine({ADC_IMM, 200});
    machine->get_cpu().get_a().set_value(32);
    machine->execute();

    ASSERT_EQ(232, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, ADC_IMM_OverflowFlag_Postive) {
    auto machine = create_machine({ADC_IMM, 120});
    machine->get_cpu().get_a().set_value(32);
    machine->execute();

    ASSERT_EQ(152, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    flags.overflow = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, ADC_IMM_OverflowFlag_Negative) {
    auto machine = create_machine({ADC_IMM, 208});
    machine->get_cpu().get_a().set_value(144);
    machine->execute();

    ASSERT_EQ(96, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.carry = true;
    flags.overflow = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, ADC_ZPG) {
    auto machine = create_machine({ADC_ZPG, 0xf1});
    machine->get_cpu().get_a().set_value(36);
    machine->get_memory().set_at(0xf1, 20);
    machine->execute();

    ASSERT_EQ(56, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, ADC_ZPG_X) {
    auto machine = create_machine({ADC_ZPG_X, 0xf1});
    machine->get_cpu().get_a().set_value(36);
    machine->get_cpu().get_x().set_value(5);
    machine->get_memory().set_at(0xf6, 20);
    machine->execute();

    ASSERT_EQ(56, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, ADC_ABS) {
    auto machine = create_machine({ADC_ABS, 0xf1, 0x36});
    machine->get_cpu().get_a().set_value(36);
    machine->get_memory().set_at(0x36f1, 20);
    machine->execute();

    ASSERT_EQ(56, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, ADC_ABS_X) {
    auto machine = create_machine({ADC_ABS_X, 0xf1, 0x36});
    machine->get_cpu().get_a().set_value(36);
    machine->get_cpu().get_x().set_value(8);
    machine->get_memory().set_at(0x36f9, 20);
    machine->execute();

    ASSERT_EQ(56, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, ADC_ABS_Y) {
    auto machine = create_machine({ADC_ABS_Y, 0xf1, 0x36});
    machine->get_cpu().get_a().set_value(36);
    machine->get_cpu().get_y().set_value(8);
    machine->get_memory().set_at(0x36f9, 20);
    machine->execute();

    ASSERT_EQ(56, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, ADC_IND_X) {
    auto machine = create_machine({ADC_IND_X, 0x41});
    machine->get_cpu().get_x().set_value(0x22);
    machine->get_cpu().get_a().set_value(36);
    machine->get_memory().set_at(0x63, 0x34);
    machine->get_memory().set_at(0x64, 0x12);
    machine->get_memory().set_at(0x1234, 20);
    machine->execute();

    ASSERT_EQ(56, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, ADC_IND_Y) {
    auto machine = create_machine({ADC_IND_Y, 0x41});
    machine->get_cpu().get_y().set_value(0x22);
    machine->get_cpu().get_a().set_value(36);
    machine->get_memory().set_at(0x41, 0x34);
    machine->get_memory().set_at(0x42, 0x12);
    machine->get_memory().set_at(0x1256, 20);
    machine->execute();

    ASSERT_EQ(56, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, SBC_IMM) {
    auto machine = create_machine({SBC_IMM, 0x20});
    machine->get_cpu().get_a().set_value(0x50);
    machine->execute();

    ASSERT_EQ(0x30, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true; // indicates no borrow
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, SBC_IMM_WithBorrow) {
    auto machine = create_machine({SBC_IMM, 0xf0});
    machine->get_cpu().get_a().set_value(0xd0);
    machine->execute();

    ASSERT_EQ(0xe0, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = false; // indicates there was a borrow
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, SBC_IMM_WithOverflow) {
    auto machine = create_machine({SBC_IMM, 0xb0});
    machine->get_cpu().get_a().set_value(0x50);
    machine->execute();

    ASSERT_EQ(0xa0, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = false; // was a borrow
    flags.negative = true;
    flags.overflow = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, SBC_IMM_ZeroFlag) {
    auto machine = create_machine({SBC_IMM, 50});
    machine->get_cpu().get_a().set_value(50);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true; // no borrow
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, SBC_ZPG) {
    auto machine = create_machine({SBC_ZPG, 0xf1});
    machine->get_cpu().get_a().set_value(36);
    machine->get_memory().set_at(0xf1, 20);
    machine->execute();

    ASSERT_EQ(16, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true; // no borrow
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, SBC_ZPG_X) {
    auto machine = create_machine({SBC_ZPG_X, 0xf1});
    machine->get_cpu().get_a().set_value(36);
    machine->get_cpu().get_x().set_value(5);
    machine->get_memory().set_at(0xf6, 20);
    machine->execute();

    ASSERT_EQ(16, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true; // no borrow
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, SBC_ABS) {
    auto machine = create_machine({SBC_ABS, 0xf1, 0x36});
    machine->get_cpu().get_a().set_value(36);
    machine->get_memory().set_at(0x36f1, 20);
    machine->execute();

    ASSERT_EQ(16, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true; // no borrow
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, SBC_ABS_X) {
    auto machine = create_machine({SBC_ABS_X, 0xf1, 0x36});
    machine->get_cpu().get_a().set_value(36);
    machine->get_cpu().get_x().set_value(8);
    machine->get_memory().set_at(0x36f9, 20);
    machine->execute();

    ASSERT_EQ(16, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true; // no borrow
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, SBC_ABS_Y) {
    auto machine = create_machine({SBC_ABS_Y, 0xf1, 0x36});
    machine->get_cpu().get_a().set_value(36);
    machine->get_cpu().get_y().set_value(8);
    machine->get_memory().set_at(0x36f9, 20);
    machine->execute();

    ASSERT_EQ(16, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true; // no borrow
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, SBC_IND_X) {
    auto machine = create_machine({SBC_IND_X, 0x41});
    machine->get_cpu().get_x().set_value(0x22);
    machine->get_cpu().get_a().set_value(36);
    machine->get_memory().set_at(0x63, 0x34);
    machine->get_memory().set_at(0x64, 0x12);
    machine->get_memory().set_at(0x1234, 20);
    machine->execute();

    ASSERT_EQ(16, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true; // no borrow
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, SBC_IND_Y) {
    auto machine = create_machine({SBC_IND_Y, 0x41});
    machine->get_cpu().get_y().set_value(0x22);
    machine->get_cpu().get_a().set_value(36);
    machine->get_memory().set_at(0x41, 0x34);
    machine->get_memory().set_at(0x42, 0x12);
    machine->get_memory().set_at(0x1256, 20);
    machine->execute();

    ASSERT_EQ(16, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true; // no borrow
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, DEC_ZPG) {
    auto machine = create_machine({DEC_ZPG, 0xf1});
    machine->get_memory().set_at(0xf1, 20);
    machine->execute();

    ASSERT_EQ(19, machine->get_memory().get_at(0xf1));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, DEC_ZPG_ZeroFlag) {
    auto machine = create_machine({DEC_ZPG, 0xf1});
    machine->get_memory().set_at(0xf1, 1);
    machine->execute();

    ASSERT_EQ(0, machine->get_memory().get_at(0xf1));

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, DEC_ZPG_NegativeFlag) {
    auto machine = create_machine({DEC_ZPG, 0xf1});
    machine->get_memory().set_at(0xf1, 0);
    machine->execute();

    ASSERT_EQ(0xFF, machine->get_memory().get_at(0xf1));

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, DEC_ZPG_X) {
    auto machine = create_machine({DEC_ZPG_X, 0x45});
    machine->get_cpu().get_x().set_value(0x10);
    machine->get_memory().set_at(0x55, 20);
    machine->execute();

    ASSERT_EQ(19, machine->get_memory().get_at(0x55));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, DEC_ABS) {
    auto machine = create_machine({DEC_ABS, 0x45, 0x1a});
    machine->get_memory().set_at(0x1a45, 20);
    machine->execute();

    ASSERT_EQ(19, machine->get_memory().get_at(0x1a45));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, DEC_ABS_X) {
    auto machine = create_machine({DEC_ABS_X, 0x45, 0x1a});
    machine->get_cpu().get_x().set_value(0x10);
    machine->get_memory().set_at(0x1a55, 20);
    machine->execute();

    ASSERT_EQ(19, machine->get_memory().get_at(0x1a55));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, INC_ZPG) {
    auto machine = create_machine({INC_ZPG, 0xf1});
    machine->get_memory().set_at(0xf1, 20);
    machine->execute();

    ASSERT_EQ(21, machine->get_memory().get_at(0xf1));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, INC_ZPG_ZeroFlag) {
    auto machine = create_machine({INC_ZPG, 0xf1});
    machine->get_memory().set_at(0xf1, 0xff);
    machine->execute();

    ASSERT_EQ(0, machine->get_memory().get_at(0xf1));

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, INC_ZPG_NegativeFlag) {
    auto machine = create_machine({INC_ZPG, 0xf1});
    machine->get_memory().set_at(0xf1, 0x7f);
    machine->execute();

    ASSERT_EQ(0x80, machine->get_memory().get_at(0xf1));

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, INC_ZPG_X) {
    auto machine = create_machine({INC_ZPG_X, 0x45});
    machine->get_cpu().get_x().set_value(0x10);
    machine->get_memory().set_at(0x55, 20);
    machine->execute();

    ASSERT_EQ(21, machine->get_memory().get_at(0x55));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, INC_ABS) {
    auto machine = create_machine({INC_ABS, 0x45, 0x1a});
    machine->get_memory().set_at(0x1a45, 20);
    machine->execute();

    ASSERT_EQ(21, machine->get_memory().get_at(0x1a45));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, INC_ABS_X) {
    auto machine = create_machine({INC_ABS_X, 0x45, 0x1a});
    machine->get_cpu().get_x().set_value(0x10);
    machine->get_memory().set_at(0x1a55, 20);
    machine->execute();

    ASSERT_EQ(21, machine->get_memory().get_at(0x1a55));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, INX) {
    auto machine = create_machine({INX});
    machine->get_cpu().get_x().set_value(5);
    machine->execute();

    ASSERT_EQ(6, machine->get_cpu().get_x().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, INX_ZeroFlag) {
    auto machine = create_machine({INX});
    machine->get_cpu().get_x().set_value(0xff);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, INX_NegativeFlag) {
    auto machine = create_machine({INX});
    machine->get_cpu().get_x().set_value(0x7f);
    machine->execute();

    ASSERT_EQ(0x80, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, INY) {
    auto machine = create_machine({INY});
    machine->get_cpu().get_y().set_value(5);
    machine->execute();

    ASSERT_EQ(6, machine->get_cpu().get_y().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, DEX) {
    auto machine = create_machine({DEX});
    machine->get_cpu().get_x().set_value(5);
    machine->execute();

    ASSERT_EQ(4, machine->get_cpu().get_x().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(MathsOpcodeHandlerContainer, DEX_ZeroFlag) {
    auto machine = create_machine({DEX});
    machine->get_cpu().get_x().set_value(1);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, DEX_NegativeFlag) {
    auto machine = create_machine({DEX});
    machine->get_cpu().get_x().set_value(0);
    machine->execute();

    ASSERT_EQ(0xff, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(MathsOpcodeHandlerContainer, DEY) {
    auto machine = create_machine({DEY});
    machine->get_cpu().get_y().set_value(5);
    machine->execute();

    ASSERT_EQ(4, machine->get_cpu().get_y().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}
