#ifndef INC_6502_EMULATOR_TERMINAL_H
#define INC_6502_EMULATOR_TERMINAL_H

#include <memory>
#include <SDL2/SDL.h>
#include "memory.h"

using namespace std;

namespace emu_6502 {
    class Terminal {
    private:
        const uint16_t LOW_ADDR = 0xE000;
        const uint16_t HIGH_ADDR = 0xF000;
        const uint8_t WIDTH = 64;
        const uint8_t HEIGHT = 64;
        const uint8_t PIXEL_WEIGHT = 8;

        Memory& memory;

        SDL_Event event;
        SDL_Renderer* renderer;
        SDL_Window* window;

        void draw_pixel(int x, int y, uint8_t colour);

    public:
        Terminal(Memory& memory);
        Terminal(const Terminal&) = delete;
        Terminal& operator=(const Terminal&) = delete;
        ~Terminal();

        void refresh();
    };
}


#endif //INC_6502_EMULATOR_TERMINAL_H
