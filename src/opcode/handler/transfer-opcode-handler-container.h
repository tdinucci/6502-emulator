#ifndef INC_6502_EMULATOR_TRANSFER_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_TRANSFER_OPCODE_HANDLER_CONTAINER_H

#include "opcode-handler-container.h"
#include "../../machine/register.h"

namespace emu_6502 {
    class TransferOpcodeHandlerContainer : public OpcodeHandlerContainer {
    private:
        enum Op {
            TAX = 0xAA,
            TAY = 0xA8,
            TSX = 0xBA,
            TXA = 0x8A,
            TXS = 0x9A,
            TYA = 0x98
        };

        void transfer(Machine& machine, const Register<uint8_t>& source, Register<uint8_t>& dest,
                      bool ignoreFlags = false);

    public:
        TransferOpcodeHandlerContainer();
        TransferOpcodeHandlerContainer(const TransferOpcodeHandlerContainer&) = delete;
        TransferOpcodeHandlerContainer operator=(const TransferOpcodeHandlerContainer&) = delete;
    };
}


#endif //INC_6502_EMULATOR_TRANSFER_OPCODE_HANDLER_CONTAINER_H
