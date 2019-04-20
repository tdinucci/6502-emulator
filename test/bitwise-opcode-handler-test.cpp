#include "gtest/gtest.h"
#include "test-utils.h"

using namespace std;
using namespace emu_6502;

const uint8_t AND_IMM = 0x29;
const uint8_t AND_ZPG = 0x25;
const uint8_t AND_ZPG_X = 0x35;
const uint8_t AND_ABS = 0x2D;
const uint8_t AND_ABS_X = 0x3D;
const uint8_t AND_ABS_Y = 0x39;
const uint8_t AND_IND_X = 0x21;
const uint8_t AND_IND_Y = 0x31;

const uint8_t ORA_IMM = 0x09;
const uint8_t ORA_ZPG = 0x05;
const uint8_t ORA_ZPG_X = 0x15;
const uint8_t ORA_ABS = 0x0D;
const uint8_t ORA_ABS_X = 0x1D;
const uint8_t ORA_ABS_Y = 0x19;
const uint8_t ORA_IND_X = 0x01;
const uint8_t ORA_IND_Y = 0x11;

const uint8_t EOR_IMM = 0x49;
const uint8_t EOR_ZPG = 0x45;
const uint8_t EOR_ZPG_X = 0x55;
const uint8_t EOR_ABS = 0x4D;
const uint8_t EOR_ABS_X = 0x5D;
const uint8_t EOR_ABS_Y = 0x59;
const uint8_t EOR_IND_X = 0x41;
const uint8_t EOR_IND_Y = 0x51;

const uint8_t BIT_ZPG = 0x24;
const uint8_t BIT_ABS = 0x2C;

const uint8_t ASL_ACC = 0x0A;
const uint8_t ASL_ZPG = 0x06;
const uint8_t ASL_ZPG_X = 0x16;
const uint8_t ASL_ABS = 0x0E;
const uint8_t ASL_ABS_X = 0x1E;

const uint8_t LSR_ACC = 0x4A;
const uint8_t LSR_ZPG = 0x46;
const uint8_t LSR_ZPG_X = 0x56;
const uint8_t LSR_ABS = 0x4E;
const uint8_t LSR_ABS_X = 0x5E;

const uint8_t ROL_ACC = 0x2A;
const uint8_t ROL_ZPG = 0x26;
const uint8_t ROL_ZPG_X = 0x36;
const uint8_t ROL_ABS = 0x2E;
const uint8_t ROL_ABS_X = 0x3E;

const uint8_t ROR_ACC = 0x6A;
const uint8_t ROR_ZPG = 0x66;
const uint8_t ROR_ZPG_X = 0x76;
const uint8_t ROR_ABS = 0x6E;
const uint8_t ROR_ABS_X = 0x7E;

