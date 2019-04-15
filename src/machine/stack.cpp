#include "stack.h"

namespace emu_6502 {
    Stack::Stack(Memory& memory, Register<uint8_t>& sp) : memory(memory), sp(sp) {
        sp.set_value(0xFF);
    }

    void Stack::push(uint8_t value) {
        auto sp_value = sp.get_value();
        memory.set_on_page(Stack::PAGE, sp_value, value);

        sp.set_value(sp_value + 1);
    }

    uint8_t Stack::pop() {
        // a "feature" of the 6502 is that there is no check when popping and stack will wrap around
        auto sp_value = sp.get_value() - 1;
        sp.set_value(sp_value);

        return memory.get_from_page(Stack::PAGE, sp_value);
    }
}