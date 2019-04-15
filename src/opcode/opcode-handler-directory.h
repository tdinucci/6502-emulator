#ifndef INC_6502_EMULATOR_OPCODE_HANDLER_DIRECTORY_H
#define INC_6502_EMULATOR_OPCODE_HANDLER_DIRECTORY_H

#include "handler/opcode-handler-container.h"
#include "../machine/machine.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

namespace emu_6502 {
    class OpcodeHandlerDirectory {
    private:
        vector<unique_ptr<OpcodeHandlerContainer>> handler_containers;
        unordered_map<uint8_t, function<void(Machine&)>> handlers;

        void init_handlers();

    public:
        OpcodeHandlerDirectory();
        OpcodeHandlerDirectory(const OpcodeHandlerDirectory&) = delete;
        OpcodeHandlerDirectory& operator=(const OpcodeHandlerDirectory&) = delete;

        void execute(uint8_t opcode, Machine& machine);
    };
}

#endif //INC_6502_EMULATOR_OPCODE_HANDLER_DIRECTORY_H
