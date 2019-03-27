#ifndef INC_6502_EMULATOR_STATUS_REGISTER_H
#define INC_6502_EMULATOR_STATUS_REGISTER_H

#include "register.h"
#include <bitset>

class StatusRegister : public Register<bitset<8>> {
public:
    explicit StatusRegister() : Register<bitset<8>>("P") {}

    bool is_carry_set();
    bool is_zero_set();
    bool is_interupt_disable_set();
    bool is_decimal_set();
    bool is_break_set();
    bool is_overflow_set();
    bool is_negative_set();

    void set_carry(bool state);
    void set_zero(bool state);
    void set_interupt_disable(bool state);
    void set_decimal(bool state);
    void set_break(bool state);
    void set_overflow(bool state);
    void set_negative(bool state);
};


#endif //INC_6502_EMULATOR_STATUS_REGISTER_H
