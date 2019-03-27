#include "gtest/gtest.h"
#include "../src/machine.h"
#include "../src/program.h"

#include <memory>
#include <vector>

using namespace std;

const uint8_t TAX = 0xAA;
const uint8_t TXA = 0x8A;
const uint8_t DEX = 0xCA;
const uint8_t INX = 0xE8;
const uint8_t TAY = 0xA8;
const uint8_t TYA = 0x98;
const uint8_t DEY = 0x88;
const uint8_t INY = 0xC8;

unique_ptr<Machine> rt_get_machine(shared_ptr<vector<uint8_t>> code) {
    auto program = make_shared<Program>(Program(code));
    auto machine = make_unique<Machine>(Machine(program));
    return machine;
}

TEST(RegisterOpcodeHandler, TransferAtoX) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{TAX});
    auto machine = rt_get_machine(code);
    auto reg_man = machine->get_reg_man();

    auto aval = reg_man->get_accumulator()->get_value();
    auto xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0, aval);
    ASSERT_EQ(0, xval);

    machine->execute();
    aval = reg_man->get_accumulator()->get_value();
    xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0, aval);
    ASSERT_EQ(0, xval);

    reg_man->get_program_counter()->set_value(0);
    reg_man->get_accumulator()->set_value(0x3e);
    machine->execute();
    aval = reg_man->get_accumulator()->get_value();
    xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0x3e, aval);
    ASSERT_EQ(0x3e, xval);
}

TEST(RegisterOpcodeHandler, TransferXtoA) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{TXA});
    auto machine = rt_get_machine(code);
    auto reg_man = machine->get_reg_man();

    auto aval = reg_man->get_accumulator()->get_value();
    auto xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0, aval);
    ASSERT_EQ(0, xval);

    machine->execute();
    aval = reg_man->get_accumulator()->get_value();
    xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0, aval);
    ASSERT_EQ(0, xval);

    reg_man->get_program_counter()->set_value(0);
    reg_man->get_x_index()->set_value(0x4f);
    machine->execute();
    aval = reg_man->get_accumulator()->get_value();
    xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0x4f, aval);
    ASSERT_EQ(0x4f, xval);
}

TEST(RegisterOpcodeHandler, DecrementX) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{DEX});
    auto machine = rt_get_machine(code);
    auto reg_man = machine->get_reg_man();

    auto xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0, xval);

    machine->execute();
    xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0xff, xval);

    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0xfe, xval);

    reg_man->get_program_counter()->set_value(0);
    reg_man->get_x_index()->set_value(0x45);
    machine->execute();
    xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0x44, xval);
}

TEST(RegisterOpcodeHandler, IncrementX) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{INX});
    auto machine = rt_get_machine(code);
    auto reg_man = machine->get_reg_man();

    auto xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0, xval);

    machine->execute();
    xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0x01, xval);

    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0x02, xval);

    reg_man->get_program_counter()->set_value(0);
    reg_man->get_x_index()->set_value(0x45);
    machine->execute();
    xval = reg_man->get_x_index()->get_value();
    ASSERT_EQ(0x46, xval);
}

TEST(RegisterOpcodeHandler, TransferAtoY) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{TAY});
    auto machine = rt_get_machine(code);
    auto reg_man = machine->get_reg_man();

    auto aval = reg_man->get_accumulator()->get_value();
    auto yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0, aval);
    ASSERT_EQ(0, yval);

    machine->execute();
    aval = reg_man->get_accumulator()->get_value();
    yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0, aval);
    ASSERT_EQ(0, yval);

    reg_man->get_program_counter()->set_value(0);
    reg_man->get_accumulator()->set_value(0xaf);
    machine->execute();
    aval = reg_man->get_accumulator()->get_value();
    yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0xaf, aval);
    ASSERT_EQ(0xaf, yval);
}

TEST(RegisterOpcodeHandler, TransferYtoA) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{TYA});
    auto machine = rt_get_machine(code);
    auto reg_man = machine->get_reg_man();

    auto aval = reg_man->get_accumulator()->get_value();
    auto yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0, aval);
    ASSERT_EQ(0, yval);

    machine->execute();
    aval = reg_man->get_accumulator()->get_value();
    yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0, aval);
    ASSERT_EQ(0, yval);

    reg_man->get_program_counter()->set_value(0);
    reg_man->get_y_index()->set_value(0xff);
    machine->execute();
    aval = reg_man->get_accumulator()->get_value();
    yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0xff, aval);
    ASSERT_EQ(0xff, yval);
}

TEST(RegisterOpcodeHandler, DecrementY) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{DEY});
    auto machine = rt_get_machine(code);
    auto reg_man = machine->get_reg_man();

    auto yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0, yval);

    machine->execute();
    yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0xff, yval);

    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0xfe, yval);

    reg_man->get_program_counter()->set_value(0);
    reg_man->get_y_index()->set_value(0x3b);
    machine->execute();
    yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0x3a, yval);
}

TEST(RegisterOpcodeHandler, IncrementY) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{INY});
    auto machine = rt_get_machine(code);
    auto reg_man = machine->get_reg_man();

    auto yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0, yval);

    machine->execute();
    yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0x01, yval);

    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0x02, yval);

    reg_man->get_program_counter()->set_value(0);
    reg_man->get_y_index()->set_value(0x3b);
    machine->execute();
    yval = reg_man->get_y_index()->get_value();
    ASSERT_EQ(0x3c, yval);
}
