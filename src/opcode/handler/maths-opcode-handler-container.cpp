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

        handlers.insert({Op::SBC_IMM, [this](Machine& machine) { sbc_imm(machine); }});
        handlers.insert({Op::SBC_ZPG, [this](Machine& machine) { sbc_zpg(machine); }});
        handlers.insert({Op::SBC_ZPG_X, [this](Machine& machine) { sbc_zpg_x(machine); }});
        handlers.insert({Op::SBC_ABS, [this](Machine& machine) { sbc_abs(machine); }});
        handlers.insert({Op::SBC_ABS_X, [this](Machine& machine) { sbc_abs_x(machine); }});
        handlers.insert({Op::SBC_ABS_Y, [this](Machine& machine) { sbc_abs_y(machine); }});
        handlers.insert({Op::SBC_IND_X, [this](Machine& machine) { sbc_ind_x(machine); }});
        handlers.insert({Op::SBC_IND_Y, [this](Machine& machine) { sbc_ind_y(machine); }});

        handlers.insert({Op::DEC_ZPG, [this](Machine& machine) { dec_zpg(machine); }});
        handlers.insert({Op::DEC_ZPG_X, [this](Machine& machine) { dec_zpg_x(machine); }});
        handlers.insert({Op::DEC_ABS, [this](Machine& machine) { dec_abs(machine); }});
        handlers.insert({Op::DEC_ABS_X, [this](Machine& machine) { dec_abs_x(machine); }});

        handlers.insert({Op::INC_ZPG, [this](Machine& machine) { inc_zpg(machine); }});
        handlers.insert({Op::INC_ZPG_X, [this](Machine& machine) { inc_zpg_x(machine); }});
        handlers.insert({Op::INC_ABS, [this](Machine& machine) { inc_abs(machine); }});
        handlers.insert({Op::INC_ABS_X, [this](Machine& machine) { inc_abs_x(machine); }});

        handlers.insert({Op::INX, [this](Machine& machine) { inx(machine); }});
        handlers.insert({Op::INY, [this](Machine& machine) { iny(machine); }});
        handlers.insert({Op::DEX, [this](Machine& machine) { dex(machine); }});
        handlers.insert({Op::DEY, [this](Machine& machine) { dey(machine); }});
    }

    void MathsOpcodeHandlerContainer::set_zero_neg(StatusRegister& ps, uint8_t value) {
        ps.set_zero(value == 0);
        ps.set_negative((value & 0x80) == 0x80);
    }

    void MathsOpcodeHandlerContainer::adc(Machine& machine, uint8_t value) {
        auto& cpu = machine.get_cpu();
        auto init_a = cpu.get_a().get_value();

        // allow for operation to breach 8 bits
        uint16_t result = value + init_a;
        if (cpu.get_ps().is_carry_set())
            result += 1;

        cpu.get_a().set_value(result); // will chop off bit 8 if set
        auto a = cpu.get_a().get_value();

        // 'a' may be 0 if the result wasn't 0, i.e. the cary bit is set
        set_zero_neg(cpu.get_ps(), a);
        cpu.get_ps().set_carry(result > 0xFF);
        cpu.get_ps().set_overflow(
                (value < 0x7F && init_a < 0x7F && a > 0x7F) ||
                (value > 0x7F && init_a > 0x7F && a < 0x7F));
    }

    void MathsOpcodeHandlerContainer::adc_imm(Machine& machine) {
        adc(machine, machine.read_program_byte());
    }

    void MathsOpcodeHandlerContainer::adc_zpg(Machine& machine) {
        adc(machine, machine.get_memory().get_at(get_zpg_address(machine)));
    }

    void MathsOpcodeHandlerContainer::adc_zpg_x(Machine& machine) {
        adc(machine, machine.get_memory().get_at(get_zpg_x_address(machine)));
    }

    void MathsOpcodeHandlerContainer::adc_abs(Machine& machine) {
        adc(machine, machine.get_memory().get_at(get_abs_address(machine)));
    }

    void MathsOpcodeHandlerContainer::adc_abs_x(Machine& machine) {
        adc(machine, machine.get_memory().get_at(get_abs_x_address(machine)));
    }

    void MathsOpcodeHandlerContainer::adc_abs_y(Machine& machine) {
        adc(machine, machine.get_memory().get_at(get_abs_y_address(machine)));
    }

    void MathsOpcodeHandlerContainer::adc_ind_x(Machine& machine) {
        adc(machine, machine.get_memory().get_at(get_ind_x_address(machine)));
    }

    void MathsOpcodeHandlerContainer::adc_ind_y(Machine& machine) {
        adc(machine, machine.get_memory().get_at(get_ind_y_address(machine)));
    }

    void MathsOpcodeHandlerContainer::sbc(Machine& machine, uint8_t value) {
        // subtract is same as add negative value (i.e. add accumulator to the twos compliment of 'value')
        adc(machine, (0xFF ^ value) + 1);
    }

    void MathsOpcodeHandlerContainer::sbc_imm(Machine& machine) {
        sbc(machine, machine.read_program_byte());
    }

    void MathsOpcodeHandlerContainer::sbc_zpg(Machine& machine) {
        sbc(machine, machine.get_memory().get_at(get_zpg_address(machine)));
    }

    void MathsOpcodeHandlerContainer::sbc_zpg_x(Machine& machine) {
        sbc(machine, machine.get_memory().get_at(get_zpg_x_address(machine)));
    }

    void MathsOpcodeHandlerContainer::sbc_abs(Machine& machine) {
        sbc(machine, machine.get_memory().get_at(get_abs_address(machine)));
    }

    void MathsOpcodeHandlerContainer::sbc_abs_x(Machine& machine) {
        sbc(machine, machine.get_memory().get_at(get_abs_x_address(machine)));
    }

    void MathsOpcodeHandlerContainer::sbc_abs_y(Machine& machine) {
        sbc(machine, machine.get_memory().get_at(get_abs_y_address(machine)));
    }

    void MathsOpcodeHandlerContainer::sbc_ind_x(Machine& machine) {
        sbc(machine, machine.get_memory().get_at(get_ind_x_address(machine)));
    }

    void MathsOpcodeHandlerContainer::sbc_ind_y(Machine& machine) {
        sbc(machine, machine.get_memory().get_at(get_ind_y_address(machine)));
    }

    void MathsOpcodeHandlerContainer::dec(Machine& machine, uint16_t address) {
        uint8_t value = machine.get_memory().get_at(address) - 1;
        machine.get_memory().set_at(address, value);

        set_zero_neg(machine.get_cpu().get_ps(), value);
    }

    void MathsOpcodeHandlerContainer::dec_zpg(Machine& machine) {
        dec(machine, get_zpg_address(machine));
    }

    void MathsOpcodeHandlerContainer::dec_zpg_x(Machine& machine) {
        dec(machine, get_zpg_x_address(machine));
    }

    void MathsOpcodeHandlerContainer::dec_abs(Machine& machine) {
        dec(machine, get_abs_address(machine));
    }

    void MathsOpcodeHandlerContainer::dec_abs_x(Machine& machine) {
        dec(machine, get_abs_x_address(machine));
    }

    void MathsOpcodeHandlerContainer::inc(Machine& machine, uint16_t address) {
        uint8_t value = machine.get_memory().get_at(address) + 1;
        machine.get_memory().set_at(address, value);

        set_zero_neg(machine.get_cpu().get_ps(), value);
    }

    void MathsOpcodeHandlerContainer::inc_zpg(Machine& machine) {
        inc(machine, get_zpg_address(machine));
    }

    void MathsOpcodeHandlerContainer::inc_zpg_x(Machine& machine) {
        inc(machine, get_zpg_x_address(machine));
    }

    void MathsOpcodeHandlerContainer::inc_abs(Machine& machine) {
        inc(machine, get_abs_address(machine));
    }

    void MathsOpcodeHandlerContainer::inc_abs_x(Machine& machine) {
        inc(machine, get_abs_x_address(machine));
    }

    void MathsOpcodeHandlerContainer::de(Machine& machine, Register<uint8_t>& reg) {
        uint8_t value = reg.get_value() - 1;
        reg.set_value(value);

        set_zero_neg(machine.get_cpu().get_ps(), value);
    }

    void MathsOpcodeHandlerContainer::dex(Machine& machine) {
        de(machine, machine.get_cpu().get_x());
    }

    void MathsOpcodeHandlerContainer::dey(Machine& machine) {
        de(machine, machine.get_cpu().get_y());
    }

    void MathsOpcodeHandlerContainer::in(Machine& machine, Register<uint8_t>& reg) {
        uint8_t value = reg.get_value() + 1;
        reg.set_value(value);

        set_zero_neg(machine.get_cpu().get_ps(), value);
    }

    void MathsOpcodeHandlerContainer::inx(Machine& machine) {
        in(machine, machine.get_cpu().get_x());
    }

    void MathsOpcodeHandlerContainer::iny(Machine& machine) {
        in(machine, machine.get_cpu().get_y());
    }
}
