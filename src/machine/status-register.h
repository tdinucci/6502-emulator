#ifndef INC_6502_EMULATOR_STATUS_REGISTER_H
#define INC_6502_EMULATOR_STATUS_REGISTER_H

#include <bitset>
#include <string>
#include "register.h"

using namespace std;

namespace emu_6502 {
    class StatusRegister : public Register<bitset<8>> {
    private:
        enum Flag {
            CARRY = 0,
            ZERO = 1,
            INTERUPT_DISABLE = 2,
            DECIMAL = 3,
            BREAK = 4,
            OVERFLOW = 6,
            NEGATIVE = 7
        };

    public:
        StatusRegister() : Register<bitset<8>>("PS") {}

        StatusRegister(const StatusRegister&) = delete;
        virtual StatusRegister& operator=(const StatusRegister&) = delete;

        bool is_carry_set() const;
        bool is_zero_set() const;
        bool is_interupt_disable_set() const;
        bool is_decimal_set() const;
        bool is_break_set() const;
        bool is_overflow_set() const;
        bool is_negative_set() const;

        void set_carry(bool state);
        void set_zero(bool state);
        void set_interupt_disable(bool state);
        void set_decimal(bool state);
        void set_break(bool state);
        void set_overflow(bool state);
        void set_negative(bool state);
    };
}

#endif //INC_6502_EMULATOR_STATUS_REGISTER_H
