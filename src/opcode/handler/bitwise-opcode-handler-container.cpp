#include "bitwise-opcode-handler-container.h"
#include "../../utils.h"

namespace emu_6502 {
    BitwiseOpcodeHandlerContainer::BitwiseOpcodeHandlerContainer() {
        handlers.insert({Op::AND_IMM, [this](Machine& machine) { and_imm(machine); }});
        handlers.insert({Op::AND_ZPG, [this](Machine& machine) { and_zpg(machine); }});
        handlers.insert({Op::AND_ZPG_X, [this](Machine& machine) { and_zpg_x(machine); }});
        handlers.insert({Op::AND_ABS, [this](Machine& machine) { and_abs(machine); }});
        handlers.insert({Op::AND_ABS_X, [this](Machine& machine) { and_abs_x(machine); }});
        handlers.insert({Op::AND_ABS_Y, [this](Machine& machine) { and_abs_y(machine); }});
        handlers.insert({Op::AND_IND_X, [this](Machine& machine) { and_ind_x(machine); }});
        handlers.insert({Op::AND_IND_Y, [this](Machine& machine) { and_ind_y(machine); }});

        handlers.insert({Op::ORA_IMM, [this](Machine& machine) { or_imm(machine); }});
        handlers.insert({Op::ORA_ZPG, [this](Machine& machine) { or_zpg(machine); }});
        handlers.insert({Op::ORA_ZPG_X, [this](Machine& machine) { or_zpg_x(machine); }});
        handlers.insert({Op::ORA_ABS, [this](Machine& machine) { or_abs(machine); }});
        handlers.insert({Op::ORA_ABS_X, [this](Machine& machine) { or_abs_x(machine); }});
        handlers.insert({Op::ORA_ABS_Y, [this](Machine& machine) { or_abs_y(machine); }});
        handlers.insert({Op::ORA_IND_X, [this](Machine& machine) { or_ind_x(machine); }});
        handlers.insert({Op::ORA_IND_Y, [this](Machine& machine) { or_ind_y(machine); }});

        handlers.insert({Op::EOR_IMM, [this](Machine& machine) { xor_imm(machine); }});
        handlers.insert({Op::EOR_ZPG, [this](Machine& machine) { xor_zpg(machine); }});
        handlers.insert({Op::EOR_ZPG_X, [this](Machine& machine) { xor_zpg_x(machine); }});
        handlers.insert({Op::EOR_ABS, [this](Machine& machine) { xor_abs(machine); }});
        handlers.insert({Op::EOR_ABS_X, [this](Machine& machine) { xor_abs_x(machine); }});
        handlers.insert({Op::EOR_ABS_Y, [this](Machine& machine) { xor_abs_y(machine); }});
        handlers.insert({Op::EOR_IND_X, [this](Machine& machine) { xor_ind_x(machine); }});
        handlers.insert({Op::EOR_IND_Y, [this](Machine& machine) { xor_ind_y(machine); }});

        handlers.insert({Op::BIT_ZPG, [this](Machine& machine) { bit_zpg(machine); }});
        handlers.insert({Op::BIT_ABS, [this](Machine& machine) { bit_abs(machine); }});

        handlers.insert({Op::ASL_ACC, [this](Machine& machine) { asl_acc(machine); }});
        handlers.insert({Op::ASL_ZPG, [this](Machine& machine) { asl_zpg(machine); }});
        handlers.insert({Op::ASL_ZPG_X, [this](Machine& machine) { asl_zpg_x(machine); }});
        handlers.insert({Op::ASL_ABS, [this](Machine& machine) { asl_abs(machine); }});
        handlers.insert({Op::ASL_ABS_X, [this](Machine& machine) { asl_abs_x(machine); }});

        handlers.insert({Op::LSR_ACC, [this](Machine& machine) { lsr_acc(machine); }});
        handlers.insert({Op::LSR_ZPG, [this](Machine& machine) { lsr_zpg(machine); }});
        handlers.insert({Op::LSR_ZPG_X, [this](Machine& machine) { lsr_zpg_x(machine); }});
        handlers.insert({Op::LSR_ABS, [this](Machine& machine) { lsr_abs(machine); }});
        handlers.insert({Op::LSR_ABS_X, [this](Machine& machine) { lsr_abs_x(machine); }});

        handlers.insert({Op::ROL_ACC, [this](Machine& machine) { rol_acc(machine); }});
        handlers.insert({Op::ROL_ZPG, [this](Machine& machine) { rol_zpg(machine); }});
        handlers.insert({Op::ROL_ZPG_X, [this](Machine& machine) { rol_zpg_x(machine); }});
        handlers.insert({Op::ROL_ABS, [this](Machine& machine) { rol_abs(machine); }});
        handlers.insert({Op::ROL_ABS_X, [this](Machine& machine) { rol_abs_x(machine); }});

        handlers.insert({Op::ROR_ACC, [this](Machine& machine) { ror_acc(machine); }});
        handlers.insert({Op::ROR_ZPG, [this](Machine& machine) { ror_zpg(machine); }});
        handlers.insert({Op::ROR_ZPG_X, [this](Machine& machine) { ror_zpg_x(machine); }});
        handlers.insert({Op::ROR_ABS, [this](Machine& machine) { ror_abs(machine); }});
        handlers.insert({Op::ROR_ABS_X, [this](Machine& machine) { ror_abs_x(machine); }});
    }

