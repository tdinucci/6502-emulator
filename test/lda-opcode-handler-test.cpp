#include "gtest/gtest.h"
#include "../src/machine.h"
#include "../src/program.h"
#include "../src/opcode/handler/lda-opcode-handler.h"

#include <memory>
#include <vector>

using namespace std;

const uint8_t IMMEDIATE = 0xA9;
const uint8_t ZERO_PAGE = 0xA5;
const uint8_t ZERO_PAGE_X = 0xB5;
const uint8_t ABSOLUTE = 0xAD;
const uint8_t ABSOLUTE_X = 0xBD;
const uint8_t ABSOLUTE_Y = 0xB9;
const uint8_t INDIRECT_X = 0xA1;
const uint8_t INDIRECT_Y = 0xB1;

unique_ptr<Machine> ldat_get_machine(shared_ptr<vector<uint8_t>> code) {
    auto program = make_shared<Program>(Program(code));
    auto machine = make_unique<Machine>(Machine(program));
    return machine;
}

TEST(LdaOpcodeHandler, Immediate) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{IMMEDIATE, 36});
    auto machine = ldat_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto accumulator = reg_man->get_accumulator();

    ASSERT_EQ(0, accumulator->get_value());

    machine->execute();

    ASSERT_EQ(36, accumulator->get_value());
}

TEST(LdaOpcodeHandler, ZeroPage) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ZERO_PAGE, 123});
    auto machine = ldat_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto accumulator = reg_man->get_accumulator();

    ASSERT_EQ(0, accumulator->get_value());

    machine->get_memory()->set_byte_at(123, 78);
    machine->execute();

    ASSERT_EQ(78, accumulator->get_value());
}

TEST(LdaOpcodeHandler, ZeroPageX) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ZERO_PAGE_X, 0x50});
    auto machine = ldat_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto accumulator = reg_man->get_accumulator();
    auto x_reg = reg_man->get_x_index();

    ASSERT_EQ(0, accumulator->get_value());
    ASSERT_EQ(0, x_reg->get_value());
    machine->get_memory()->set_byte_at(0x50, 0xff);
    machine->execute();
    ASSERT_EQ(0xff, accumulator->get_value());

    x_reg->set_value(0x15);
    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    ASSERT_EQ(0, accumulator->get_value());

    machine->get_memory()->set_byte_at(0x65, 233);
    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    ASSERT_EQ(233, accumulator->get_value());
}

TEST(LdaOpcodeHandler, ZeroPageXWrap) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ZERO_PAGE_X, 0x80});
    auto machine = ldat_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto accumulator = reg_man->get_accumulator();
    auto x_reg = reg_man->get_x_index();

    ASSERT_EQ(0, accumulator->get_value());
    ASSERT_EQ(0, x_reg->get_value());

    x_reg->set_value(0xff);
    machine->get_memory()->set_byte_at(0x7f, 0x12);
    machine->execute();
    ASSERT_EQ(0x12, accumulator->get_value());
}

TEST(LdaOpcodeHandler, Absolute) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ABSOLUTE, 0xe5, 0xff});
    auto machine = ldat_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto accumulator = reg_man->get_accumulator();

    ASSERT_EQ(0, accumulator->get_value());

    machine->get_memory()->set_byte_at(0xffe5, 0xde);
    machine->execute();

    ASSERT_EQ(0xde, accumulator->get_value());
}

TEST(LdaOpcodeHandler, AbsoluteX) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ABSOLUTE_X, 0x33, 0xc2});
    auto machine = ldat_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto accumulator = reg_man->get_accumulator();
    auto x_reg = reg_man->get_x_index();

    ASSERT_EQ(0, accumulator->get_value());
    ASSERT_EQ(0, x_reg->get_value());
    machine->get_memory()->set_byte_at(0xc233, 0xc8);
    machine->execute();
    ASSERT_EQ(0xc8, accumulator->get_value());

    x_reg->set_value(0x55);
    machine->get_memory()->set_byte_at(0xc233 + 0x55, 0xab);
    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    ASSERT_EQ(0xab, accumulator->get_value());
}

TEST(LdaOpcodeHandler, AbsoluteY) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ABSOLUTE_Y, 0x33, 0xc2});
    auto machine = ldat_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto accumulator = reg_man->get_accumulator();
    auto y_reg = reg_man->get_y_index();

    ASSERT_EQ(0, accumulator->get_value());
    ASSERT_EQ(0, y_reg->get_value());
    machine->get_memory()->set_byte_at(0xc233, 0xc8);
    machine->execute();
    ASSERT_EQ(0xc8, accumulator->get_value());

    y_reg->set_value(0x55);
    machine->get_memory()->set_byte_at(0xc233 + 0x55, 0xab);
    reg_man->get_program_counter()->set_value(0);
    machine->execute();
    ASSERT_EQ(0xab, accumulator->get_value());
}

TEST(LdaOpcodeHandler, IndirectX) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{INDIRECT_X, 0x00});
    auto machine = ldat_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto accumulator = reg_man->get_accumulator();
    auto x_reg = reg_man->get_x_index();

    ASSERT_EQ(0, accumulator->get_value());

    x_reg->set_value(0x01);
    machine->get_memory()->set_byte_at(0x01, 0x05);
    machine->get_memory()->set_byte_at(0x02, 0x07);
    machine->get_memory()->set_byte_at(0x0705, 0xc6);
    machine->execute();
    ASSERT_EQ(0xc6, accumulator->get_value());

    code->at(1) = 0x15;
    reg_man->get_program_counter()->set_value(0);

    x_reg->set_value(0x20);
    machine->get_memory()->set_byte_at(0x35, 0xef);
    machine->get_memory()->set_byte_at(0x36, 0xa8);
    machine->get_memory()->set_byte_at(0xa8ef, 0x9d);
    machine->execute();
    ASSERT_EQ(0x9d, accumulator->get_value());
}

TEST(LdaOpcodeHandler, IndirectY) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{INDIRECT_Y, 0x00});
    auto machine = ldat_get_machine(code);
    auto reg_man = machine->get_reg_man();
    auto accumulator = reg_man->get_accumulator();
    auto y_reg = reg_man->get_y_index();

    ASSERT_EQ(0, accumulator->get_value());

    y_reg->set_value(0x00);
    machine->get_memory()->set_byte_at(0x00, 0x25);
    machine->get_memory()->set_byte_at(0x01, 0x3e);
    machine->get_memory()->set_byte_at(0x3e25, 0xf0);
    machine->execute();
    ASSERT_EQ(0xf0, accumulator->get_value());

    code->at(1) = 0x15;
    reg_man->get_program_counter()->set_value(0);

    y_reg->set_value(0x25);
    machine->get_memory()->set_byte_at(0x15, 0x20);
    machine->get_memory()->set_byte_at(0x16, 0x07);
    machine->get_memory()->set_byte_at(0x0745, 0x89);
    machine->execute();
    ASSERT_EQ(0x89, accumulator->get_value());
}