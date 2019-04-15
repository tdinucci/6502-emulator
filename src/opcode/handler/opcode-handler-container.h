#ifndef INC_6502_EMULATOR_OPCODE_HANDLER_CONTAINER_H
#define INC_6502_EMULATOR_OPCODE_HANDLER_CONTAINER_H

#include "../../machine/machine.h"

#include <cstdint>
#include <unordered_map>
#include <functional>

namespace emu_6502 {
    class OpcodeHandlerContainer {
    protected:
        unordered_map<uint8_t, function<void(Machine&)>> handlers;

    public:
        OpcodeHandlerContainer();
        OpcodeHandlerContainer(const OpcodeHandlerContainer& other) = delete;

        virtual ~OpcodeHandlerContainer() {};

        const unordered_map<uint8_t, function<void(Machine&)>>& get_handlers();
    };
}
#endif //INC_6502_EMULATOR_OPCODE_HANDLER_CONTAINER_H
