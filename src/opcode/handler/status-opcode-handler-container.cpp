#include "status-opcode-handler-container.h"

namespace emu_6502 {
    StatusOpcodeHandlerContainer::StatusOpcodeHandlerContainer() {
        handlers.insert({Op::CLC, [this](Machine& machine) { clc(machine); }});
        handlers.insert({Op::CLD, [this](Machine& machine) { cld(machine); }});
        handlers.insert({Op::CLI, [this](Machine& machine) { cli(machine); }});
        handlers.insert({Op::CLV, [this](Machine& machine) { clv(machine); }});

        handlers.insert({Op::SEC, [this](Machine& machine) { sec(machine); }});
        handlers.insert({Op::SED, [this](Machine& machine) { sed(machine); }});
        handlers.insert({Op::SEI, [this](Machine& machine) { sei(machine); }});
    }

    void StatusOpcodeHandlerContainer::clc(Machine& machine) {
        machine.get_cpu().get_ps().set_carry(false);
    }

    void StatusOpcodeHandlerContainer::cld(Machine& machine) {
        machine.get_cpu().get_ps().set_decimal(false);
    }

    void StatusOpcodeHandlerContainer::cli(Machine& machine) {
        machine.get_cpu().get_ps().set_interupt_disable(false);
    }

    void StatusOpcodeHandlerContainer::clv(Machine& machine) {
        machine.get_cpu().get_ps().set_overflow(false);
    }

    void StatusOpcodeHandlerContainer::sec(Machine& machine) {
        machine.get_cpu().get_ps().set_carry(true);
    }

    void StatusOpcodeHandlerContainer::sed(Machine& machine) {
        machine.get_cpu().get_ps().set_decimal(true);
    }

    void StatusOpcodeHandlerContainer::sei(Machine& machine) {
        machine.get_cpu().get_ps().set_interupt_disable(true);
    }
}