#ifndef INC_6502_EMULATOR_STATUS_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_STATUS_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"

namespace emu_6502 {
    class StatusOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            CLC = 0x18,
            CLD = 0xD8,
            CLI = 0x58,
            CLV = 0xB8,

            SEC = 0x38,
            SED = 0xF8,
            SEI = 0x78
        };

        void clc(Machine& machine);
        void cld(Machine& machine);
        void cli(Machine& machine);
        void clv(Machine& machine);

        void sec(Machine& machine);
        void sed(Machine& machine);
        void sei(Machine& machine);

    public:
        StatusOpcodeHandlerContainer();
        StatusOpcodeHandlerContainer(const StatusOpcodeHandlerContainer&) = delete;
        StatusOpcodeHandlerContainer& operator=(const StatusOpcodeHandlerContainer&) = delete;
    };
}


#endif //INC_6502_EMULATOR_STATUS_OPCODE_HANDLER_CONTAINER_H
