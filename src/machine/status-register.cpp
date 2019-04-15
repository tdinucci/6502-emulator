#include "status-register.h"

namespace emu_6502 {
    bool StatusRegister::is_carry_set() const {
        return this->value[Flag::CARRY];
    }

    bool StatusRegister::is_zero_set() const {
        return this->value[Flag::ZERO];
    }

    bool StatusRegister::is_interupt_disable_set() const {
        return this->value[Flag::INTERUPT_DISABLE];
    }

    bool StatusRegister::is_decimal_set() const {
        return this->value[Flag::DECIMAL];
    }

    bool StatusRegister::is_break_set() const {
        return this->value[Flag::BREAK];
    }

    bool StatusRegister::is_overflow_set() const {
        return this->value[Flag::OVERFLOW];
    }

    bool StatusRegister::is_negative_set() const {
        return this->value[Flag::NEGATIVE];
    }

    void StatusRegister::set_carry(bool state) {
        this->value[Flag::CARRY] = state;
    }

    void StatusRegister::set_zero(bool state) {
        this->value[Flag::ZERO] = state;
    }

    void StatusRegister::set_interupt_disable(bool state) {
        this->value[Flag::INTERUPT_DISABLE] = state;
    }

    void StatusRegister::set_decimal(bool state) {
        this->value[Flag::DECIMAL] = state;
    }

    void StatusRegister::set_break(bool state) {
        this->value[Flag::BREAK] = state;
    }

    void StatusRegister::set_overflow(bool state) {
        this->value[Flag::OVERFLOW] = state;
    }

    void StatusRegister::set_negative(bool state) {
        this->value[Flag::NEGATIVE] = state;
    }
}