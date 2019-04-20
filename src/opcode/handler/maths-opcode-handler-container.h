#ifndef INC_6502_EMULATOR_MATHS_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_MATHS_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"

namespace emu_6502 {
    class MathsOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            ADC_IMM = 0x69,
            ADC_ZPG = 0x65,
            ADC_ZPG_X = 0x75,
            ADC_ABS = 0x6D,
            ADC_ABS_X = 0x7D,
            ADC_ABS_Y = 0x79,
            ADC_IND_X = 0x61,
            ADC_IND_Y = 0x71,

            DEC_ZPG = 0xC6,
            DEC_ZPG_X = 0xD6,
            DEC_ABS = 0xCE,
            DEC_ABS_X = 0xDE,

            INC_ZPG = 0xE6,
            INC_ZPG_X = 0xF6,
            INC_ABS = 0xEE,
            INC_ABS_X = 0xFE,

            DEX = 0xCA,
            DEY = 0x88,
            INX = 0xE8,
            INY = 0xC8,

            SBC_IMM = 0x0,
            SBC_ZPG = 0x0,
            SBC_ZPG_X = 0x0,
            SBC_ABS = 0x0,
            SBC_ABS_X = 0x0,
            SBC_ABS_Y = 0x0,
            SBC_IND_X = 0x0,
            SBC_IND_Y = 0x0
        };

        void set_zero_neg(StatusRegister& ps, uint8_t value);

        void adc(Machine& machine, uint8_t value);
        void adc_imm(Machine& machine);
        void adc_zpg(Machine& machine);
        void adc_zpg_x(Machine& machine);
        void adc_abs(Machine& machine);
        void adc_abs_x(Machine& machine);
        void adc_abs_y(Machine& machine);
        void adc_ind_x(Machine& machine);
        void adc_ind_y(Machine& machine);

        void dec(Machine& machine, uint16_t address);
        void dec_zpg(Machine& machine);
        void dec_zpg_x(Machine& machine);
        void dec_abs(Machine& machine);
        void dec_abs_x(Machine& machine);

        void inc(Machine& machine, uint16_t address);
        void inc_zpg(Machine& machine);
        void inc_zpg_x(Machine& machine);
        void inc_abs(Machine& machine);
        void inc_abs_x(Machine& machine);

        void de(Machine& machine, Register<uint8_t>& reg);
        void dex(Machine& machine);
        void dey(Machine& machine);

        void in(Machine& machine, Register<uint8_t>& reg);
        void inx(Machine& machine);
        void iny(Machine& machine);

        void sbc_imm(Machine& machine);
        void sbc_zpg(Machine& machine);
        void sbc_zpg_x(Machine& machine);
        void sbc_abs(Machine& machine);
        void sbc_abs_x(Machine& machine);
        void sbc_abs_y(Machine& machine);
        void sbc_ind_x(Machine& machine);
        void sbc_ind_y(Machine& machine);

    public:
        MathsOpcodeHandlerContainer();
        MathsOpcodeHandlerContainer(const MathsOpcodeHandlerContainer&) = delete;
        MathsOpcodeHandlerContainer& operator=(const MathsOpcodeHandlerContainer&) = delete;
    };
}


#endif //INC_6502_EMULATOR_MATHS_OPCODE_HANDLER_CONTAINER_H
