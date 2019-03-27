#include "gtest/gtest.h"
#include "../src/machine.h"
#include "../src/program.h"

#include <memory>
#include <vector>

using namespace std;

const uint8_t ZERO_PAGE = 0x84;
const uint8_t ZERO_PAGE_X = 0x94;
const uint8_t ABSOLUTE = 0x8C;

unique_ptr<Machine> styt_get_machine(shared_ptr<vector<uint8_t>> code) {
    auto program = make_shared<Program>(Program(code));
    auto machine = make_unique<Machine>(Machine(program));
    return machine;
}

TEST(StyOpcodeHandler, ZeroPage) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ZERO_PAGE, 50});
    auto machine = styt_get_machine(code);
    auto memory = machine->get_memory();
    auto reg_man = machine->get_reg_man();
    auto y_reg = reg_man->get_y_index();

    ASSERT_EQ(0, y_reg->get_value());
    ASSERT_EQ(0, memory->get_byte_at(50));

    y_reg->set_value(0x8a);
    machine->execute();

    ASSERT_EQ(0x8a, memory->get_byte_at(50));
}

TEST(StyOpcodeHandler, ZeroPageX) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ZERO_PAGE_X, 0x45});
    auto machine = styt_get_machine(code);
    auto memory = machine->get_memory();
    auto reg_man = machine->get_reg_man();
    auto x_reg = reg_man->get_x_index();
    auto y_reg = reg_man->get_y_index();

    ASSERT_EQ(0, x_reg->get_value());
    ASSERT_EQ(0, y_reg->get_value());
    ASSERT_EQ(0, memory->get_byte_at(0x5b));

    x_reg->set_value(0x16);
    y_reg->set_value(0xe1);
    machine->execute();

    ASSERT_EQ(0xe1, memory->get_byte_at(0x5b));
}

TEST(StyOpcodeHandler, Absolute) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{ABSOLUTE, 0x33, 0x44});
    auto machine = styt_get_machine(code);
    auto memory = machine->get_memory();
    auto reg_man = machine->get_reg_man();
    auto x_reg = reg_man->get_x_index();
    auto y_reg = reg_man->get_y_index();

    ASSERT_EQ(0, x_reg->get_value());
    ASSERT_EQ(0, y_reg->get_value());
    ASSERT_EQ(0, memory->get_byte_at(0x4433));

    y_reg->set_value(0x9f);
    machine->execute();

    ASSERT_EQ(0x9f, memory->get_byte_at(0x4433));
}