TEST(LoadOpcodeHandlerContainer, AND_IMM) {
    auto machine = create_machine({AND_IMM, 0x23});
    machine->get_cpu().get_a().set_value(0x13);
    machine->execute();

    ASSERT_EQ(0x03, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, AND_IMM_ZeroFlag) {
    auto machine = create_machine({AND_IMM, 0x11});
    machine->get_cpu().get_a().set_value(0x22);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, AND_IMM_NegativeFlag) {
    auto machine = create_machine({AND_IMM, 0xF0});
    machine->get_cpu().get_a().set_value(0xA1);
    machine->execute();

    ASSERT_EQ(0xA0, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, AND_ZPG) {
    auto machine = create_machine({AND_ZPG, 0xF5});
    machine->get_memory().set_at(0xF5, 0x55);
    machine->get_cpu().get_a().set_value(0x41);
    machine->execute();

    ASSERT_EQ(0x41, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, AND_ZPG_X) {
    auto machine = create_machine({AND_ZPG_X, 0x30});
    machine->get_cpu().get_x().set_value(0x50);
    machine->get_memory().set_at(0x80, 0x55);
    machine->get_cpu().get_a().set_value(0x41);
    machine->execute();

    ASSERT_EQ(0x41, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, AND_ABS) {
    auto machine = create_machine({AND_ABS, 0x30, 0x05});
    machine->get_memory().set_at(0x0530, 0x55);
    machine->get_cpu().get_a().set_value(0x41);
    machine->execute();

    ASSERT_EQ(0x41, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, AND_ABS_X) {
    auto machine = create_machine({AND_ABS_X, 0x30, 0x05});
    machine->get_cpu().get_x().set_value(0xA);
    machine->get_memory().set_at(0x053A, 0x55);
    machine->get_cpu().get_a().set_value(0x41);
    machine->execute();

    ASSERT_EQ(0x41, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, AND_ABS_Y) {
    auto machine = create_machine({AND_ABS_Y, 0x30, 0x05});
    machine->get_cpu().get_y().set_value(0xA);
    machine->get_memory().set_at(0x053A, 0x55);
    machine->get_cpu().get_a().set_value(0x41);
    machine->execute();

    ASSERT_EQ(0x41, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, AND_IND_X) {
    auto machine = create_machine({AND_IND_X, 0x55});
    machine->get_cpu().get_x().set_value(0x22);
    machine->get_cpu().get_a().set_value(0x41);
    machine->get_memory().set_at(0x77, 0x34);
    machine->get_memory().set_at(0x78, 0x12);
    machine->get_memory().set_at(0x1234, 0x43);
    machine->execute();

    ASSERT_EQ(0x41, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, AND_IND_Y) {
    auto machine = create_machine({AND_IND_Y, 0x41});
    machine->get_cpu().get_y().set_value(0x22);
    machine->get_cpu().get_a().set_value(0xFF);
    machine->get_memory().set_at(0x41, 0x34);
    machine->get_memory().set_at(0x42, 0x12);
    machine->get_memory().set_at(0x1256, 0x29);
    machine->execute();

    ASSERT_EQ(0x29, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ORA_IMM) {
    auto machine = create_machine({ORA_IMM, 0x30});
    machine->get_cpu().get_a().set_value(0x13);
    machine->execute();

    ASSERT_EQ(0x33, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ORA_IMM_ZeroFlag) {
    auto machine = create_machine({ORA_IMM, 0x00});
    machine->get_cpu().get_a().set_value(0x00);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ORA_IMM_NegativeFlag) {
    auto machine = create_machine({ORA_IMM, 0xF0});
    machine->get_cpu().get_a().set_value(0xA1);
    machine->execute();

    ASSERT_EQ(0xF1, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ORA_ZPG) {
    auto machine = create_machine({ORA_ZPG, 0xF5});
    machine->get_memory().set_at(0xF5, 0x10);
    machine->get_cpu().get_a().set_value(0x25);
    machine->execute();

    ASSERT_EQ(0x35, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ORA_ZPG_X) {
    auto machine = create_machine({ORA_ZPG_X, 0x30});
    machine->get_cpu().get_x().set_value(0x50);
    machine->get_memory().set_at(0x80, 0x81);
    machine->get_cpu().get_a().set_value(0x42);
    machine->execute();

    ASSERT_EQ(0xC3, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ORA_ABS) {
    auto machine = create_machine({ORA_ABS, 0x30, 0x05});
    machine->get_memory().set_at(0x0530, 0x55);
    machine->get_cpu().get_a().set_value(0x41);
    machine->execute();

    ASSERT_EQ(0x55, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ORA_ABS_X) {
    auto machine = create_machine({ORA_ABS_X, 0x30, 0x05});
    machine->get_cpu().get_x().set_value(0xA);
    machine->get_memory().set_at(0x053A, 0x40);
    machine->get_cpu().get_a().set_value(0x53);
    machine->execute();

    ASSERT_EQ(0x53, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ORA_ABS_Y) {
    auto machine = create_machine({ORA_ABS_Y, 0x30, 0x05});
    machine->get_cpu().get_y().set_value(0xA);
    machine->get_memory().set_at(0x053A, 0x20);
    machine->get_cpu().get_a().set_value(0x02);
    machine->execute();

    ASSERT_EQ(0x22, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ORA_IND_X) {
    auto machine = create_machine({ORA_IND_X, 0x55});
    machine->get_cpu().get_x().set_value(0x22);
    machine->get_cpu().get_a().set_value(0x18);
    machine->get_memory().set_at(0x77, 0x34);
    machine->get_memory().set_at(0x78, 0x12);
    machine->get_memory().set_at(0x1234, 0x18);
    machine->execute();

    ASSERT_EQ(0x18, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ORA_IND_Y) {
    auto machine = create_machine({ORA_IND_Y, 0x41});
    machine->get_cpu().get_y().set_value(0x22);
    machine->get_cpu().get_a().set_value(0xFF);
    machine->get_memory().set_at(0x41, 0x34);
    machine->get_memory().set_at(0x42, 0x12);
    machine->get_memory().set_at(0x1256, 0x23);
    machine->execute();

    ASSERT_EQ(0xFF, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, EOR_IMM) {
    auto machine = create_machine({EOR_IMM, 0x30});
    machine->get_cpu().get_a().set_value(0x13);
    machine->execute();

    ASSERT_EQ(0x23, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, EOR_IMM_ZeroFlag) {
    auto machine = create_machine({EOR_IMM, 0x11});
    machine->get_cpu().get_a().set_value(0x11);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, EOR_IMM_NegativeFlag) {
    auto machine = create_machine({EOR_IMM, 0xF0});
    machine->get_cpu().get_a().set_value(0x05);
    machine->execute();

    ASSERT_EQ(0xF5, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, EOR_ZPG) {
    auto machine = create_machine({EOR_ZPG, 0xF5});
    machine->get_memory().set_at(0xF5, 0x31);
    machine->get_cpu().get_a().set_value(0x25);
    machine->execute();

    ASSERT_EQ(0x14, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, EOR_ZPG_X) {
    auto machine = create_machine({EOR_ZPG_X, 0x30});
    machine->get_cpu().get_x().set_value(0x50);
    machine->get_memory().set_at(0x80, 0x31);
    machine->get_cpu().get_a().set_value(0x23);
    machine->execute();

    ASSERT_EQ(0x12, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, EOR_ABS) {
    auto machine = create_machine({EOR_ABS, 0x30, 0x05});
    machine->get_memory().set_at(0x0530, 0x55);
    machine->get_cpu().get_a().set_value(0x41);
    machine->execute();

    ASSERT_EQ(0x14, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, EOR_ABS_X) {
    auto machine = create_machine({EOR_ABS_X, 0x30, 0x05});
    machine->get_cpu().get_x().set_value(0xA);
    machine->get_memory().set_at(0x053A, 0x40);
    machine->get_cpu().get_a().set_value(0x53);
    machine->execute();

    ASSERT_EQ(0x13, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, EOR_ABS_Y) {
    auto machine = create_machine({EOR_ABS_Y, 0x30, 0x05});
    machine->get_cpu().get_y().set_value(0xA);
    machine->get_memory().set_at(0x053A, 0x20);
    machine->get_cpu().get_a().set_value(0x02);
    machine->execute();

    ASSERT_EQ(0x22, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, EOR_IND_X) {
    auto machine = create_machine({EOR_IND_X, 0x55});
    machine->get_cpu().get_x().set_value(0x22);
    machine->get_cpu().get_a().set_value(0x19);
    machine->get_memory().set_at(0x77, 0x34);
    machine->get_memory().set_at(0x78, 0x12);
    machine->get_memory().set_at(0x1234, 0x28);
    machine->execute();

    ASSERT_EQ(0x31, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, EOR_IND_Y) {
    auto machine = create_machine({EOR_IND_Y, 0x41});
    machine->get_cpu().get_y().set_value(0x22);
    machine->get_cpu().get_a().set_value(0x35);
    machine->get_memory().set_at(0x41, 0x34);
    machine->get_memory().set_at(0x42, 0x12);
    machine->get_memory().set_at(0x1256, 0x23);
    machine->execute();

    ASSERT_EQ(0x16, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, BIT_ZPG) {
    auto machine = create_machine({BIT_ZPG, 0x41});
    machine->get_cpu().get_a().set_value(0x23);
    machine->get_memory().set_at(0x41, 0x35);
    machine->execute();

    ASSERT_EQ(0x23, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(0x35, machine->get_memory().get_at(0x41));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, BIT_ZPG_ZeroFlag) {
    auto machine = create_machine({BIT_ZPG, 0x41});
    machine->get_cpu().get_a().set_value(0x11);
    machine->get_memory().set_at(0x41, 0x22);
    machine->execute();

    ASSERT_EQ(0x11, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(0x22, machine->get_memory().get_at(0x41));
    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, BIT_ZPG_NegativeFlag) {
    auto machine = create_machine({BIT_ZPG, 0x41});
    machine->get_cpu().get_a().set_value(0x23);
    machine->get_memory().set_at(0x41, 0xa5);
    machine->execute();

    ASSERT_EQ(0x23, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(0xa5, machine->get_memory().get_at(0x41));
    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, BIT_ZPG_OverflowFlag) {
    auto machine = create_machine({BIT_ZPG, 0x41});
    machine->get_cpu().get_a().set_value(0x23);
    machine->get_memory().set_at(0x41, 0x45);
    machine->execute();

    ASSERT_EQ(0x23, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(0x45, machine->get_memory().get_at(0x41));
    RegisterFlagSet flags{};
    flags.overflow = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, BIT_ZPG_ZeroNegativeAndOverflowFlag) {
    auto machine = create_machine({BIT_ZPG, 0x41});
    machine->get_cpu().get_a().set_value(0x02);
    machine->get_memory().set_at(0x41, 0xc5);
    machine->execute();

    ASSERT_EQ(0x02, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(0xc5, machine->get_memory().get_at(0x41));
    RegisterFlagSet flags{};
    flags.overflow = true;
    flags.negative = true;
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, BIT_ABS) {
    auto machine = create_machine({BIT_ABS, 0x41, 0x90});
    machine->get_cpu().get_a().set_value(0x23);
    machine->get_memory().set_at(0x9041, 0x35);
    machine->execute();

    ASSERT_EQ(0x23, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(0x35, machine->get_memory().get_at(0x9041));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ASL_ACC) {
    auto machine = create_machine({ASL_ACC});
    machine->get_cpu().get_a().set_value(0x09);
    machine->execute();

    ASSERT_EQ(0x12, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ASL_ACC_CarryFlag) {
    auto machine = create_machine({ASL_ACC});
    machine->get_cpu().get_a().set_value(0x99);
    machine->execute();

    ASSERT_EQ(0x32, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ASL_ACC_ZeroFlag) {
    auto machine = create_machine({ASL_ACC});
    machine->get_cpu().get_a().set_value(0x80);
    machine->execute();

    ASSERT_EQ(0x0, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ASL_ACC_NegativeFlag) {
    auto machine = create_machine({ASL_ACC});
    machine->get_cpu().get_a().set_value(0xc0);
    machine->execute();

    ASSERT_EQ(0x80, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ASL_ZPG) {
    auto machine = create_machine({ASL_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 0x09);
    machine->execute();

    ASSERT_EQ(0x12, machine->get_memory().get_at(0x10));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ASL_ZPG_CarryFlag) {
    auto machine = create_machine({ASL_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 0x99);
    machine->execute();

    ASSERT_EQ(0x32, machine->get_memory().get_at(0x10));
    RegisterFlagSet flags{};
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ASL_ZPG_ZeroFlag) {
    auto machine = create_machine({ASL_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 0x80);
    machine->execute();

    ASSERT_EQ(0x0, machine->get_memory().get_at(0x10));
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ASL_ZPG_NegativeFlag) {
    auto machine = create_machine({ASL_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 0xc0);
    machine->execute();

    ASSERT_EQ(0x80, machine->get_memory().get_at(0x10));
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ASL_ZPG_X) {
    auto machine = create_machine({ASL_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x5);
    machine->get_memory().set_at(0x15, 0x09);
    machine->execute();

    ASSERT_EQ(0x12, machine->get_memory().get_at(0x15));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ASL_ABS) {
    auto machine = create_machine({ASL_ABS, 0x10, 0x85});
    machine->get_memory().set_at(0x8510, 0x09);
    machine->execute();

    ASSERT_EQ(0x12, machine->get_memory().get_at(0x8510));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ASL_ABS_X) {
    auto machine = create_machine({ASL_ABS_X, 0x10, 0x85});
    machine->get_cpu().get_x().set_value(0x5);
    machine->get_memory().set_at(0x8515, 0x09);
    machine->execute();

    ASSERT_EQ(0x12, machine->get_memory().get_at(0x8515));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LSR_ACC) {
    auto machine = create_machine({LSR_ACC});
    machine->get_cpu().get_a().set_value(0x8);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LSR_ACC_CarryFlag) {
    auto machine = create_machine({LSR_ACC});
    machine->get_cpu().get_a().set_value(0x9);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LSR_ACC_ZeroFlag) {
    auto machine = create_machine({LSR_ACC});
    machine->get_cpu().get_a().set_value(1);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LSR_ZPG) {
    auto machine = create_machine({LSR_ZPG, 0x5});
    machine->get_memory().set_at(0x5, 0x8);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_memory().get_at(0x5));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LSR_ZPG_CarryFlag) {
    auto machine = create_machine({LSR_ZPG, 0x5});
    machine->get_memory().set_at(0x5, 0x9);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_memory().get_at(0x5));
    RegisterFlagSet flags{};
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LSR_ZPG_ZeroFlag) {
    auto machine = create_machine({LSR_ZPG, 0x5});
    machine->get_memory().set_at(0x5, 1);
    machine->execute();

    ASSERT_EQ(0, machine->get_memory().get_at(0x5));
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LSR_ZPG_X) {
    auto machine = create_machine({LSR_ZPG_X, 0x5});
    machine->get_cpu().get_x().set_value(0x5);
    machine->get_memory().set_at(0x0a, 0x8);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_memory().get_at(0xa));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LSR_ABS) {
    auto machine = create_machine({LSR_ABS, 0x5, 0x8});
    machine->get_memory().set_at(0x805, 0x8);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_memory().get_at(0x805));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LSR_ABS_X) {
    auto machine = create_machine({LSR_ABS_X, 0x5, 0x8});
    machine->get_cpu().get_x().set_value(0x5);
    machine->get_memory().set_at(0x80a, 0x8);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_memory().get_at(0x80a));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROL_ACC) {
    auto machine = create_machine({ROL_ACC});
    machine->get_cpu().get_a().set_value(0x09);
    machine->execute();

    ASSERT_EQ(0x12, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROL_ACC_OldCarry) {
    auto machine = create_machine({ROL_ACC});
    machine->get_cpu().get_a().set_value(0x09);
    machine->get_cpu().get_ps().set_carry(true);
    machine->execute();

    ASSERT_EQ(0x13, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROL_ACC_CarryFlag) {
    auto machine = create_machine({ROL_ACC});
    machine->get_cpu().get_a().set_value(0x89);
    machine->get_cpu().get_ps().set_carry(true);
    machine->execute();

    ASSERT_EQ(0x13, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROL_ACC_NegativeFlag) {
    auto machine = create_machine({ROL_ACC});
    machine->get_cpu().get_a().set_value(0xc9);
    machine->get_cpu().get_ps().set_carry(true);
    machine->execute();

    ASSERT_EQ(0x93, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROL_ACC_ZeroFlag) {
    auto machine = create_machine({ROL_ACC});
    machine->get_cpu().get_a().set_value(0x80);
    machine->execute();

    ASSERT_EQ(0x0, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROL_ZPG) {
    auto machine = create_machine({ROL_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 0x09);
    machine->execute();

    ASSERT_EQ(0x12, machine->get_memory().get_at(0x10));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROL_ZPG_OldCarry) {
    auto machine = create_machine({ROL_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 0x09);
    machine->get_cpu().get_ps().set_carry(true);
    machine->execute();

    ASSERT_EQ(0x13, machine->get_memory().get_at(0x10));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROL_ZPG_CarryFlag) {
    auto machine = create_machine({ROL_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 0x89);
    machine->get_cpu().get_ps().set_carry(true);
    machine->execute();

    ASSERT_EQ(0x13, machine->get_memory().get_at(0x10));
    RegisterFlagSet flags{};
    flags.carry = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROL_ZPG_NegativeFlag) {
    auto machine = create_machine({ROL_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 0xc9);
    machine->get_cpu().get_ps().set_carry(true);
    machine->execute();

    ASSERT_EQ(0x93, machine->get_memory().get_at(0x10));
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROL_ZPG_ZeroFlag) {
    auto machine = create_machine({ROL_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 0x80);
    machine->execute();

    ASSERT_EQ(0x0, machine->get_memory().get_at(0x10));
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROL_ZPG_X) {
    auto machine = create_machine({ROL_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x5);
    machine->get_memory().set_at(0x15, 0x09);
    machine->execute();

    ASSERT_EQ(0x12, machine->get_memory().get_at(0x15));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROL_ABS) {
    auto machine = create_machine({ROL_ABS, 0x10, 0x11});
    machine->get_memory().set_at(0x1110, 0x09);
    machine->execute();

    ASSERT_EQ(0x12, machine->get_memory().get_at(0x1110));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROL_ABS_X) {
    auto machine = create_machine({ROL_ABS_X, 0x10, 0x11});
    machine->get_cpu().get_x().set_value(0x5);
    machine->get_memory().set_at(0x1115, 0x09);
    machine->execute();

    ASSERT_EQ(0x12, machine->get_memory().get_at(0x1115));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROR_ACC) {
    auto machine = create_machine({ROR_ACC});
    machine->get_cpu().get_a().set_value(0x08);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROR_ACC_OldCarry) {
    auto machine = create_machine({ROR_ACC});
    machine->get_cpu().get_ps().set_carry(true);
    machine->get_cpu().get_a().set_value(0x08);
    machine->execute();

    ASSERT_EQ(0x84, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROR_ACC_NegativeAndCarryFlag) {
    auto machine = create_machine({ROR_ACC});
    machine->get_cpu().get_ps().set_carry(true);
    machine->get_cpu().get_a().set_value(0x09);
    machine->execute();

    ASSERT_EQ(0x84, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROR_ACC_ZeroFlag) {
    auto machine = create_machine({ROR_ACC});
    machine->get_cpu().get_a().set_value(0x01);
    machine->execute();

    ASSERT_EQ(0x0, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROR_ZPG) {
    auto machine = create_machine({ROR_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 0x08);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_memory().get_at(0x10));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROR_ZPG_OldCarry) {
    auto machine = create_machine({ROR_ZPG, 0x10});
    machine->get_cpu().get_ps().set_carry(true);
    machine->get_memory().set_at(0x10, 0x08);
    machine->execute();

    ASSERT_EQ(0x84, machine->get_memory().get_at(0x10));
    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROR_ZPG_NegativeAndCarryFlag) {
    auto machine = create_machine({ROR_ZPG, 0x10});
    machine->get_cpu().get_ps().set_carry(true);
    machine->get_memory().set_at(0x10, 0x09);
    machine->execute();

    ASSERT_EQ(0x84, machine->get_memory().get_at(0x10));
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROR_ZPG_ZeroFlag) {
    auto machine = create_machine({ROR_ZPG, 0x10});
    machine->get_memory().set_at(0x10, 0x01);
    machine->execute();

    ASSERT_EQ(0x0, machine->get_memory().get_at(0x10));
    RegisterFlagSet flags{};
    flags.carry = true;
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, ROR_ZPG_X) {
    auto machine = create_machine({ROR_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x5);
    machine->get_memory().set_at(0x15, 0x08);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_memory().get_at(0x15));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROR_ABS) {
    auto machine = create_machine({ROR_ABS, 0x10, 0x75});
    machine->get_memory().set_at(0x7510, 0x08);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_memory().get_at(0x7510));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, ROR_ABS_X) {
    auto machine = create_machine({ROR_ABS_X, 0x10, 0x75});
    machine->get_cpu().get_x().set_value(0x5);
    machine->get_memory().set_at(0x7515, 0x08);
    machine->execute();

    ASSERT_EQ(0x4, machine->get_memory().get_at(0x7515));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}
