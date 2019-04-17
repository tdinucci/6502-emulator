#include "gtest/gtest.h"
#include "test-utils.h"

using namespace std;
using namespace emu_6502;

const uint8_t LDA_IMM = 0xA9;
const uint8_t LDA_ZPG = 0xA5;
const uint8_t LDA_ZPG_X = 0xB5;
const uint8_t LDA_ABS = 0xAD;
const uint8_t LDA_ABS_X = 0xBD;
const uint8_t LDA_ABS_Y = 0xB9;
const uint8_t LDA_IND_X = 0xA1;
const uint8_t LDA_IND_Y = 0xB1;

const uint8_t LDX_IMM = 0xA2;
const uint8_t LDX_ZPG = 0xA6;
const uint8_t LDX_ZPG_Y = 0xB6;
const uint8_t LDX_ABS = 0xAE;
const uint8_t LDX_ABS_Y = 0xBE;

const uint8_t LDY_IMM = 0xA0;
const uint8_t LDY_ZPG = 0xA4;
const uint8_t LDY_ZPG_X = 0xB4;
const uint8_t LDY_ABS = 0xAC;
const uint8_t LDY_ABS_X = 0xBC;

TEST(LoadOpcodeHandlerContainer, LDA_IMM) {
    auto machine = create_machine({LDA_IMM, 36});
    machine->execute();

    ASSERT_EQ(36, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDA_IMM_ZeroFlag) {
    auto machine = create_machine({LDA_IMM, 0});
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_IMM_NegativeFlag) {
    // ensure bit 7 set
    auto machine = create_machine({LDA_IMM, 128});
    machine->execute();

    ASSERT_EQ(128, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_ZPG) {
    auto machine = create_machine({LDA_ZPG, 123});

    machine->get_memory().set_at(123, 78);
    machine->execute();

    ASSERT_EQ(78, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDA_ZPG_ZeroFlag) {
    auto machine = create_machine({LDA_ZPG, 123});

    machine->get_memory().set_at(123, 0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_ZPG_NegativeFlag) {
    auto machine = create_machine({LDA_ZPG, 123});

    // ensure bit 7 set
    machine->get_memory().set_at(123, 150);
    machine->execute();

    ASSERT_EQ(150, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_ZPG_X) {
    auto machine = create_machine({LDA_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x15);

    machine->get_memory().set_at(0x25, 78);
    machine->execute();

    ASSERT_EQ(78, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDA_ZPG_X_Wrap) {
    auto machine = create_machine({LDA_ZPG_X, 0xFF});
    machine->get_cpu().get_x().set_value(0x80);

    machine->get_memory().set_at(0x7F, 78);
    machine->execute();

    ASSERT_EQ(78, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDA_ZPG_X_ZeroFlag) {
    auto machine = create_machine({LDA_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x15);

    machine->get_memory().set_at(0x25, 0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_ZPG_X_NegativeFlag) {
    auto machine = create_machine({LDA_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x15);

    // ensure bit 7 set
    machine->get_memory().set_at(0x25, 0xF5);
    machine->execute();

    ASSERT_EQ(0xF5, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_ABS) {
    auto machine = create_machine({LDA_ABS, 0x55, 0x66});
    machine->get_memory().set_at(0x6655, 0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDA_ABS_ZeroFlag) {
    auto machine = create_machine({LDA_ABS, 0x55, 0x66});
    machine->get_memory().set_at(0x6655, 0x0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_ABS_NegativeFlag) {
    // ensure bit 7 set
    auto machine = create_machine({LDA_ABS, 0x55, 0x66});
    machine->get_memory().set_at(0x6655, 0xF6);
    machine->execute();

    ASSERT_EQ(0xF6, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_ABS_X) {
    auto machine = create_machine({LDA_ABS_X, 0x55, 0x66});
    machine->get_cpu().get_x().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDA_ABS_X_ZeroFlag) {
    auto machine = create_machine({LDA_ABS_X, 0x55, 0x66});
    machine->get_cpu().get_x().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0x0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_ABS_X_NegativeFlag) {
    // ensure bit 7 set
    auto machine = create_machine({LDA_ABS_X, 0x55, 0x66});
    machine->get_cpu().get_x().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0xF6);
    machine->execute();

    ASSERT_EQ(0xF6, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_ABS_Y) {
    auto machine = create_machine({LDA_ABS_Y, 0x55, 0x66});
    machine->get_cpu().get_y().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDA_ABS_Y_ZeroFlag) {
    auto machine = create_machine({LDA_ABS_Y, 0x55, 0x66});
    machine->get_cpu().get_y().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0x0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_ABS_Y_NegativeFlag) {
    // ensure bit 7 set
    auto machine = create_machine({LDA_ABS_Y, 0x55, 0x66});
    machine->get_cpu().get_y().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0xF6);
    machine->execute();

    ASSERT_EQ(0xF6, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_IND_X) {
    auto machine = create_machine({LDA_IND_X, 0x55});
    machine->get_cpu().get_x().set_value(0x4);

    // pointer
    machine->get_memory().set_at(0x59, 0x3c);
    machine->get_memory().set_at(0x5A, 0x4d);

    // value
    machine->get_memory().set_at(0x4d3c, 0x33);

    machine->execute();

    ASSERT_EQ(0x33, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDA_IND_X_Wrap) {
    auto machine = create_machine({LDA_IND_X, 0xFF});
    machine->get_cpu().get_x().set_value(0x6b);

    // pointer
    machine->get_memory().set_at(0x6a, 0x3c);
    machine->get_memory().set_at(0x6b, 0x4d);

    // value
    machine->get_memory().set_at(0x4d3c, 0x33);

    machine->execute();

    ASSERT_EQ(0x33, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDA_IND_X_ZeroFlag) {
    auto machine = create_machine({LDA_IND_X, 0x55});
    machine->get_cpu().get_x().set_value(0x4);

    // pointer
    machine->get_memory().set_at(0x59, 0x3c);
    machine->get_memory().set_at(0x5A, 0x4d);

    // value
    machine->get_memory().set_at(0x4d3c, 0);

    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_IND_X_NegativeFlag) {
    auto machine = create_machine({LDA_IND_X, 0x55});
    machine->get_cpu().get_x().set_value(0x4);

    // pointer
    machine->get_memory().set_at(0x59, 0x3c);
    machine->get_memory().set_at(0x5A, 0x4d);

    // value - ensure bit 7 set
    machine->get_memory().set_at(0x4d3c, 0xe3);

    machine->execute();

    ASSERT_EQ(0xe3, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_IND_Y) {
    auto machine = create_machine({LDA_IND_Y, 0x55});
    machine->get_memory().set_at(0x55, 0x12);
    machine->get_memory().set_at(0x56, 0x34);

    machine->get_cpu().get_y().set_value(0x1a);

    machine->get_memory().set_at(0x342c, 0x33);

    machine->execute();

    ASSERT_EQ(0x33, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDA_IND_Y_ZeroFlag) {
    auto machine = create_machine({LDA_IND_Y, 0x55});
    machine->get_memory().set_at(0x55, 0x12);
    machine->get_memory().set_at(0x56, 0x34);

    machine->get_cpu().get_y().set_value(0x1a);

    machine->get_memory().set_at(0x342c, 0);

    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDA_IND_Y_NegativeFlag) {
    auto machine = create_machine({LDA_IND_Y, 0x55});
    machine->get_memory().set_at(0x55, 0x12);
    machine->get_memory().set_at(0x56, 0x34);

    machine->get_cpu().get_y().set_value(0x1a);

    // ensure bit 7 set
    machine->get_memory().set_at(0x342c, 0xf3);

    machine->execute();

    ASSERT_EQ(0xf3, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDX_IMM) {
    auto machine = create_machine({LDX_IMM, 36});
    machine->execute();

    ASSERT_EQ(36, machine->get_cpu().get_x().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDX_IMM_ZeroFlag) {
    auto machine = create_machine({LDX_IMM, 0});
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDX_IMM_NegativeFlag) {
    auto machine = create_machine({LDX_IMM, 0xff});
    machine->execute();

    ASSERT_EQ(0xff, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDX_ZPG) {
    auto machine = create_machine({LDX_ZPG, 123});

    machine->get_memory().set_at(123, 78);
    machine->execute();

    ASSERT_EQ(78, machine->get_cpu().get_x().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDX_ZPG_ZeroFlag) {
    auto machine = create_machine({LDX_ZPG, 123});

    machine->get_memory().set_at(123, 0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDX_ZPG_NegativeFlag) {
    auto machine = create_machine({LDX_ZPG, 123});

    // ensure bit 7 set
    machine->get_memory().set_at(123, 150);
    machine->execute();

    ASSERT_EQ(150, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDX_ZPG_Y) {
    auto machine = create_machine({LDX_ZPG_Y, 0x10});
    machine->get_cpu().get_y().set_value(0x15);

    machine->get_memory().set_at(0x25, 78);
    machine->execute();

    ASSERT_EQ(78, machine->get_cpu().get_x().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDX_ZPG_Y_Wrap) {
    auto machine = create_machine({LDX_ZPG_Y, 0xFF});
    machine->get_cpu().get_y().set_value(0x80);

    machine->get_memory().set_at(0x7F, 78);
    machine->execute();

    ASSERT_EQ(78, machine->get_cpu().get_x().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDX_ZPG_Y_ZeroFlag) {
    auto machine = create_machine({LDX_ZPG_Y, 0x10});
    machine->get_cpu().get_y().set_value(0x15);

    machine->get_memory().set_at(0x25, 0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDX_ZPG_Y_NegativeFlag) {
    auto machine = create_machine({LDX_ZPG_Y, 0x10});
    machine->get_cpu().get_y().set_value(0x15);

    // ensure bit 7 set
    machine->get_memory().set_at(0x25, 0xF5);
    machine->execute();

    ASSERT_EQ(0xF5, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDX_ABS) {
    auto machine = create_machine({LDX_ABS, 0x55, 0x66});
    machine->get_memory().set_at(0x6655, 0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_cpu().get_x().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDX_ABS_ZeroFlag) {
    auto machine = create_machine({LDX_ABS, 0x55, 0x66});
    machine->get_memory().set_at(0x6655, 0x0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDX_ABS_NegativeFlag) {
    // ensure bit 7 set
    auto machine = create_machine({LDX_ABS, 0x55, 0x66});
    machine->get_memory().set_at(0x6655, 0xF6);
    machine->execute();

    ASSERT_EQ(0xF6, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDX_ABS_Y) {
    auto machine = create_machine({LDX_ABS_Y, 0x55, 0x66});
    machine->get_cpu().get_y().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_cpu().get_x().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDX_ABS_Y_ZeroFlag) {
    auto machine = create_machine({LDX_ABS_Y, 0x55, 0x66});
    machine->get_cpu().get_y().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0x0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDX_ABS_Y_NegativeFlag) {
    // ensure bit 7 set
    auto machine = create_machine({LDX_ABS_Y, 0x55, 0x66});
    machine->get_cpu().get_y().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0xF6);
    machine->execute();

    ASSERT_EQ(0xF6, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDY_IMM) {
    auto machine = create_machine({LDY_IMM, 36});
    machine->execute();

    ASSERT_EQ(36, machine->get_cpu().get_y().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDY_IMM_ZeroFlag) {
    auto machine = create_machine({LDY_IMM, 0});
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDY_IMM_NegativeFlag) {
    auto machine = create_machine({LDY_IMM, 0xff});
    machine->execute();

    ASSERT_EQ(0xff, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDY_ZPG) {
    auto machine = create_machine({LDY_ZPG, 123});

    machine->get_memory().set_at(123, 78);
    machine->execute();

    ASSERT_EQ(78, machine->get_cpu().get_y().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDY_ZPG_ZeroFlag) {
    auto machine = create_machine({LDY_ZPG, 123});

    machine->get_memory().set_at(123, 0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDY_ZPG_NegativeFlag) {
    auto machine = create_machine({LDY_ZPG, 123});

    // ensure bit 7 set
    machine->get_memory().set_at(123, 150);
    machine->execute();

    ASSERT_EQ(150, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDY_ZPG_X) {
    auto machine = create_machine({LDY_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x15);

    machine->get_memory().set_at(0x25, 78);
    machine->execute();

    ASSERT_EQ(78, machine->get_cpu().get_y().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDY_ZPG_X_Wrap) {
    auto machine = create_machine({LDY_ZPG_X, 0xFF});
    machine->get_cpu().get_x().set_value(0x80);

    machine->get_memory().set_at(0x7F, 78);
    machine->execute();

    ASSERT_EQ(78, machine->get_cpu().get_y().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDY_ZPG_X_ZeroFlag) {
    auto machine = create_machine({LDY_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x15);

    machine->get_memory().set_at(0x25, 0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDY_ZPG_X_NegativeFlag) {
    auto machine = create_machine({LDY_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x15);

    // ensure bit 7 set
    machine->get_memory().set_at(0x25, 0xF5);
    machine->execute();

    ASSERT_EQ(0xF5, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDY_ABS) {
    auto machine = create_machine({LDY_ABS, 0x55, 0x66});
    machine->get_memory().set_at(0x6655, 0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_cpu().get_y().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDY_ABS_ZeroFlag) {
    auto machine = create_machine({LDY_ABS, 0x55, 0x66});
    machine->get_memory().set_at(0x6655, 0x0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDY_ABS_NegativeFlag) {
    // ensure bit 7 set
    auto machine = create_machine({LDY_ABS, 0x55, 0x66});
    machine->get_memory().set_at(0x6655, 0xF6);
    machine->execute();

    ASSERT_EQ(0xF6, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDY_ABS_X) {
    auto machine = create_machine({LDY_ABS_X, 0x55, 0x66});
    machine->get_cpu().get_x().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_cpu().get_y().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(LoadOpcodeHandlerContainer, LDY_ABS_X_ZeroFlag) {
    auto machine = create_machine({LDY_ABS_X, 0x55, 0x66});
    machine->get_cpu().get_x().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0x0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(LoadOpcodeHandlerContainer, LDY_ABS_X_NegativeFlag) {
    // ensure bit 7 set
    auto machine = create_machine({LDY_ABS_X, 0x55, 0x66});
    machine->get_cpu().get_x().set_value(0x4);
    machine->get_memory().set_at(0x6659, 0xF6);
    machine->execute();

    ASSERT_EQ(0xF6, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}
