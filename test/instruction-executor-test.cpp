#include "gtest/gtest.h"
#include "../src/program.h"
#include "../src/instruction/instruction-executor.h"
#include "../src/register/register-manager.h"
#include "../src/opcode/opcode-handler-directory.h"
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

const uint8_t CLC = 0x18;
const uint8_t SEC = 0x38;

const uint8_t LDX_IMMEDIATE = 0xA9;

TEST(InstructionExecutor, Execute) {
    auto reg_man = make_shared<RegisterManager>(RegisterManager());
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>
            {SEC,
             CLC
            });
    auto program = make_shared<Program>(Program(code));
    auto memory = make_shared<Memory>(Memory());
    auto opcode_handler_dir = make_shared<OpcodeHandlerDirectory>(OpcodeHandlerDirectory(program, reg_man, memory));
    auto executor = make_unique<InstructionExecutor>(InstructionExecutor(program, reg_man, opcode_handler_dir));

    executor->execute();
}
