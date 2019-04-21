#include "gtest/gtest.h"
#include "test-utils.h"

using namespace std;
using namespace emu_6502;

const uint8_t CLC = 0x18;
const uint8_t CLD = 0xD8;
const uint8_t CLI = 0x58;
const uint8_t CLV = 0xB8;
const uint8_t SEC = 0x38;
const uint8_t SED = 0xF8;
const uint8_t SEI = 0x78;

TEST(StatusOpcodeHandlerContainer, CLC) {
    auto machine = create_machine({CLC});
    auto& ps = machine->get_cpu().get_ps();
    ps.set_carry(true);

    ASSERT_TRUE(ps.is_carry_set());
    machine->execute();
    ASSERT_FALSE(ps.is_carry_set());
}

TEST(StatusOpcodeHandlerContainer, CLD) {
    auto machine = create_machine({CLD});
    auto& ps = machine->get_cpu().get_ps();
    ps.set_decimal(true);

    ASSERT_TRUE(ps.is_decimal_set());
    machine->execute();
    ASSERT_FALSE(ps.is_decimal_set());
}

TEST(StatusOpcodeHandlerContainer, CLI) {
    auto machine = create_machine({CLI});
    auto& ps = machine->get_cpu().get_ps();
    ps.set_interupt_disable(true);

    ASSERT_TRUE(ps.is_interupt_disable_set());
    machine->execute();
    ASSERT_FALSE(ps.is_interupt_disable_set());
}

TEST(StatusOpcodeHandlerContainer, CLV) {
    auto machine = create_machine({CLV});
    auto& ps = machine->get_cpu().get_ps();
    ps.set_overflow(true);

    ASSERT_TRUE(ps.is_overflow_set());
    machine->execute();
    ASSERT_FALSE(ps.is_overflow_set());
}

TEST(StatusOpcodeHandlerContainer, SEC) {
    auto machine = create_machine({SEC});
    auto& ps = machine->get_cpu().get_ps();

    ASSERT_FALSE(ps.is_carry_set());
    machine->execute();
    ASSERT_TRUE(ps.is_carry_set());
}

TEST(StatusOpcodeHandlerContainer, SED) {
    auto machine = create_machine({SED});
    auto& ps = machine->get_cpu().get_ps();

    ASSERT_FALSE(ps.is_decimal_set());
    machine->execute();
    ASSERT_TRUE(ps.is_decimal_set());
}

TEST(StatusOpcodeHandlerContainer, SEI) {
    auto machine = create_machine({SEI});
    auto& ps = machine->get_cpu().get_ps();

    ASSERT_FALSE(ps.is_interupt_disable_set());
    machine->execute();
    ASSERT_TRUE(ps.is_interupt_disable_set());
}
