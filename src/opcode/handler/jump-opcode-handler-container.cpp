#include "jump-opcode-handler-container.h"
#include "../../utils.h"

namespace emu_6502 {
    JumpOpcodeHandlerContainer::JumpOpcodeHandlerContainer() {
        handlers.insert({Op::JMP_ABS, [this](Machine& machine) { jmp_abs(machine); }});
        handlers.insert({Op::JMP_IND, [this](Machine& machine) { jmp_ind(machine); }});

        handlers.insert({Op::JSR, [this](Machine& machine) { jsr(machine); }});

        handlers.insert({Op::RTI, [this](Machine& machine) { rti(machine); }});
        handlers.insert({Op::RTS, [this](Machine& machine) { rts(machine); }});
    }

    void JumpOpcodeHandlerContainer::jmp_abs(Machine& machine) {
        auto addr = get_abs_address(machine);
        machine.get_cpu().get_pc().set_value(addr);
    }

    void JumpOpcodeHandlerContainer::jmp_ind(Machine& machine) {
        auto addr = get_ind_address(machine);
        machine.get_cpu().get_pc().set_value(addr);
    }

    void JumpOpcodeHandlerContainer::jsr(Machine& machine) {
        uint16_t addr = get_abs_address(machine);

        uint16_t pc_value = machine.get_cpu().get_pc().get_value();
        machine.get_stack().push(pc_value >> 8);
        machine.get_stack().push(pc_value);

        machine.get_cpu().get_pc().set_value(addr);
    }

    void JumpOpcodeHandlerContainer::rti(Machine& machine) {}

    void JumpOpcodeHandlerContainer::rts(Machine& machine) {
        auto low_byte = machine.get_stack().pop();
        auto high_byte = machine.get_stack().pop();

        uint16_t return_address = (high_byte << 8) + low_byte + 1;
        machine.get_cpu().get_pc().set_value(return_address);
    }
}