#include "gtest/gtest.h"
#include "../src/machine.h"
#include "../src/program.h"
#include "../src/opcode/handler/stack-opcode-handler.h"

#include <memory>
#include <vector>

using namespace std;

const uint8_t IMMEDIATE = 0xA2;
const uint8_t ZERO_PAGE = 0xA6;
const uint8_t ZERO_PAGE_Y = 0xB6;
const uint8_t ABSOLUTE = 0xAE;
const uint8_t ABSOLUTE_Y = 0xBE;

unique_ptr<Machine> ldxt_get_machine(shared_ptr<vector<uint8_t>> code) {
    auto program = make_shared<Program>(Program(code));
    auto machine = make_unique<Machine>(Machine(program));
    return machine;
}

TEST(LdxOpcodeHandler, Immediate) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{IMMEDIATE, 36});
    auto machine = ldxt_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto x_reg = reg_man->get_x_index();

    ASSERT_EQ(0, x_reg->get_value());

    machine->execute();

    ASSERT_EQ(36, x_reg->get_value());
}

TEST(LdxOpcodeHandler, ZeroPage) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ZERO_PAGE, 123});
    auto machine = ldxt_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto x_reg = reg_man->get_x_index();

    ASSERT_EQ(0, x_reg->get_value());

    machine->get_memory()->set_byte_at(123, 78);
    machine->execute();

    ASSERT_EQ(78, x_reg->get_value());
}

TEST(LdxOpcodeHandler, ZeroPageY) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ZERO_PAGE_Y, 250});
    auto machine = ldxt_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto x_reg = reg_man->get_x_index();
    auto y_reg = reg_man->get_y_index();

    ASSERT_EQ(0, x_reg->get_value());
    ASSERT_EQ(0, y_reg->get_value());
    machine->get_memory()->set_byte_at(250, 255);
    machine->execute();
    ASSERT_EQ(255, x_reg->get_value());

    reg_man->get_y_index()->set_value(100);
    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    ASSERT_EQ(0, x_reg->get_value());

    machine->get_memory()->set_byte_at(350, 233);
    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    ASSERT_EQ(233, x_reg->get_value());
}

TEST(LdxOpcodeHandler, Absolute) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ABSOLUTE, 0xe5, 0xff});
    auto machine = ldxt_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto x_reg = reg_man->get_x_index();

    ASSERT_EQ(0, x_reg->get_value());

    machine->get_memory()->set_byte_at(0xffe5, 0xde);
    machine->execute();

    ASSERT_EQ(0xde, x_reg->get_value());
}

TEST(LdxOpcodeHandler, AbsoluteY) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ABSOLUTE_Y, 0x33, 0xc2});
    auto machine = ldxt_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto x_reg = reg_man->get_x_index();
    auto y_reg = reg_man->get_y_index();

    ASSERT_EQ(0, x_reg->get_value());
    ASSERT_EQ(0, y_reg->get_value());
    machine->get_memory()->set_byte_at(0xc233, 0xc8);
    machine->execute();
    ASSERT_EQ(0xc8, x_reg->get_value());

    y_reg->set_value(0x55);
    machine->get_memory()->set_byte_at(0xc233 + 0x55, 0xab);
    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    ASSERT_EQ(0xab, x_reg->get_value());
}