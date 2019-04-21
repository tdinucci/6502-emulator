#include "gtest/gtest.h"
#include "test-utils.h"

using namespace std;
using namespace emu_6502;

const uint8_t JMP_ABS = 0x4C;
const uint8_t JMP_IND = 0x6C;

const uint8_t JSR = 0x20;

const uint8_t RTI = 0x40;
const uint8_t RTS = 0x60;

const uint8_t LDA_IMM = 0xA9;

TEST(LoadOpcodeHandlerContainer, JMP_ABS) {
    auto machine = create_machine({JMP_ABS, 0x34, 0x12});

    try {
        machine->execute();
    }
    catch (exception) {
    }

    ASSERT_EQ(0x1234, machine->get_cpu().get_pc().get_value());
}

TEST(LoadOpcodeHandlerContainer, JMP_IND) {
    auto machine = create_machine({JMP_IND, 0x34, 0x12});
    machine->get_memory().set_at(0x1234, 0xF6);
    machine->get_memory().set_at(0x1235, 0xAB);
    try {
        machine->execute();
    }
    catch (exception) {
    }

    ASSERT_EQ(0xABF6, machine->get_cpu().get_pc().get_value());
}

TEST(LoadOpcodeHandlerContainer, JSR) {
    auto machine = create_machine({JSR, 0x34, 0x12});

    try {
        machine->execute();
    }
    catch (exception) {
    }

    ASSERT_EQ(0x1234, machine->get_cpu().get_pc().get_value());
    ASSERT_EQ(3, machine->get_stack().pop());
}

TEST(LoadOpcodeHandlerContainer, RTS) {
    auto machine = create_machine({JSR, 0x07, 0x06, 0x0, 0x0, 0x0, 0x0, LDA_IMM, 0x99, RTS});

    try {
        machine->execute();
    }
    catch (exception) {
    }

    ASSERT_EQ(0x99, machine->get_cpu().get_a().get_value());
    ASSERT_EQ(0x605, machine->get_cpu().get_pc().get_value());
}