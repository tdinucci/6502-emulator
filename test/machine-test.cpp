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

const uint8_t LDX_IMMEDIATE = 0xA9;

TEST(Machine, Execute) {
    auto code = make_shared<vector<uint8_t>>(vector<uint8_t>{SEC, SEI, SED, CLI, CLV, CLD, CLC, LDX_IMMEDIATE, 0x6B});
    auto program = make_shared<Program>(Program(code));
    auto machine = make_unique<Machine>(Machine(program));

    machine->execute();
}
