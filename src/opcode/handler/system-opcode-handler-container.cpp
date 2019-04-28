#include "system-opcode-handler-container.h"

namespace emu_6502 {
    SystemOpcodeHandlerContainer::SystemOpcodeHandlerContainer() {
        handlers.insert({Op::NOP, [](Machine&) {}});
    }
}