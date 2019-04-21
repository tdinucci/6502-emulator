#include "gtest/gtest.h"
#include "test-utils.h"

using namespace std;
using namespace emu_6502;

const uint8_t CMP_IMM = 0xC9;
const uint8_t CMP_ZPG = 0xC5;
const uint8_t CMP_ZPG_X = 0xD5;
const uint8_t CMP_ABS = 0xCD;
const uint8_t CMP_ABS_X = 0xDD;
const uint8_t CMP_ABS_Y = 0xD9;
const uint8_t CMP_IND_X = 0xC1;
const uint8_t CMP_IND_Y = 0xD1;

const uint8_t CPX_IMM = 0xE0;
const uint8_t CPX_ZPG = 0xE4;
const uint8_t CPX_ABS = 0xEC;

const uint8_t CPY_IMM = 0xC0;
const uint8_t CPY_ZPG = 0xC4;
const uint8_t CPY_ABS = 0xCC;

TEST(CompareOpcodeHandlerContainer, CMP_IMM_Equal) {
    auto machine = create_machine({CMP_IMM, 100});
    machine->get_cpu().get_a().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CMP_IMM_LessThan) {
    auto machine = create_machine({CMP_IMM, 100});
    machine->get_cpu().get_a().set_value(99);
    machine->execute();

    ASSERT_EQ(99, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CMP_IMM_GreaterThan) {
    auto machine = create_machine({CMP_IMM, 100});
    machine->get_cpu().get_a().set_value(101);
    machine->execute();

    ASSERT_EQ(101, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CMP_ZPG) {
    auto machine = create_machine({CMP_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 100);
    machine->get_cpu().get_a().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(100, machine->get_memory().get_at(0x10));

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CMP_ZPG_X) {
    auto machine = create_machine({CMP_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x5);
    machine->get_memory().set_at(0x15, 100);
    machine->get_cpu().get_a().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(100, machine->get_memory().get_at(0x15));

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CMP_ABS) {
    auto machine = create_machine({CMP_ABS, 0x10, 0x2a});
    machine->get_memory().set_at(0x2a10, 100);
    machine->get_cpu().get_a().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(100, machine->get_memory().get_at(0x2a10));

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CMP_ABS_X) {
    auto machine = create_machine({CMP_ABS_X, 0x10, 0x2a});
    machine->get_cpu().get_x().set_value(0x5);
    machine->get_memory().set_at(0x2a15, 100);
    machine->get_cpu().get_a().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(100, machine->get_memory().get_at(0x2a15));

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CMP_ABS_Y) {
    auto machine = create_machine({CMP_ABS_Y, 0x10, 0x2a});
    machine->get_cpu().get_y().set_value(0x7);
    machine->get_memory().set_at(0x2a17, 100);
    machine->get_cpu().get_a().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(100, machine->get_memory().get_at(0x2a17));

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CMP_IND_X) {
    auto machine = create_machine({CMP_IND_X, 0x55});
    machine->get_cpu().get_x().set_value(0x22);
    machine->get_cpu().get_a().set_value(100);
    machine->get_memory().set_at(0x77, 0x34);
    machine->get_memory().set_at(0x78, 0x12);
    machine->get_memory().set_at(0x1234, 100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(100, machine->get_memory().get_at(0x1234));

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CMP_IND_Y) {
    auto machine = create_machine({CMP_IND_Y, 0x41});
    machine->get_cpu().get_y().set_value(0x22);
    machine->get_cpu().get_a().set_value(100);
    machine->get_memory().set_at(0x41, 0x34);
    machine->get_memory().set_at(0x42, 0x12);
    machine->get_memory().set_at(0x1256, 100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(100, machine->get_memory().get_at(0x1256));

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CPX_IMM) {
    auto machine = create_machine({CPX_IMM, 100});
    machine->get_cpu().get_x().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CPX_ZPG) {
    auto machine = create_machine({CPX_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 100);
    machine->get_cpu().get_x().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_x().get_value());
    ASSERT_EQ(100, machine->get_memory().get_at(0x10));

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CPX_ABS) {
    auto machine = create_machine({CPX_ABS, 0x10, 0x2a});
    machine->get_memory().set_at(0x2a10, 100);
    machine->get_cpu().get_x().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_x().get_value());
    ASSERT_EQ(100, machine->get_memory().get_at(0x2a10));

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CPY_IMM) {
    auto machine = create_machine({CPY_IMM, 100});
    machine->get_cpu().get_y().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CPY_ZPG) {
    auto machine = create_machine({CPY_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 100);
    machine->get_cpu().get_y().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_y().get_value());
    ASSERT_EQ(100, machine->get_memory().get_at(0x10));

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(CompareOpcodeHandlerContainer, CPY_ABS) {
    auto machine = create_machine({CPY_ABS, 0x10, 0x2a});
    machine->get_memory().set_at(0x2a10, 100);
    machine->get_cpu().get_y().set_value(100);
    machine->execute();

    ASSERT_EQ(100, machine->get_cpu().get_y().get_value());
    ASSERT_EQ(100, machine->get_memory().get_at(0x2a10));

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}
