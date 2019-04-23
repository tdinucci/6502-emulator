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

            draw_pixel(x, y, memory.get_at(i));
        }

        SDL_RenderPresent(renderer);
        //SDL_Delay(20);
    }

    void Terminal::draw_pixel(int x, int y, uint8_t colour) {
        uint8_t red, green, blue = 0;
        red = colour >> 5;
        green = (colour >> 2) & 0x07;
        blue = colour & 0x03;

        //cout << "x: " << (int)x << " y: " << (int)y << " RED: " << (int)red << " GREEN: " << (int)green << " BLUE: " << (int)blue << endl;

        SDL_SetRenderDrawColor(renderer, red * 36, green * 36, blue * 85, 255);
        SDL_Rect rect{};
        rect.x = x * PIXEL_WEIGHT;
        rect.y = y * PIXEL_WEIGHT;
        rect.w = PIXEL_WEIGHT;
        rect.h = PIXEL_WEIGHT;
        SDL_RenderFillRect(renderer, &rect);
    }
}