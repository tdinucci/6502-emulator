#include <unistd.h>
#include <iostream>

#include "terminal.h"

namespace emu_6502 {
    Terminal::Terminal(Memory& memory) : memory(memory) {
//    for (auto i = 0; i < 100; i++)
//        memory->set_at(Terminal::LOW_ADDR + i, 0x20 + i);
//
//    if ((mainwin = initscr()) == NULL) {
//        fprintf(stderr, "Error initialising ncurses.\n");
//        exit(EXIT_FAILURE);
//    }
//
//    start_color();
    }

    Terminal::~Terminal() {
//    delwin(mainwin);
//    endwin();

        cout << "shutting down" << endl;
    }

    void Terminal::refresh() {
//    for (auto n = 0; n <= 100; n++) {
//        auto line = (n / TERM_COLS);
//        auto col = n % TERM_COLS;
//
//        mvaddch(line, col, memory->get_at(Terminal::LOW_ADDR + n));
//        n++;
//    }
//
//    wrefresh(mainwin);
    }
}