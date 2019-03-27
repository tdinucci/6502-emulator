#include "gtest/gtest.h"
#include "../src/machine.h"
#include "../src/program.h"
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

const uint8_t CLC = 0x18;
const uint8_t SEC = 0x38;
const uint8_t CLI = 0x58;
const uint8_t SEI = 0x78;
const uint8_t CLV = 0xB8;
const uint8_t CLD = 0xD8;
const uint8_t SED = 0xF8;

unique_ptr<Machine> ft_get_machine(shared_ptr<vector<uint8_t>> code){
    auto program = make_shared<Program>(Program(code));
    auto machine = make_unique<Machine>(Machine(program));
    return machine;
}

TEST(FlagOpcodeHandlerTest, ClearCarry) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{CLC});
    auto machine = ft_get_machine(code);
    auto status = machine->get_reg_man()->get_status_register();

    ASSERT_EQ(0, status->is_carry_set());

    status->set_carry(true);
    ASSERT_EQ(1, status->is_carry_set());

    machine->execute();
    ASSERT_EQ(0, status->is_carry_set());
}

TEST(FlagOpcodeHandlerTest, SetCarry) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{SEC});
    auto machine = ft_get_machine(code);
    auto status = machine->get_reg_man()->get_status_register();

    ASSERT_EQ(0, status->is_carry_set());

    machine->execute();
    ASSERT_EQ(1, status->is_carry_set());
}

TEST(FlagOpcodeHandlerTest, ClearInteruptDisable) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{CLI});
    auto machine = ft_get_machine(code);
    auto status = machine->get_reg_man()->get_status_register();

    ASSERT_EQ(0, status->is_interupt_disable_set());

    status->set_interupt_disable(true);
    ASSERT_EQ(1, status->is_interupt_disable_set());

    machine->execute();
    ASSERT_EQ(0, status->is_interupt_disable_set());
}

TEST(FlagOpcodeHandlerTest, SetInteruptDisable) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{SEI});
    auto machine = ft_get_machine(code);
    auto status = machine->get_reg_man()->get_status_register();

    ASSERT_EQ(0, status->is_interupt_disable_set());

    machine->execute();
    ASSERT_EQ(1, status->is_interupt_disable_set());
}

TEST(FlagOpcodeHandlerTest, ClearOverflow) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{CLV});
    auto machine = ft_get_machine(code);
    auto status = machine->get_reg_man()->get_status_register();

    ASSERT_EQ(0, status->is_overflow_set());

    status->set_overflow(true);
    ASSERT_EQ(1, status->is_overflow_set());

    machine->execute();
    ASSERT_EQ(0, status->is_overflow_set());
}

TEST(FlagOpcodeHandlerTest, ClearDecimal) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{CLD});
    auto machine = ft_get_machine(code);
    auto status = machine->get_reg_man()->get_status_register();

    ASSERT_EQ(0, status->is_decimal_set());

    status->set_decimal(true);
    ASSERT_EQ(1, status->is_decimal_set());

    machine->execute();
    ASSERT_EQ(0, status->is_decimal_set());
}

TEST(FlagOpcodeHandlerTest, SetDecimal) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{SED});
    auto machine = ft_get_machine(code);
    auto status = machine->get_reg_man()->get_status_register();

    ASSERT_EQ(0, status->is_decimal_set());

    machine->execute();
    ASSERT_EQ(1, status->is_decimal_set());
}
