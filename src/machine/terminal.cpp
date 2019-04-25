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

        memory.register_callback([this](pair<uint16_t, uint8_t> addr_val) { on_memory_written(addr_val); });
    }

    Terminal::~Terminal() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Terminal::on_memory_written(pair<uint16_t, uint8_t> address_value) {
        uint16_t address = address_value.first;

        if (address >= LOW_ADDR && address <= HIGH_ADDR) {
            uint8_t colour = address_value.second;
            int x = (address - LOW_ADDR) % WIDTH;
            int y = (address - LOW_ADDR) / HEIGHT;

            draw_pixel(x, y, colour);

            SDL_RenderPresent(renderer);
            SDL_Delay(50);
        }
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