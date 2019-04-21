#include "branch-opcode-handler-container.h"

namespace emu_6502 {
    BranchOpcodeHandlerContainer::BranchOpcodeHandlerContainer() {
        handlers.insert({Op::BCS, [this](Machine& machine) { bcs(machine); }});
        handlers.insert({Op::BCC, [this](Machine& machine) { bcc(machine); }});

        handlers.insert({Op::BEQ, [this](Machine& machine) { beq(machine); }});
        handlers.insert({Op::BNE, [this](Machine& machine) { bne(machine); }});

        handlers.insert({Op::BPL, [this](Machine& machine) { bpl(machine); }});
        handlers.insert({Op::BMI, [this](Machine& machine) { bmi(machine); }});

        handlers.insert({Op::BVS, [this](Machine& machine) { bvs(machine); }});
        handlers.insert({Op::BVC, [this](Machine& machine) { bvc(machine); }});
    }

    void BranchOpcodeHandlerContainer::bcs(Machine& machine) {
        auto jump = machine.read_program_byte();
        if (machine.get_cpu().get_ps().is_carry_set())
            machine.get_cpu().get_pc().add(jump);
    }

    void BranchOpcodeHandlerContainer::bcc(Machine& machine) {
        auto jump = machine.read_program_byte();
        if (!machine.get_cpu().get_ps().is_carry_set())
            machine.get_cpu().get_pc().add(jump);
    }

    void BranchOpcodeHandlerContainer::beq(Machine& machine) {
        auto jump = machine.read_program_byte();
        if (machine.get_cpu().get_ps().is_zero_set())
            machine.get_cpu().get_pc().add(jump);
    }

    void BranchOpcodeHandlerContainer::bne(Machine& machine) {
        auto jump = machine.read_program_byte();
        if (!machine.get_cpu().get_ps().is_zero_set())
            machine.get_cpu().get_pc().add(jump);
    }

    void BranchOpcodeHandlerContainer::bpl(Machine& machine) {
        auto jump = machine.read_program_byte();
        if (!machine.get_cpu().get_ps().is_negative_set())
            machine.get_cpu().get_pc().add(jump);
    }

    void BranchOpcodeHandlerContainer::bmi(Machine& machine) {
        auto jump = machine.read_program_byte();
        if (machine.get_cpu().get_ps().is_negative_set())
            machine.get_cpu().get_pc().add(jump);
    }

    void BranchOpcodeHandlerContainer::bvs(Machine& machine) {
        auto jump = machine.read_program_byte();
        if (machine.get_cpu().get_ps().is_overflow_set())
            machine.get_cpu().get_pc().add(jump);
    }

    void BranchOpcodeHandlerContainer::bvc(Machine& machine) {
        auto jump = machine.read_program_byte();
        if (!machine.get_cpu().get_ps().is_overflow_set())
            machine.get_cpu().get_pc().add(jump);
    }
}
