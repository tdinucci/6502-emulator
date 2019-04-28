#ifndef INC_6502_EMULATOR_SYSTEM_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_SYSTEM_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"

namespace emu_6502 {
    class SystemOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            NOP = 0xEA
        };

    public:
        SystemOpcodeHandlerContainer();
        SystemOpcodeHandlerContainer(const SystemOpcodeHandlerContainer& other) = delete;
        SystemOpcodeHandlerContainer operator=(const SystemOpcodeHandlerContainer& other) = delete;
    };
}


#endif //INC_6502_EMULATOR_SYSTEM_OPCODE_HANDLER_CONTAINER_H
