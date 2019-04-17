#ifndef INC_6502_EMULATOR_STORE_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_STORE_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"
#include "../../machine/machine.h"

#include <unordered_map>
#include <memory>
#include <functional>

using namespace std;

namespace emu_6502 {
    class StoreOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            STA_ZPG = 0x85,
            STA_ZPG_X = 0x95,
            STA_ABS = 0x8D,
            STA_ABS_X = 0x9D,
            STA_ABS_Y = 0x99,
            STA_IND_X = 0x81,
            STA_IND_Y = 0x91,

            STX_ZPG = 0x86,
            STX_ZPG_Y = 0x96,
            STX_ABS = 0x8E,

            STY_ZPG = 0x84,
            STY_ZPG_X = 0x94,
            STY_ABS = 0x8C,
        };

        void store_to(Machine& machine, Register<uint8_t>& reg, uint16_t address);

        void st_zpg(Machine& machine, Register<uint8_t>& reg);
        void st_zpg_x(Machine& machine, Register<uint8_t>& reg);
        void st_zpg_y(Machine& machine, Register<uint8_t>& reg);
        void st_abs(Machine& machine, Register<uint8_t>& reg);
        void st_abs_x(Machine& machine, Register<uint8_t>& reg);
        void st_abs_y(Machine& machine, Register<uint8_t>& reg);
        void st_ind_x(Machine& machine, Register<uint8_t>& reg);
        void st_ind_y(Machine& machine, Register<uint8_t>& reg);

    public:
        StoreOpcodeHandlerContainer();
        StoreOpcodeHandlerContainer(const StoreOpcodeHandlerContainer& other) = delete;
    };
}


#endif //INC_6502_EMULATOR_STORE_OPCODE_HANDLER_CONTAINER_H
