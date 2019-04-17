#include "transfer-opcode-handler-container.h"

namespace emu_6502 {

    TransferOpcodeHandlerContainer::TransferOpcodeHandlerContainer() : OpcodeHandlerContainer() {
        handlers.insert({Op::TAX, [this](Machine& machine) {
            transfer(machine, machine.get_cpu().get_a(), machine.get_cpu().get_x());
        }});

        handlers.insert({Op::TAY, [this](Machine& machine) {
            transfer(machine, machine.get_cpu().get_a(), machine.get_cpu().get_y());
        }});

        handlers.insert({Op::TSX, [this](Machine& machine) {
            transfer(machine, machine.get_cpu().get_sp(), machine.get_cpu().get_x());
        }});

        handlers.insert({Op::TXA, [this](Machine& machine) {
            transfer(machine, machine.get_cpu().get_x(), machine.get_cpu().get_a());
        }});

        handlers.insert({Op::TXS, [this](Machine& machine) {
            transfer(machine, machine.get_cpu().get_x(), machine.get_cpu().get_sp(), true);
        }});

        handlers.insert({Op::TYA, [this](Machine& machine) {
            transfer(machine, machine.get_cpu().get_y(), machine.get_cpu().get_a());
        }});
    }

    void TransferOpcodeHandlerContainer::transfer(Machine& machine, const Register<uint8_t>& source,
                                                  Register<uint8_t>& dest, bool ignoreFlags) {
        auto value = source.get_value();
        dest.set_value(value);

        if (!ignoreFlags) {
            auto& ps = machine.get_cpu().get_ps();
            ps.set_zero(value == 0);
            ps.set_negative((value & 0x80) == 0x80);
        }
    }
}