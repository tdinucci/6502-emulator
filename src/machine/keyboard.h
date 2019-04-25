#ifndef INC_6502_EMULATOR_KEYBOARD_H
#define INC_6502_EMULATOR_KEYBOARD_H

#include "memory.h"
#include <SDL2/SDL.h>

namespace emu_6502 {
    class Keyboard {
    private:
        static const uint16_t LAST_KEY_PRESS_ADDR = 0xF001;

        uint16_t count;

        SDL_Event event;
        Memory& memory;

    public:
        Keyboard(Memory& memory);
        Keyboard(const Keyboard&) = delete;
        Keyboard& operator=(const Keyboard&) = delete;

        void read();
    };
}

#endif //INC_6502_EMULATOR_KEYBOARD_H