    void BitwiseOpcodeHandlerContainer::do_and(Machine& machine, uint8_t value) {
        auto& cpu = machine.get_cpu();
        auto result = cpu.get_a().get_value() & value;
        cpu.get_a().set_value(result);

        set_zero_and_neg_flags(machine.get_cpu().get_ps(), result);
    }

    void BitwiseOpcodeHandlerContainer::do_and_with(Machine& machine, uint16_t address) {
        do_and(machine, machine.get_memory().get_at(address));
    }

    void BitwiseOpcodeHandlerContainer::and_imm(Machine& machine) {
        do_and(machine, machine.read_program_byte());
    }

    void BitwiseOpcodeHandlerContainer::and_zpg(Machine& machine) {
        do_and_with(machine, get_zpg_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::and_zpg_x(Machine& machine) {
        do_and_with(machine, get_zpg_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::and_abs(Machine& machine) {
        do_and_with(machine, get_abs_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::and_abs_x(Machine& machine) {
        do_and_with(machine, get_abs_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::and_abs_y(Machine& machine) {
        do_and_with(machine, get_abs_y_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::and_ind_x(Machine& machine) {
        do_and_with(machine, get_ind_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::and_ind_y(Machine& machine) {
        do_and_with(machine, get_ind_y_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::do_or(Machine& machine, uint8_t value) {
        auto& cpu = machine.get_cpu();
        auto result = cpu.get_a().get_value() | value;
        cpu.get_a().set_value(result);

        set_zero_and_neg_flags(machine.get_cpu().get_ps(), result);
    }

    void BitwiseOpcodeHandlerContainer::do_or_with(Machine& machine, uint16_t address) {
        do_or(machine, machine.get_memory().get_at(address));
    }

    void BitwiseOpcodeHandlerContainer::or_imm(Machine& machine) {
        do_or(machine, machine.read_program_byte());
    }

    void BitwiseOpcodeHandlerContainer::or_zpg(Machine& machine) {
        do_or_with(machine, get_zpg_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::or_zpg_x(Machine& machine) {
        do_or_with(machine, get_zpg_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::or_abs(Machine& machine) {
        do_or_with(machine, get_abs_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::or_abs_x(Machine& machine) {
        do_or_with(machine, get_abs_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::or_abs_y(Machine& machine) {
        do_or_with(machine, get_abs_y_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::or_ind_x(Machine& machine) {
        do_or_with(machine, get_ind_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::or_ind_y(Machine& machine) {
        do_or_with(machine, get_ind_y_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::do_xor(Machine& machine, uint8_t value) {
        auto& cpu = machine.get_cpu();
        auto result = cpu.get_a().get_value() ^value;
        cpu.get_a().set_value(result);

        set_zero_and_neg_flags(machine.get_cpu().get_ps(), result);
    }

    void BitwiseOpcodeHandlerContainer::do_xor_with(Machine& machine, uint16_t address) {
        do_xor(machine, machine.get_memory().get_at(address));
    }

    void BitwiseOpcodeHandlerContainer::xor_imm(Machine& machine) {
        do_xor(machine, machine.read_program_byte());
    }

    void BitwiseOpcodeHandlerContainer::xor_zpg(Machine& machine) {
        do_xor_with(machine, get_zpg_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::xor_zpg_x(Machine& machine) {
        do_xor_with(machine, get_zpg_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::xor_abs(Machine& machine) {
        do_xor_with(machine, get_abs_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::xor_abs_x(Machine& machine) {
        do_xor_with(machine, get_abs_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::xor_abs_y(Machine& machine) {
        do_xor_with(machine, get_abs_y_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::xor_ind_x(Machine& machine) {
        do_xor_with(machine, get_ind_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::xor_ind_y(Machine& machine) {
        do_xor_with(machine, get_ind_y_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::bit(Machine& machine, uint16_t address) {
        auto a = machine.get_cpu().get_a().get_value();
        auto mem = machine.get_memory().get_at(address);
        auto& ps = machine.get_cpu().get_ps();

        ps.set_zero((a & mem) == 0);
        ps.set_negative((mem & 0x80) == 0x80);
        ps.set_overflow((mem & 0x40) == 0x40);
    }

    void BitwiseOpcodeHandlerContainer::bit_zpg(Machine& machine) {
        bit(machine, get_zpg_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::bit_abs(Machine& machine) {
        bit(machine, get_abs_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::asl(emu_6502::Machine& machine, function<uint8_t()> get_value,
                                            function<void(uint8_t)> set_value) {
        uint16_t result = get_value() << 1;
        set_value(result);

        auto& ps = machine.get_cpu().get_ps();
        ps.set_carry((result & 0x100) == 0x100);
        set_zero_and_neg_flags(ps, result);
    }

    void BitwiseOpcodeHandlerContainer::asl_at(Machine& machine, uint16_t address) {
        asl(machine,
            [&]() { return machine.get_memory().get_at(address); },
            [&](uint8_t value) { machine.get_memory().set_at(address, value); });
    }

    void BitwiseOpcodeHandlerContainer::asl_acc(Machine& machine) {
        asl(machine,
            [&]() { return machine.get_cpu().get_a().get_value(); },
            [&](uint8_t value) { machine.get_cpu().get_a().set_value(value); });
    }

    void BitwiseOpcodeHandlerContainer::asl_zpg(Machine& machine) {
        asl_at(machine, get_zpg_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::asl_zpg_x(Machine& machine) {
        asl_at(machine, get_zpg_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::asl_abs(Machine& machine) {
        asl_at(machine, get_abs_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::asl_abs_x(Machine& machine) {
        asl_at(machine, get_abs_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::lsr(emu_6502::Machine& machine, function<uint8_t()> get_value,
                                            function<void(uint8_t)> set_value) {
        auto orig = get_value();
        auto result = orig >> 1;
        set_value(result);

        auto& ps = machine.get_cpu().get_ps();
        ps.set_carry((orig & 1) == 1);
        ps.set_zero(result == 0);
    }

    void BitwiseOpcodeHandlerContainer::lsr_at(Machine& machine, uint16_t address) {
        lsr(machine,
            [&]() { return machine.get_memory().get_at(address); },
            [&](uint8_t value) { machine.get_memory().set_at(address, value); });
    }

    void BitwiseOpcodeHandlerContainer::lsr_acc(Machine& machine) {
        lsr(machine,
            [&]() { return machine.get_cpu().get_a().get_value(); },
            [&](uint8_t value) { machine.get_cpu().get_a().set_value(value); });
    }

    void BitwiseOpcodeHandlerContainer::lsr_zpg(Machine& machine) {
        lsr_at(machine, get_zpg_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::lsr_zpg_x(Machine& machine) {
        lsr_at(machine, get_zpg_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::lsr_abs(Machine& machine) {
        lsr_at(machine, get_abs_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::lsr_abs_x(Machine& machine) {
        lsr_at(machine, get_abs_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::rol(emu_6502::Machine& machine, function<uint8_t()> get_value,
                                            function<void(uint8_t)> set_value) {
        uint16_t result = get_value() << 1;
        auto& ps = machine.get_cpu().get_ps();
        if (ps.is_carry_set())
            result += 1;

        set_value(result);
        ps.set_carry((result & 0x100) == 0x100);
        set_zero_and_neg_flags(ps, result);
    }

    void BitwiseOpcodeHandlerContainer::rol_at(Machine& machine, uint16_t address) {
        rol(machine,
            [&]() { return machine.get_memory().get_at(address); },
            [&](uint8_t value) { machine.get_memory().set_at(address, value); });
    }

    void BitwiseOpcodeHandlerContainer::rol_acc(Machine& machine) {
        rol(machine,
            [&]() { return machine.get_cpu().get_a().get_value(); },
            [&](uint8_t value) { machine.get_cpu().get_a().set_value(value); });
    }

    void BitwiseOpcodeHandlerContainer::rol_zpg(Machine& machine) {
        rol_at(machine, get_zpg_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::rol_zpg_x(Machine& machine) {
        rol_at(machine, get_zpg_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::rol_abs(Machine& machine) {
        rol_at(machine, get_abs_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::rol_abs_x(Machine& machine) {
        rol_at(machine, get_abs_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::ror(Machine& machine, function<uint8_t()> get_value,
                                            function<void(uint8_t)> set_value) {
        auto orig = get_value();
        auto result = orig >> 1;

        auto& ps = machine.get_cpu().get_ps();
        if (ps.is_carry_set())
            result += 0x80;

        set_value(result);
        ps.set_carry((orig & 1) == 1);
        set_zero_and_neg_flags(ps, result);
    }

    void BitwiseOpcodeHandlerContainer::ror_at(Machine& machine, uint16_t address) {
        ror(machine,
            [&]() { return machine.get_memory().get_at(address); },
            [&](uint8_t value) { machine.get_memory().set_at(address, value); });
    }

    void BitwiseOpcodeHandlerContainer::ror_acc(Machine& machine) {
        ror(machine,
            [&]() { return machine.get_cpu().get_a().get_value(); },
            [&](uint8_t value) { machine.get_cpu().get_a().set_value(value); });
    }

    void BitwiseOpcodeHandlerContainer::ror_zpg(Machine& machine) {
        ror_at(machine, get_zpg_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::ror_zpg_x(Machine& machine) {
        ror_at(machine, get_zpg_x_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::ror_abs(Machine& machine) {
        ror_at(machine, get_abs_address(machine));
    }

    void BitwiseOpcodeHandlerContainer::ror_abs_x(Machine& machine) {
        ror_at(machine, get_abs_x_address(machine));
    }
}