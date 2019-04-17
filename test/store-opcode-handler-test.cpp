#include "gtest/gtest.h"
#include "test-utils.h"

using namespace std;
using namespace emu_6502;

const uint8_t STA_ZPG = 0x85;
const uint8_t STA_ZPG_X = 0x95;
const uint8_t STA_ABS = 0x8D;
const uint8_t STA_ABS_X = 0x9D;
const uint8_t STA_ABS_Y = 0x99;
const uint8_t STA_IND_X = 0x81;
const uint8_t STA_IND_Y = 0x91;

const uint8_t STX_ZPG = 0x86;
const uint8_t STX_ZPG_Y = 0x96;
const uint8_t STX_ABS = 0x8E;

const uint8_t STY_ZPG = 0x84;
const uint8_t STY_ZPG_X = 0x94;
const uint8_t STY_ABS = 0x8C;

TEST(StoreOpcodeHandlerContainer, STA_ZPG) {
    auto machine = create_machine({STA_ZPG, 0xe5});
    machine->get_cpu().get_a().set_value(0x9d);
    machine->execute();

    ASSERT_EQ(0x9d, machine->get_memory().get_at(0xe5));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STA_ZPG_FlagsUnaffected) {
    auto machine = create_machine({STA_ZPG, 0xe5});
    machine->get_cpu().get_a().set_value(0x9d);

    auto& ps = machine->get_cpu().get_ps();
    ps.set_overflow(true);
    ps.set_zero(true);
    ps.set_negative(true);
    ps.set_carry(true);
    ps.set_break(true);
    ps.set_decimal(true);
    ps.set_interupt_disable(true);

    machine->execute();

    ASSERT_EQ(0x9d, machine->get_memory().get_at(0xe5));

    RegisterFlagSet flags{};
    flags.overflow = true;
    flags.zero = true;
    flags.negative = true;
    flags.carry = true;
    flags.brk = true;
    flags.decimal = true;
    flags.interupt_disable = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(StoreOpcodeHandlerContainer, STA_ZPG_X) {
    auto machine = create_machine({STA_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x15);
    machine->get_cpu().get_a().set_value(0x4f);
    machine->execute();

    ASSERT_EQ(0x4f, machine->get_memory().get_at(0x25));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STA_ZPG_X_Wrap) {
    auto machine = create_machine({STA_ZPG_X, 0xFF});
    machine->get_cpu().get_x().set_value(0x80);
    machine->get_cpu().get_a().set_value(0x4f);
    machine->execute();

    ASSERT_EQ(0x4f, machine->get_memory().get_at(0x7F));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STA_ABS) {
    auto machine = create_machine({STA_ABS, 0x55, 0x66});
    machine->get_cpu().get_a().set_value(0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_memory().get_at(0x6655));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STA_ABS_X) {
    auto machine = create_machine({STA_ABS_X, 0x55, 0x66});
    machine->get_cpu().get_x().set_value(0x4);
    machine->get_cpu().get_a().set_value(0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_memory().get_at(0x6659));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STA_ABS_Y) {
    auto machine = create_machine({STA_ABS_Y, 0x55, 0x66});
    machine->get_cpu().get_y().set_value(0x4);
    machine->get_cpu().get_a().set_value(0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_memory().get_at(0x6659));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STA_IND_X) {
    auto machine = create_machine({STA_IND_X, 0x55});
    machine->get_cpu().get_x().set_value(0x4);
    machine->get_cpu().get_a().set_value(0x33);

    // pointer
    machine->get_memory().set_at(0x59, 0x3c);
    machine->get_memory().set_at(0x5A, 0x4d);

    machine->execute();

    ASSERT_EQ(0x33, machine->get_memory().get_at(0x4d3c));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STA_IND_X_Wrap) {
    auto machine = create_machine({STA_IND_X, 0xFF});
    machine->get_cpu().get_x().set_value(0x6b);
    machine->get_cpu().get_a().set_value(0x33);

    // pointer
    machine->get_memory().set_at(0x6a, 0x3c);
    machine->get_memory().set_at(0x6b, 0x4d);

    machine->execute();

    ASSERT_EQ(0x33, machine->get_memory().get_at(0x4d3c));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STA_IND_Y) {
    auto machine = create_machine({STA_IND_Y, 0x55});
    machine->get_memory().set_at(0x55, 0x12);
    machine->get_memory().set_at(0x56, 0x34);

    machine->get_cpu().get_y().set_value(0x1a);
    machine->get_cpu().get_a().set_value(0x33);

    machine->execute();

    ASSERT_EQ(0x33, machine->get_memory().get_at(0x342c));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STX_ZPG) {
    auto machine = create_machine({STX_ZPG, 123});
    machine->get_cpu().get_x().set_value(78);
    machine->execute();

    ASSERT_EQ(78, machine->get_memory().get_at(123));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STX_ZPG_Y) {
    auto machine = create_machine({STX_ZPG_Y, 0x10});
    machine->get_cpu().get_y().set_value(0x15);
    machine->get_cpu().get_x().set_value(78);
    machine->execute();

    ASSERT_EQ(78, machine->get_memory().get_at(0x25));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STX_ZPG_Y_Wrap) {
    auto machine = create_machine({STX_ZPG_Y, 0xFF});
    machine->get_cpu().get_y().set_value(0x80);
    machine->get_cpu().get_x().set_value(78);
    machine->execute();

    ASSERT_EQ(78, machine->get_memory().get_at(0x7F));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STX_ABS) {
    auto machine = create_machine({STX_ABS, 0x55, 0x66});
    machine->get_cpu().get_x().set_value(0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_memory().get_at(0x6655));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STY_ZPG) {
    auto machine = create_machine({STY_ZPG, 123});
    machine->get_cpu().get_y().set_value(78);
    machine->execute();

    ASSERT_EQ(78, machine->get_memory().get_at(123));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STY_ZPG_X) {
    auto machine = create_machine({STY_ZPG_X, 0x10});
    machine->get_cpu().get_x().set_value(0x15);
    machine->get_cpu().get_y().set_value(78);
    machine->execute();

    ASSERT_EQ(78, machine->get_memory().get_at(0x25));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STY_ZPG_X_Wrap) {
    auto machine = create_machine({STY_ZPG_X, 0xFF});
    machine->get_cpu().get_x().set_value(0x80);
    machine->get_cpu().get_y().set_value(78);
    machine->execute();

    ASSERT_EQ(78, machine->get_memory().get_at(0x7F));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StoreOpcodeHandlerContainer, STY_ABS) {
    auto machine = create_machine({STY_ABS, 0x55, 0x66});
    machine->get_cpu().get_y().set_value(0x10);
    machine->execute();

    ASSERT_EQ(0x10, machine->get_memory().get_at(0x6655));
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

