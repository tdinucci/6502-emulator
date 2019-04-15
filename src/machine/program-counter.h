#ifndef INC_6502_EMULATOR_PROGRAM_COUNTER_H
#define INC_6502_EMULATOR_PROGRAM_COUNTER_H

#include "register.h"

namespace emu_6502 {
    class ProgramCounter : public Register<uint16_t> {
    public:
        ProgramCounter() : Register<uint16_t>("PC") {}

        ProgramCounter(const ProgramCounter&) = delete;
        ProgramCounter& operator=(const ProgramCounter&) = delete;

        void inc();
    };
}

#endif //INC_6502_EMULATOR_PROGRAM_COUNTER_H
