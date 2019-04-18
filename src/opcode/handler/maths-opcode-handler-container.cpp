#include "maths-opcode-handler-container.h"
#include "../../utils.h"

namespace emu_6502 {
    MathsOpcodeHandlerContainer::MathsOpcodeHandlerContainer() : OpcodeHandlerContainer() {
        handlers.insert({Op::ADC_IMM, [this](Machine& machine) { adc_imm(machine); }});
        handlers.insert({Op::ADC_ZPG, [this](Machine& machine) { adc_zpg(machine); }});
        handlers.insert({Op::ADC_ZPG_X, [this](Machine& machine) { adc_zpg_x(machine); }});
        handlers.insert({Op::ADC_ABS, [this](Machine& machine) { adc_abs(machine); }});
        handlers.insert({Op::ADC_ABS_X, [this](Machine& machine) { adc_abs_x(machine); }});
        handlers.insert({Op::ADC_ABS_Y, [this](Machine& machine) { adc_abs_y(machine); }});
        handlers.insert({Op::ADC_IND_X, [this](Machine& machine) { adc_ind_x(machine); }});
        handlers.insert({Op::ADC_IND_Y, [this](Machine& machine) { adc_ind_y(machine); }});
    }

    void MathsOpcodeHandlerContainer::adc(Machine& machine, uint8_t value){
        auto& cpu = machine.get_cpu();
        auto init_a = cpu.get_a().get_value();

        uint16_t result = value + init_a;
        if (cpu.get_ps().is_carry_set())
            result += 1;

        cpu.get_a().set_value(result); // will chop off bit 8 if set
        auto a = cpu.get_a().get_value();

        // 'a' may be 0 if the result wasn't 0, i.e. the cary bit is set
        cpu.get_ps().set_zero(a == 0);
        cpu.get_ps().set_negative((a & 0x80) == 0x80);
        cpu.get_ps().set_carry(result > 0xFF);
        cpu.get_ps().set_overflow(
                (value < 0x7F && init_a < 0x7F && a > 0x7F) ||
                (value > 0x7F && init_a > 0x7F && a < 0x7F));
    }

    void MathsOpcodeHandlerContainer::adc_imm(Machine& machine) {
        adc(machine, machine.read_program_byte());
    }

    void MathsOpcodeHandlerContainer::adc_zpg(Machine& machine) {
        auto addr = get_zpg_address(machine.read_program_byte());
        adc(machine, machine.get_memory().get_at(addr));
    }

    void MathsOpcodeHandlerContainer::adc_zpg_x(Machine& machine) {
        auto addr = get_zpg_x_address(machine.read_program_byte(), machine.get_cpu());
        adc(machine, machine.get_memory().get_at(addr));
    }

    void MathsOpcodeHandlerContainer::adc_abs(Machine& machine) {
        auto low = machine.read_program_byte();
        auto high = machine.read_program_byte();
        auto addr = get_abs_address(low, high);
        adc(machine, machine.get_memory().get_at(addr));
    }

    void MathsOpcodeHandlerContainer::adc_abs_x(Machine& machine) {
        auto addr = get_abs_x_address(machine, machine.get_cpu());
        adc(machine, machine.get_memory().get_at(addr));
    }

    void MathsOpcodeHandlerContainer::adc_abs_y(Machine& machine) {
        auto addr = get_abs_y_address(machine, machine.get_cpu());
        adc(machine, machine.get_memory().get_at(addr));
    }

    void MathsOpcodeHandlerContainer::adc_ind_x(Machine& machine) {
        auto addr = get_ind_x_address(machine.read_program_byte(), machine);
        adc(machine, machine.get_memory().get_at(addr));
    }

    void MathsOpcodeHandlerContainer::adc_ind_y(Machine& machine) {
        auto addr = get_ind_y_address(machine.read_program_byte(), machine);
        adc(machine, machine.get_memory().get_at(addr));
    }

    void MathsOpcodeHandlerContainer::dec_zpg(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::dec_zpg_x(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::dec_abs(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::dec_abs_x(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::dex(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::dey(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::inx(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::iny(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::sbc_imm(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::sbc_zpg(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::sbc_zpg_x(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::sbc_abs(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::sbc_abs_x(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::sbc_abs_y(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::sbc_ind_x(Machine& machine) {
    }

    void MathsOpcodeHandlerContainer::sbc_ind_y(Machine& machine) {
    }
}
