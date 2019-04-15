#include "load-opcode-handler-container.h"
#include "../../utils.h"

#include <iostream>

namespace emu_6502 {
    LoadOpcodeHandlerContainer::LoadOpcodeHandlerContainer() : OpcodeHandlerContainer() {
        handlers.insert({Op::LDA_IMM, [this](Machine& machine) { ld_imm(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::LDA_ZPG, [this](Machine& machine) { ld_zpg(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::LDA_ZPG_X, [this](Machine& machine) { ld_zpg_x(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::LDA_ABS, [this](Machine& machine) { ld_abs(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::LDA_ABS_X, [this](Machine& machine) { ld_abs_x(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::LDA_ABS_Y, [this](Machine& machine) { ld_abs_y(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::LDA_IND_X, [this](Machine& machine) { ld_ind_x(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::LDA_IND_Y, [this](Machine& machine) { ld_ind_y(machine, machine.get_cpu().get_a()); }});

        handlers.insert({Op::LDX_IMM, [this](Machine& machine) { ld_imm(machine, machine.get_cpu().get_x()); }});
        handlers.insert({Op::LDX_ZPG, [this](Machine& machine) { ld_zpg(machine, machine.get_cpu().get_x()); }});
        handlers.insert({Op::LDX_ZPG_Y, [this](Machine& machine) { ld_zpg_y(machine, machine.get_cpu().get_x()); }});
        handlers.insert({Op::LDX_ABS, [this](Machine& machine) { ld_abs(machine, machine.get_cpu().get_x()); }});
        handlers.insert({Op::LDX_ABS_Y, [this](Machine& machine) { ld_abs_y(machine, machine.get_cpu().get_x()); }});

        handlers.insert({Op::LDY_IMM, [this](Machine& machine) { ld_imm(machine, machine.get_cpu().get_y()); }});
        handlers.insert({Op::LDY_ZPG, [this](Machine& machine) { ld_zpg(machine, machine.get_cpu().get_y()); }});
        handlers.insert({Op::LDY_ZPG_X, [this](Machine& machine) { ld_zpg_x(machine, machine.get_cpu().get_y()); }});
        handlers.insert({Op::LDY_ABS, [this](Machine& machine) { ld_abs(machine, machine.get_cpu().get_y()); }});
        handlers.insert({Op::LDY_ABS_X, [this](Machine& machine) { ld_abs_x(machine, machine.get_cpu().get_y()); }});
    }

    void LoadOpcodeHandlerContainer::set_flags(Cpu& cpu, Register<uint8_t>& reg) {
        auto value = reg.get_value();
        cpu.get_ps().set_negative((value & 0x80) == 0x80);
        cpu.get_ps().set_zero(value == 0);
    }

    void LoadOpcodeHandlerContainer::set_from(Machine& machine, Register<uint8_t>& reg, uint16_t address) {
        auto value = machine.get_memory().get_at(address);
        reg.set_value(value);
        set_flags(machine.get_cpu(), reg);
    }

    void LoadOpcodeHandlerContainer::ld_imm(Machine& machine, Register<uint8_t>& reg) {
        reg.set_value(machine.read_program_byte());
        set_flags(machine.get_cpu(), reg);
    }

    void LoadOpcodeHandlerContainer::ld_zpg(Machine& machine, Register<uint8_t>& reg) {
        auto addr = get_zpg_address(machine.read_program_byte());
        set_from(machine, reg, addr);
    }

    void LoadOpcodeHandlerContainer::ld_zpg_x(Machine& machine, Register<uint8_t>& reg) {
        auto addr = get_zpg_x_address(machine.read_program_byte(), machine.get_cpu());
        set_from(machine, reg, addr);
    }

    void LoadOpcodeHandlerContainer::ld_zpg_y(Machine& machine, Register<uint8_t>& reg) {
        auto addr = get_zpg_y_address(machine.read_program_byte(), machine.get_cpu());
        set_from(machine, reg, addr);
    }

    void LoadOpcodeHandlerContainer::ld_abs(Machine& machine, Register<uint8_t>& reg) {
        auto low = machine.read_program_byte();
        auto high = machine.read_program_byte();
        auto addr = get_abs_address(low, high);
        set_from(machine, reg, addr);
    }

    void LoadOpcodeHandlerContainer::ld_abs_x(Machine& machine, Register<uint8_t>& reg) {
        auto low = machine.read_program_byte();
        auto high = machine.read_program_byte();
        auto addr = get_abs_x_address(low, high, machine.get_cpu());
        set_from(machine, reg, addr);
    }

    void LoadOpcodeHandlerContainer::ld_abs_y(Machine& machine, Register<uint8_t>& reg) {
        auto low = machine.read_program_byte();
        auto high = machine.read_program_byte();
        auto addr = get_abs_y_address(low, high, machine.get_cpu());
        set_from(machine, reg, addr);
    }

    void LoadOpcodeHandlerContainer::ld_ind_x(Machine& machine, Register<uint8_t>& reg) {
        auto addr = get_ind_x_address(machine.read_program_byte(), machine);
        set_from(machine, reg, addr);
    }

    void LoadOpcodeHandlerContainer::ld_ind_y(Machine& machine, Register<uint8_t>& reg) {
        auto addr = get_ind_y_address(machine.read_program_byte(), machine);
        set_from(machine, reg, addr);
    }
}