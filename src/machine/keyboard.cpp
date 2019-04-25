#include "keyboard.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

namespace emu_6502 {
    Keyboard::Keyboard(Memory& memory) : memory(memory) {
        count = 0;
    }

    void Keyboard::read() {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_KEYDOWN:

                //if(event.key.keysym.scancode < 255)
                    memory.set_at(LAST_KEY_PRESS_ADDR, event.key.keysym.scancode);

                cout << "CODE: " << event.key.keysym.scancode << endl;
//                switch (event.key.keysym.sym) {
//                    case SDLK_LEFT:
//                        cout << "LEFT " << (uint16_t) count++ << endl;
//                        break;
//                    case SDLK_RIGHT:
//                        cout << "RIGHT" << (uint16_t) count++ << endl;
//                        break;
//                    case SDLK_UP:
//                        cout << "UP" << (uint16_t) count++ << endl;
//                        break;
//                    case SDLK_DOWN:
//                        cout << "DOWN" << (uint16_t) count++ << endl;
//                        break;
//                    default:
//                        break;
//                }
                break;
            default:
                return;
        }
    }
}