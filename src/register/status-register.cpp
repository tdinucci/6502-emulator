#include "status-register.h"

const uint8_t CARRY_FLAG = 0;
const uint8_t ZERO_FLAG = 1;
const uint8_t INTERUPT_DISABLE_FLAG = 2;
const uint8_t DECIMAL_FLAG = 3;
const uint8_t BREAK_FLAG = 4;
const uint8_t OVERFLOW_FLAG = 6;
const uint8_t NEGATIVE_FLAG = 7;

bool StatusRegister::is_carry_set() {
    return this->value[CARRY_FLAG];
}

bool StatusRegister::is_zero_set() {
    return this->value[ZERO_FLAG];
}

bool StatusRegister::is_interupt_disable_set() {
    return this->value[INTERUPT_DISABLE_FLAG];
}

bool StatusRegister::is_decimal_set() {
    return this->value[DECIMAL_FLAG];
}

bool StatusRegister::is_break_set() {
    return this->value[BREAK_FLAG];
}

bool StatusRegister::is_overflow_set() {
    return this->value[OVERFLOW_FLAG];
}

bool StatusRegister::is_negative_set() {
    return this->value[NEGATIVE_FLAG];
}

void StatusRegister::set_carry(bool state) {
    this->value[CARRY_FLAG] = state;
}

void StatusRegister::set_zero(bool state) {
    this->value[ZERO_FLAG] = state;
}

void StatusRegister::set_interupt_disable(bool state) {
    this->value[INTERUPT_DISABLE_FLAG] = state;
}

void StatusRegister::set_decimal(bool state) {
    this->value[DECIMAL_FLAG] = state;
}

void StatusRegister::set_break(bool state) {
    this->value[BREAK_FLAG] = state;
}

void StatusRegister::set_overflow(bool state) {
    this->value[OVERFLOW_FLAG] = state;
}

void StatusRegister::set_negative(bool state) {
    this->value[NEGATIVE_FLAG] = state;
}