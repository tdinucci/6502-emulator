#include "gtest/gtest.h"
#include "test-utils.h"

using namespace std;
using namespace emu_6502;

const uint8_t TAX = 0xAA;
const uint8_t TAY = 0xA8;
const uint8_t TSX = 0xBA;
const uint8_t TXA = 0x8A;
const uint8_t TXS = 0x9A;
const uint8_t TYA = 0x98;

TEST(TransferOpcodeHandlerContainer, TAX) {
    auto machine = create_machine({TAX});
    machine->get_cpu().get_a().set_value(0x11);
    machine->execute();

    ASSERT_EQ(0x11, machine->get_cpu().get_x().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(TransferOpcodeHandlerContainer, TAX_ZeroFlag) {
    auto machine = create_machine({TAX});
    machine->get_cpu().get_a().set_value(0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(TransferOpcodeHandlerContainer, TAX_NegativeFlag) {
    auto machine = create_machine({TAX});
    machine->get_cpu().get_a().set_value(0xf0);
    machine->execute();

    ASSERT_EQ(0xf0, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(TransferOpcodeHandlerContainer, TAY) {
    auto machine = create_machine({TAY});
    machine->get_cpu().get_a().set_value(0x11);
    machine->execute();

    ASSERT_EQ(0x11, machine->get_cpu().get_y().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(TransferOpcodeHandlerContainer, TAY_ZeroFlag) {
    auto machine = create_machine({TAY});
    machine->get_cpu().get_a().set_value(0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(TransferOpcodeHandlerContainer, TAY_NegativeFlag) {
    auto machine = create_machine({TAY});
    machine->get_cpu().get_a().set_value(0xf0);
    machine->execute();

    ASSERT_EQ(0xf0, machine->get_cpu().get_y().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(TransferOpcodeHandlerContainer, TSX) {
    auto machine = create_machine({TSX});
    machine->get_cpu().get_sp().set_value(0x11);
    machine->execute();

    ASSERT_EQ(0x11, machine->get_cpu().get_x().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(TransferOpcodeHandlerContainer, TSX_ZeroFlag) {
    auto machine = create_machine({TSX});
    machine->get_cpu().get_sp().set_value(0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(TransferOpcodeHandlerContainer, TSX_NegativeFlag) {
    auto machine = create_machine({TSX});
    machine->get_cpu().get_sp().set_value(0xf0);
    machine->execute();

    ASSERT_EQ(0xf0, machine->get_cpu().get_x().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(TransferOpcodeHandlerContainer, TXA) {
    auto machine = create_machine({TXA});
    machine->get_cpu().get_x().set_value(0x11);
    machine->execute();

    ASSERT_EQ(0x11, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(TransferOpcodeHandlerContainer, TXA_ZeroFlag) {
    auto machine = create_machine({TXA});
    machine->get_cpu().get_x().set_value(0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(TransferOpcodeHandlerContainer, TXA_NegativeFlag) {
    auto machine = create_machine({TXA});
    machine->get_cpu().get_x().set_value(0xf0);
    machine->execute();

    ASSERT_EQ(0xf0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(TransferOpcodeHandlerContainer, TXS) {
    auto machine = create_machine({TXS});
    machine->get_cpu().get_x().set_value(0x11);
    machine->execute();

    ASSERT_EQ(0x11, machine->get_cpu().get_sp().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(TransferOpcodeHandlerContainer, TXS_ZeroFlag) {
    auto machine = create_machine({TXS});
    machine->get_cpu().get_x().set_value(0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_sp().get_value());

    // flags not affected with this op
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(TransferOpcodeHandlerContainer, TXS_NegativeFlag) {
    auto machine = create_machine({TXS});
    machine->get_cpu().get_x().set_value(0xf0);
    machine->execute();

    ASSERT_EQ(0xf0, machine->get_cpu().get_sp().get_value());
    // flags not affected with this op
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(TransferOpcodeHandlerContainer, TYA) {
    auto machine = create_machine({TYA});
    machine->get_cpu().get_y().set_value(0x11);
    machine->execute();

    ASSERT_EQ(0x11, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(TransferOpcodeHandlerContainer, TYA_ZeroFlag) {
    auto machine = create_machine({TYA});
    machine->get_cpu().get_y().set_value(0);
    machine->execute();

    ASSERT_EQ(0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(TransferOpcodeHandlerContainer, TYA_NegativeFlag) {
    auto machine = create_machine({TYA});
    machine->get_cpu().get_y().set_value(0xf0);
    machine->execute();

    ASSERT_EQ(0xf0, machine->get_cpu().get_a().get_value());

    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}