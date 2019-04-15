#ifndef INC_6502_EMULATOR_STACK_H
#define INC_6502_EMULATOR_STACK_H

#include <memory>
#include "memory.h"
#include "register.h"

using namespace std;

namespace emu_6502 {
    class Stack {
    private:
        Memory& memory;
        Register<uint8_t>& sp;

    public:
        const uint8_t PAGE = 1;

        Stack(Memory& memory, Register<uint8_t>& sp);

        Stack(const Stack&) = delete;
        Stack& operator=(const Stack&) = delete;

        void push(uint8_t value);
        uint8_t pop();
    };
}


#endif //INC_6502_EMULATOR_STACK_H
