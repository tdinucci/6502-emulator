#ifndef INC_6502_EMULATOR_COMPARE_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_COMPARE_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"

namespace emu_6502 {
    class CompareOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            CMP_IMM = 0xC9,
            CMP_ZPG = 0xC5,
            CMP_ZPX_X = 0xD5,
            CMP_ABS = 0xCD,
            CMP_ABS_X = 0xDD,
            CMP_ABS_Y = 0xD9,
            CMP_IND_X = 0xC1,
            CMP_IND_Y = 0xD1,

            CPX_IMM = 0xE0,
            CPX_ZPG = 0xE4,
            CPX_ABS = 0xEC,

            CPY_IMM = 0x0,
            CPY_ZPG = 0x0,
            CPY_ABS = 0x0,
        };

    public:
        CompareOpcodeHandlerContainer();
        CompareOpcodeHandlerContainer(const CompareOpcodeHandlerContainer&) = delete;
        CompareOpcodeHandlerContainer& operator=(CompareOpcodeHandlerContainer&) = delete;
    };
}


#endif //INC_6502_EMULATOR_COMPARE_OPCODE_HANDLER_CONTAINER_H
