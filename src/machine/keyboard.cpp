#include "keyboard.h"
#include <SDL2/SDL.h>

using namespace std;

namespace emu_6502 {
    Keyboard::Keyboard(Memory& memory) : memory(memory) {
        count = 0;
    }

    void Keyboard::read() {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode < 255)
                    memory.set_at(LAST_KEY_PRESS_ADDR, event.key.keysym.scancode);

                break;

            default:
                return;
        }
    }
}