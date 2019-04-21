#ifndef INC_6502_EMULATOR_JUMP_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_JUMP_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"

namespace emu_6502 {
    class JumpOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            JMP_ABS = 0x4C,
            JMP_IND = 0x6C,

            JSR = 0x20,

            RTI = 0x40,
            RTS = 0x60
        };

        void jmp_abs(Machine& machine);
        void jmp_ind(Machine& machine);

        void jsr(Machine& machine);

        void rti(Machine& machine);
        void rts(Machine& machine);

    public:
        JumpOpcodeHandlerContainer();
        JumpOpcodeHandlerContainer(const JumpOpcodeHandlerContainer&) = delete;
        JumpOpcodeHandlerContainer& operator=(const JumpOpcodeHandlerContainer&) = delete;
    };
}


#endif //INC_6502_EMULATOR_JUMP_OPCODE_HANDLER_CONTAINER_H
