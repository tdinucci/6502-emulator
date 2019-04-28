#include "gtest/gtest.h"
#include "test-utils.h"

using namespace std;
using namespace emu_6502;

const uint8_t NOP = 0xEA;
const uint8_t LDA_IMM = 0xA9;

TEST(SystemOpcodeHandlerContainer, NOP) {
    auto machine = create_machine({NOP, NOP, NOP, NOP});
    machine->execute();

    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
    ASSERT_EQ(0x604, machine->get_cpu().get_pc().get_value());
}

TEST(SystemOpcodeHandlerContainer, NOP2) {
    auto machine = create_machine({NOP, NOP, NOP, LDA_IMM, 0x35, NOP});
    machine->execute();

    ASSERT_EQ(0x35, machine->get_cpu().get_a().get_value());
    ASSERT_TRUE(are_flags_set(machine->get_cpu().get_ps(), RegisterFlagSet{}));
    ASSERT_EQ(0x606, machine->get_cpu().get_pc().get_value());
}
