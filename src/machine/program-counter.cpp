#include "program-counter.h"

namespace emu_6502 {
    void ProgramCounter::inc() {
        value += 1;
    }
}