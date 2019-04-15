#include "opcode-handler-container.h"

namespace emu_6502 {
    OpcodeHandlerContainer::OpcodeHandlerContainer() : handlers{} {}

    const unordered_map<uint8_t, function<void(Machine&)>>& OpcodeHandlerContainer::get_handlers() {
        return handlers;
    }
}
