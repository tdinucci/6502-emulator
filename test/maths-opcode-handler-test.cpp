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
