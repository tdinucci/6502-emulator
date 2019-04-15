#ifndef INC_6502_EMULATOR_TERMINAL_H
#define INC_6502_EMULATOR_TERMINAL_H

#include <ncurses.h>
#include <memory>
#include "memory.h"

using namespace std;

namespace emu_6502 {
    class Terminal {
    private:
        const uint16_t LOW_ADDR = 0xFB00;
        const uint16_t HIGH_ADDR = 0xFF00;
        const uint8_t TERM_LINES = 25;
        const uint8_t TERM_COLS = 40;

        //WINDOW * mainwin;

        Memory& memory;

    public:
        Terminal(Memory& memory);
        Terminal(const Terminal&) = delete;
        Terminal& operator=(const Terminal&) = delete;
        ~Terminal();

        void refresh();
    };
}


#endif //INC_6502_EMULATOR_TERMINAL_H
