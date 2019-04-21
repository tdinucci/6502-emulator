#ifndef INC_6502_EMULATOR_BRANCH_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_BRANCH_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"

namespace emu_6502 {
    class BranchOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            BCS = 0xB0,
            BCC = 0x90,

            BEQ = 0xF0,
            BNE = 0xD0,

            BPL = 0x10,
            BMI = 0x30,

            BVS = 0x70,
            BVC = 0x50
        };

        void bcs(Machine& machine);
        void bcc(Machine& machine);

        void beq(Machine& machine);
        void bne(Machine& machine);

        void bpl(Machine& machine);
        void bmi(Machine& machine);

        void bvs(Machine& machine);
        void bvc(Machine& machine);

    public:
        BranchOpcodeHandlerContainer();
        BranchOpcodeHandlerContainer(const BranchOpcodeHandlerContainer&) = delete;
        BranchOpcodeHandlerContainer& operator=(BranchOpcodeHandlerContainer&) = delete;
    };
}

#endif //INC_6502_EMULATOR_BRANCH_OPCODE_HANDLER_CONTAINER_H
