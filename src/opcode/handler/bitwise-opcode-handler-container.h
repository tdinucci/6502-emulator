#ifndef INC_6502_EMULATOR_BITWISE_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_BITWISE_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"

namespace emu_6502 {
    class BitwiseOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            AND_IMM = 0x29,
            AND_ZPG = 0x25,
            AND_ZPG_X = 0x35,
            AND_ABS = 0x2D,
            AND_ABS_X = 0x3D,
            AND_ABS_Y = 0x39,
            AND_IND_X = 0x21,
            AND_IND_Y = 0x31,

            ORA_IMM = 0x09,
            ORA_ZPG = 0x05,
            ORA_ZPG_X = 0x15,
            ORA_ABS = 0x0D,
            ORA_ABS_X = 0x1D,
            ORA_ABS_Y = 0x19,
            ORA_IND_X = 0x01,
            ORA_IND_Y = 0x11,

            EOR_IMM = 0x49,
            EOR_ZPG = 0x45,
            EOR_ZPG_X = 0x55,
            EOR_ABS = 0x4D,
            EOR_ABS_X = 0x5D,
            EOR_ABS_Y = 0x59,
            EOR_IND_X = 0x41,
            EOR_IND_Y = 0x51,

            BIT_ZPG = 0x24,
            BIT_ABS = 0x2C,

            ASL_ACC = 0x0A,
            ASL_ZPG = 0x06,
            ASL_ZPG_X = 0x16,
            ASL_ABS = 0x0E,
            ASL_ABS_X = 0x1E,

            LSR_ACC = 0x4A,
            LSR_ZPG = 0x46,
            LSR_ZPG_X = 0x56,
            LSR_ABS = 0x4E,
            LSR_ABS_X = 0x5E,

            ROL_ACC = 0x2A,
            ROL_ZPG = 0x26,
            ROL_ZPG_X = 0x36,
            ROL_ABS = 0x2E,
            ROL_ABS_X = 0x3E,

            ROR_ACC = 0x6A,
            ROR_ZPG = 0x66,
            ROR_ZPG_X = 0x76,
            ROR_ABS = 0x6E,
            ROR_ABS_X = 0x7E,
        };

        void do_and(Machine& machine, uint8_t value);
        void do_and_with(Machine& machine, uint16_t address);
        void and_imm(Machine& machine);
        void and_zpg(Machine& machine);
        void and_zpg_x(Machine& machine);
        void and_abs(Machine& machine);
        void and_abs_x(Machine& machine);
        void and_abs_y(Machine& machine);
        void and_ind_x(Machine& machine);
        void and_ind_y(Machine& machine);

        void do_or(Machine& machine, uint8_t value);
        void do_or_with(Machine& machine, uint16_t address);
        void or_imm(Machine& machine);
        void or_zpg(Machine& machine);
        void or_zpg_x(Machine& machine);
        void or_abs(Machine& machine);
        void or_abs_x(Machine& machine);
        void or_abs_y(Machine& machine);
        void or_ind_x(Machine& machine);
        void or_ind_y(Machine& machine);

        void do_xor(Machine& machine, uint8_t value);
        void do_xor_with(Machine& machine, uint16_t address);
        void xor_imm(Machine& machine);
        void xor_zpg(Machine& machine);
        void xor_zpg_x(Machine& machine);
        void xor_abs(Machine& machine);
        void xor_abs_x(Machine& machine);
        void xor_abs_y(Machine& machine);
        void xor_ind_x(Machine& machine);
        void xor_ind_y(Machine& machine);

        void bit(Machine& machine, uint16_t address);
        void bit_zpg(Machine& machine);
        void bit_abs(Machine& machine);

        void asl_at(Machine& machine, uint16_t address);
        void asl_acc(Machine& machine);
        void asl_zpg(Machine& machine);
        void asl_zpg_x(Machine& machine);
        void asl_abs(Machine& machine);
        void asl_abs_x(Machine& machine);

        void lsr_at(Machine& machine, uint16_t address);
        void lsr_acc(Machine& machine);
        void lsr_zpg(Machine& machine);
        void lsr_zpg_x(Machine& machine);
        void lsr_abs(Machine& machine);
        void lsr_abs_x(Machine& machine);

        void rol_at(Machine& machine, uint16_t address);
        void rol_acc(Machine& machine);
        void rol_zpg(Machine& machine);
        void rol_zpg_x(Machine& machine);
        void rol_abs(Machine& machine);
        void rol_abs_x(Machine& machine);



    public:
        BitwiseOpcodeHandlerContainer();
        BitwiseOpcodeHandlerContainer(const BitwiseOpcodeHandlerContainer& other) = delete;
        BitwiseOpcodeHandlerContainer operator=(const BitwiseOpcodeHandlerContainer& other) = delete;
    };
}


#endif //INC_6502_EMULATOR_BITWISE_OPCODE_HANDLER_CONTAINER_H
