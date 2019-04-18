#include "opcode-handler-directory.h"
#include "handler/load-opcode-handler-container.h"
#include "handler/store-opcode-handler-container.h"
#include "handler/transfer-opcode-handler-container.h"
#include "handler/maths-opcode-handler-container.h"
#include "../utils.h"

namespace emu_6502 {

    OpcodeHandlerDirectory::OpcodeHandlerDirectory() : handler_containers{}, handlers{} {
        handler_containers.push_back(make_unique<LoadOpcodeHandlerContainer>());
        handler_containers.push_back(make_unique<StoreOpcodeHandlerContainer>());
        handler_containers.push_back(make_unique<TransferOpcodeHandlerContainer>());
        handler_containers.push_back(make_unique<MathsOpcodeHandlerContainer>());

        init_handlers();
    }

    void OpcodeHandlerDirectory::init_handlers() {
        for (auto& hc : handler_containers) {
            for (auto& h : hc->get_handlers()) {
                handlers.insert({h.first, h.second});
            }
        }
    }

    void OpcodeHandlerDirectory::execute(uint8_t opcode, Machine& machine) {
        auto func = handlers.find(opcode);
        if (func == handlers.end())
            throw runtime_error("No appropriate handler for opcode 0x" + uint_to_hex(opcode));

        func->second(machine);
    }
}