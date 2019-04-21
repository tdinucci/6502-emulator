#include "gtest/gtest.h"
#include "test-utils.h"

using namespace std;
using namespace emu_6502;

const uint8_t PHA = 0x48;
const uint8_t PHP = 0x08;
const uint8_t PLA = 0x68;
const uint8_t PLP = 0x28;

const uint8_t CLC = 0x18;
const uint8_t CLD = 0xD8;
const uint8_t CLI = 0x58;
const uint8_t CLV = 0xB8;

TEST(StackOpcodeHandlerContainer, PHA) {
    auto machine = create_machine({PHA});
    machine->get_cpu().get_a().set_value(0x13);
    machine->execute();

    ASSERT_EQ(0x13, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(0x13, machine->get_stack().pop());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StackOpcodeHandlerContainer, PHP) {
    auto machine = create_machine({PHP});
    machine->get_cpu().get_ps().set_value(0xFF);
    machine->execute();

    ASSERT_EQ(0xFF, machine->get_cpu().get_ps().get_value().to_ulong());
    ASSERT_EQ(0xFF, machine->get_stack().pop());
}

TEST(StackOpcodeHandlerContainer, PLA) {
    auto machine = create_machine({PLA});
    machine->get_stack().push(0x05);
    machine->execute();

    ASSERT_EQ(0x05, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
}

TEST(StackOpcodeHandlerContainer, PLA_NegativeFlag) {
    auto machine = create_machine({PLA});
    machine->get_stack().push(0xf5);
    machine->execute();

    ASSERT_EQ(0xf5, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.negative = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(StackOpcodeHandlerContainer, PLA_ZeroFlag) {
    auto machine = create_machine({PLA});
    machine->get_stack().push(0x0);
    machine->execute();

    ASSERT_EQ(0x0, machine->get_cpu().get_a().get_value());
    RegisterFlagSet flags{};
    flags.zero = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}

TEST(StackOpcodeHandlerContainer, PLP) {
    auto machine = create_machine({PHP, CLC, CLD, CLI, CLV, PLP});

    auto& ps = machine->get_cpu().get_ps();
    ps.set_zero(true);
    ps.set_negative(true);
    ps.set_carry(true);
    ps.set_overflow(true);
    ps.set_interupt_disable(true);
    ps.set_decimal(true);
    ps.set_break(true);

    machine->execute();

    RegisterFlagSet flags{};
    flags.zero = true;
    flags.negative = true;
    flags.carry = true;
    flags.overflow = true;
    flags.interupt_disable = true;
    flags.decimal = true;
    flags.brk = true;
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), flags));
}
