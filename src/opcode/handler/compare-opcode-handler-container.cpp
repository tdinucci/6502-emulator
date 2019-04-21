#include "compare-opcode-handler-container.h"
#include "../../utils.h"

namespace emu_6502 {
    CompareOpcodeHandlerContainer::CompareOpcodeHandlerContainer() {
        handlers.insert({Op::CMP_IMM, [this](Machine& machine) { cmp_imm(machine); }});
        handlers.insert({Op::CMP_ZPG, [this](Machine& machine) { cmp_zpg(machine); }});
        handlers.insert({Op::CMP_ZPG_X, [this](Machine& machine) { cmp_zpg_x(machine); }});
        handlers.insert({Op::CMP_ABS, [this](Machine& machine) { cmp_abs(machine); }});
        handlers.insert({Op::CMP_ABS_X, [this](Machine& machine) { cmp_abs_x(machine); }});
        handlers.insert({Op::CMP_ABS_Y, [this](Machine& machine) { cmp_abs_y(machine); }});
        handlers.insert({Op::CMP_IND_X, [this](Machine& machine) { cmp_ind_x(machine); }});
        handlers.insert({Op::CMP_IND_Y, [this](Machine& machine) { cmp_ind_y(machine); }});

        handlers.insert({Op::CPX_IMM, [this](Machine& machine) { cpx_imm(machine); }});
        handlers.insert({Op::CPX_ZPG, [this](Machine& machine) { cpx_zpg(machine); }});
        handlers.insert({Op::CPX_ABS, [this](Machine& machine) { cpx_abs(machine); }});

        handlers.insert({Op::CPY_IMM, [this](Machine& machine) { cpy_imm(machine); }});
        handlers.insert({Op::CPY_ZPG, [this](Machine& machine) { cpy_zpg(machine); }});
        handlers.insert({Op::CPY_ABS, [this](Machine& machine) { cpy_abs(machine); }});
    }

    void CompareOpcodeHandlerContainer::cmp(Machine& machine, Register<uint8_t>& reg, uint8_t value) {
        auto reg_val = reg.get_value();
        uint8_t result = reg_val - value;
        auto& ps = machine.get_cpu().get_ps();

        ps.set_carry(false);
        ps.set_zero(false);

        if (reg_val >= value)
            ps.set_carry(true);
        if (reg_val == value)
            ps.set_zero(true);
        if ((result & 0x80) == 0x80)
            ps.set_negative(true);
    }

    void CompareOpcodeHandlerContainer::cmp_imm(Machine& machine) {
        cmp(machine, machine.get_cpu().get_a(), machine.read_program_byte());
    }

    void CompareOpcodeHandlerContainer::cmp_zpg(Machine& machine) {
        cmp(machine, machine.get_cpu().get_a(), machine.get_memory().get_at(get_zpg_address(machine)));
    }

    void CompareOpcodeHandlerContainer::cmp_zpg_x(Machine& machine) {
        cmp(machine, machine.get_cpu().get_a(), machine.get_memory().get_at(get_zpg_x_address(machine)));
    }

    void CompareOpcodeHandlerContainer::cmp_abs(Machine& machine) {
        cmp(machine, machine.get_cpu().get_a(), machine.get_memory().get_at(get_abs_address(machine)));
    }

    void CompareOpcodeHandlerContainer::cmp_abs_x(Machine& machine) {
        cmp(machine, machine.get_cpu().get_a(), machine.get_memory().get_at(get_abs_x_address(machine)));
    }

    void CompareOpcodeHandlerContainer::cmp_abs_y(Machine& machine) {
        cmp(machine, machine.get_cpu().get_a(), machine.get_memory().get_at(get_abs_y_address(machine)));
    }

    void CompareOpcodeHandlerContainer::cmp_ind_x(Machine& machine) {
        cmp(machine, machine.get_cpu().get_a(), machine.get_memory().get_at(get_ind_x_address(machine)));
    }

    void CompareOpcodeHandlerContainer::cmp_ind_y(Machine& machine) {
        cmp(machine, machine.get_cpu().get_a(), machine.get_memory().get_at(get_ind_y_address(machine)));
    }

    void CompareOpcodeHandlerContainer::cpx_imm(Machine& machine) {
        cmp(machine, machine.get_cpu().get_x(), machine.read_program_byte());
    }

    void CompareOpcodeHandlerContainer::cpx_zpg(Machine& machine) {
        cmp(machine, machine.get_cpu().get_x(), machine.get_memory().get_at(get_zpg_address(machine)));
    }

    void CompareOpcodeHandlerContainer::cpx_abs(Machine& machine) {
        cmp(machine, machine.get_cpu().get_x(), machine.get_memory().get_at(get_abs_address(machine)));
    }

    void CompareOpcodeHandlerContainer::cpy_imm(Machine& machine) {
        cmp(machine, machine.get_cpu().get_y(), machine.read_program_byte());
    }

    void CompareOpcodeHandlerContainer::cpy_zpg(Machine& machine) {
        cmp(machine, machine.get_cpu().get_y(), machine.get_memory().get_at(get_zpg_address(machine)));
    }

    void CompareOpcodeHandlerContainer::cpy_abs(Machine& machine) {
        cmp(machine, machine.get_cpu().get_y(), machine.get_memory().get_at(get_abs_address(machine)));
    }
}
