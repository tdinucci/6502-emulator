#ifndef INC_6502_EMULATOR_TEST_UTILS_H
#define INC_6502_EMULATOR_TEST_UTILS_H

#include "../src/opcode/opcode-handler-directory.h"
#include "../src/machine/status-register.h"

#include <memory>
#include <vector>

using namespace std;
using namespace emu_6502;

struct RegisterFlagSet {
    bool carry;
    bool zero;
    bool interupt_disable;
    bool decimal;
    bool brk;
    bool overflow;
    bool negative;
};

unique_ptr<Machine> create_machine(vector<uint8_t> code);
bool are_flags_set(const StatusRegister& reg, const RegisterFlagSet& flags);

#endif