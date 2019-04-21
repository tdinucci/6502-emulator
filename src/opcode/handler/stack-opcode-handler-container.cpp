#include "stack-opcode-handler-container.h"
#include "../../utils.h"

namespace emu_6502 {
    StackOpcodeHandlerContainer::StackOpcodeHandlerContainer() {
        handlers.insert({Op::PHA, [this](Machine& machine) { pha(machine); }});
        handlers.insert({Op::PHP, [this](Machine& machine) { php(machine); }});

        handlers.insert({Op::PLA, [this](Machine& machine) { pla(machine); }});
        handlers.insert({Op::PLP, [this](Machine& machine) { plp(machine); }});
    }

    void StackOpcodeHandlerContainer::pha(Machine& machine) {
        machine.get_stack().push(machine.get_cpu().get_a().get_value());
    }

    void StackOpcodeHandlerContainer::php(Machine& machine) {
        machine.get_stack().push(machine.get_cpu().get_ps().get_value().to_ulong());
    }

    void StackOpcodeHandlerContainer::pla(Machine& machine) {
        auto value = machine.get_stack().pop();
        machine.get_cpu().get_a().set_value(value);
        set_zero_and_neg_flags(machine.get_cpu().get_ps(), value);
    }

    void StackOpcodeHandlerContainer::plp(Machine& machine) {
        machine.get_cpu().get_ps().set_value(machine.get_stack().pop());
    }
}