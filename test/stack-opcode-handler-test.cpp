#include "gtest/gtest.h"
#include "../src/machine.h"
#include "../src/program.h"
#include "../src/opcode/handler/stack-opcode-handler.h"

#include <memory>
#include <vector>

using namespace std;

const uint8_t PHA = 0x48;
const uint8_t PLA = 0x68;
const uint8_t PHP = 0x08;
const uint8_t PLP = 0x28;

unique_ptr<Machine> st_get_machine(shared_ptr<vector<uint8_t>> code) {
    auto program = make_shared<Program>(Program(code));
    auto machine = make_unique<Machine>(Machine(program));
    return machine;
}

TEST(StackOpcodeHandler, PushAccumulator) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{PHA});
    auto machine = st_get_machine(code);
    auto reg_man = machine->get_reg_man();

    reg_man->get_accumulator()->set_value(0x8b);
    ASSERT_EQ(0x8b, reg_man->get_accumulator()->get_value());

    // stack is empty
    ASSERT_THROW(machine->get_memory()->stack_pop(), runtime_error);

    machine->execute();

    ASSERT_EQ(0x8b, reg_man->get_accumulator()->get_value());
    auto stack_value = machine->get_memory()->stack_pop();

    ASSERT_EQ(0x8b, stack_value);

    // stack is empty again
    ASSERT_THROW(machine->get_memory()->stack_pop(), runtime_error);
}

TEST(StackOpcodeHandler, PullAccumulator) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{PLA});
    auto machine = st_get_machine(code);
    auto reg_man = machine->get_reg_man();

    machine->get_memory()->stack_push(1);
    machine->get_memory()->stack_push(2);
    machine->get_memory()->stack_push(3);

    machine->execute();
    ASSERT_EQ(3, reg_man->get_accumulator()->get_value());

    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    ASSERT_EQ(2, reg_man->get_accumulator()->get_value());

    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    ASSERT_EQ(1, reg_man->get_accumulator()->get_value());

    // stack is empty
    ASSERT_THROW(machine->get_memory()->stack_pop(), runtime_error);
}

TEST(StackOpcodeHandler, PushStatus) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{PHP});
    auto machine = st_get_machine(code);
    auto reg_man = machine->get_reg_man();

    reg_man->get_status_register()->set_value(255);
    ASSERT_EQ(255, reg_man->get_status_register()->get_value().to_ulong());

    // stack is empty
    ASSERT_THROW(machine->get_memory()->stack_pop(), runtime_error);

    machine->execute();

    ASSERT_EQ(255, reg_man->get_status_register()->get_value().to_ulong());
    auto stack_value = machine->get_memory()->stack_pop();

    ASSERT_EQ(255, stack_value);

    // stack is empty again
    ASSERT_THROW(machine->get_memory()->stack_pop(), runtime_error);
}

TEST(StackOpcodeHandler, PullStatus) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{PLP});
    auto machine = st_get_machine(code);
    auto reg_man = machine->get_reg_man();

    machine->get_memory()->stack_push(8);
    machine->get_memory()->stack_push(16);
    machine->get_memory()->stack_push(32);

    machine->execute();
    ASSERT_EQ(32, reg_man->get_status_register()->get_value().to_ulong());

    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    ASSERT_EQ(16, reg_man->get_status_register()->get_value().to_ulong());

    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    ASSERT_EQ(8, reg_man->get_status_register()->get_value().to_ulong());

    // stack is empty
    ASSERT_THROW(machine->get_memory()->stack_pop(), runtime_error);
}