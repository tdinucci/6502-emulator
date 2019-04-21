#ifndef INC_6502_EMULATOR_COMPARE_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_COMPARE_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"
#include "../../machine/register.h"

namespace emu_6502 {
    class CompareOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            CMP_IMM = 0xC9,
            CMP_ZPG = 0xC5,
            CMP_ZPG_X = 0xD5,
            CMP_ABS = 0xCD,
            CMP_ABS_X = 0xDD,
            CMP_ABS_Y = 0xD9,
            CMP_IND_X = 0xC1,
            CMP_IND_Y = 0xD1,

            CPX_IMM = 0xE0,
            CPX_ZPG = 0xE4,
            CPX_ABS = 0xEC,

            CPY_IMM = 0xC0,
            CPY_ZPG = 0xC4,
            CPY_ABS = 0xCC,
        };

        void cmp(Machine& machine, Register<uint8_t>& reg, uint8_t value);

        void cmp_imm(Machine& machine);
        void cmp_zpg(Machine& machine);
        void cmp_zpg_x(Machine& machine);
        void cmp_abs(Machine& machine);
        void cmp_abs_x(Machine& machine);
        void cmp_abs_y(Machine& machine);
        void cmp_ind_x(Machine& machine);
        void cmp_ind_y(Machine& machine);

        void cpx_imm(Machine& machine);
        void cpx_zpg(Machine& machine);
        void cpx_abs(Machine& machine);

        void cpy_imm(Machine& machine);
        void cpy_zpg(Machine& machine);
        void cpy_abs(Machine& machine);

    public:
        CompareOpcodeHandlerContainer();
        CompareOpcodeHandlerContainer(const CompareOpcodeHandlerContainer&) = delete;
        CompareOpcodeHandlerContainer& operator=(CompareOpcodeHandlerContainer&) = delete;
    };
}


#endif //INC_6502_EMULATOR_COMPARE_OPCODE_HANDLER_CONTAINER_H
