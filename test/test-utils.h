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

unique_ptr<Machine> create_machine(vector<uint8_t> code) {
    auto machine = make_unique<Machine>();
    machine->load(code, 0x600);

    return machine;
}

bool are_flags_set(const StatusRegister& reg, const RegisterFlagSet& flags) {
    return
            flags.carry == reg.is_carry_set() &&
            flags.zero == reg.is_zero_set() &&
            flags.interupt_disable == reg.is_interupt_disable_set() &&
            flags.decimal == reg.is_interupt_disable_set() &&
            flags.brk == reg.is_break_set() &&
            flags.overflow == reg.is_overflow_set() &&
            flags.negative == reg.is_negative_set();
}