#include <unistd.h>
#include <iostream>

#include "terminal.h"

namespace emu_6502 {
    Terminal::Terminal(Memory& memory) : memory(memory) {
        int width = WIDTH * PIXEL_WEIGHT;
        int height = HEIGHT * PIXEL_WEIGHT;

        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        SDL_RenderClear(renderer);

        for (auto i = LOW_ADDR; i <= HIGH_ADDR; i++) {
            memory.set_at(i, 0);
        }
    }

    Terminal::~Terminal() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Terminal::refresh() {
        int x, y = 0;
        for (auto i = LOW_ADDR; i <= HIGH_ADDR; i++) {
            x = (i - LOW_ADDR) % WIDTH;
            y = (i - LOW_ADDR) / HEIGHT;

            auto colour = memory.get_at(i);
            if (colour) {
                draw_pixel(x, y, colour);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(5);
    }

    void Terminal::draw_pixel(int x, int y, uint8_t colour) {
        uint8_t red, green, blue = 0;
        red = colour >> 5;
        green = (colour >> 2) & 0x07;
        blue = colour & 0x03;

        cout << "RED: " << (int)red << " GREEN: " << (int)green << " BLUE: " << (int)blue << endl;

        SDL_SetRenderDrawColor(renderer, red * 36, green * 36, blue * 85, 0);
        for (int i = 0; i < PIXEL_WEIGHT; i++) {
            SDL_RenderDrawPoint(renderer, (x * PIXEL_WEIGHT) + i, (y * PIXEL_WEIGHT));

            for (int j = 0; j < PIXEL_WEIGHT; j++) {
                SDL_RenderDrawPoint(renderer, (x * PIXEL_WEIGHT) + i, (y * PIXEL_WEIGHT) + j);
            }
        }
    }
}