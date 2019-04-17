#ifndef INC_6502_EMULATOR_LOAD_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_LOAD_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"
#include "../../machine/machine.h"

#include <unordered_map>
#include <memory>
#include <functional>

using namespace std;

namespace emu_6502 {
    class LoadOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            LDA_IMM = 0xA9,
            LDA_ZPG = 0xA5,
            LDA_ZPG_X = 0xB5,
            LDA_ABS = 0xAD,
            LDA_ABS_X = 0xBD,
            LDA_ABS_Y = 0xB9,
            LDA_IND_X = 0xA1,
            LDA_IND_Y = 0xB1,

            LDX_IMM = 0xA2,
            LDX_ZPG = 0xA6,
            LDX_ZPG_Y = 0xB6,
            LDX_ABS = 0xAE,
            LDX_ABS_Y = 0xBE,

            LDY_IMM = 0xA0,
            LDY_ZPG = 0xA4,
            LDY_ZPG_X = 0xB4,
            LDY_ABS = 0xAC,
            LDY_ABS_X = 0xBC
        };

        void set_flags(Cpu& machine, Register<uint8_t>& reg);
        void set_from(Machine& machine, Register<uint8_t>& reg, uint16_t address);

        void ld_imm(Machine& machine, Register<uint8_t>& reg);
        void ld_zpg(Machine& machine, Register<uint8_t>& reg);
        void ld_zpg_x(Machine& machine, Register<uint8_t>& reg);
        void ld_zpg_y(Machine& machine, Register<uint8_t>& reg);
        void ld_abs(Machine& machine, Register<uint8_t>& reg);
        void ld_abs_x(Machine& machine, Register<uint8_t>& reg);
        void ld_abs_y(Machine& machine, Register<uint8_t>& reg);
        void ld_ind_x(Machine& machine, Register<uint8_t>& reg);
        void ld_ind_y(Machine& machine, Register<uint8_t>& reg);

    public:
        LoadOpcodeHandlerContainer();
        LoadOpcodeHandlerContainer(const LoadOpcodeHandlerContainer&) = delete;
        LoadOpcodeHandlerContainer& operator=(const LoadOpcodeHandlerContainer&) = delete;
    };
}

#endif //INC_6502_EMULATOR_LOAD_OPCODE_HANDLER_CONTAINER_H
