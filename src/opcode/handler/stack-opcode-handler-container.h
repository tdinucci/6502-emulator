#ifndef INC_6502_EMULATOR_STACK_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_STACK_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"

namespace emu_6502 {
    class StackOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            PHA = 0x48,
            PHP = 0x08,
            PLA = 0x68,
            PLP = 0x28,
        };

        void pha(Machine& machine);
        void php(Machine& machine);

        void pla(Machine& machine);
        void plp(Machine& machine);

    public:
        StackOpcodeHandlerContainer();
        StackOpcodeHandlerContainer(const StackOpcodeHandlerContainer&) = delete;
        StackOpcodeHandlerContainer& operator=(const StackOpcodeHandlerContainer&) = delete;
    };
}


#endif //INC_6502_EMULATOR_STACK_OPCODE_HANDLER_CONTAINER_H
