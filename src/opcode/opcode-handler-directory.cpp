#include "opcode-handler-directory.h"
#include "handler/flag-opcode-handler.h"
#include "handler/register-opcode-handler.h"
#include "handler/lda-opcode-handler.h"
#include "handler/ldx-opcode-handler.h"
#include "handler/stx-opcode-handler.h"
#include "handler/sty-opcode-handler.h"
#include "handler/stack-opcode-handler.h"

#include <sstream>
#include <stdexcept>

OpcodeHandlerDirectory::OpcodeHandlerDirectory(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man, shared_ptr<Memory> memory) {
    handlers = make_unique<unordered_map<uint8_t, shared_ptr<OpcodeHandler>>>();

    register_handler(make_shared<FlagOpcodeHandler>(FlagOpcodeHandler(program, reg_man, memory)));
    register_handler(make_shared<RegisterOpcodeHandler>(RegisterOpcodeHandler(program, reg_man, memory)));
    register_handler(make_shared<LdaOpcodeHandler>(LdaOpcodeHandler(program, reg_man, memory)));
    register_handler(make_shared<LdxOpcodeHandler>(LdxOpcodeHandler(program, reg_man, memory)));
    register_handler(make_shared<StxOpcodeHandler>(StxOpcodeHandler(program, reg_man, memory)));
    register_handler(make_shared<StyOpcodeHandler>(StyOpcodeHandler(program, reg_man, memory)));
    register_handler(make_shared<StackOpcodeHandler>(StackOpcodeHandler(program, reg_man, memory)));
}

void OpcodeHandlerDirectory::register_handler(shared_ptr<OpcodeHandler> handler) {
    for (auto opcode: *handler->get_handled_opcodes()) {
        handlers->insert({opcode, handler});
    }
}

shared_ptr<OpcodeHandler> OpcodeHandlerDirectory::get_handler(uint8_t opcode) {
    if (handlers->find(opcode) == handlers->end()) {
        stringstream stream;
        stream << "No handler registered for opcode 0x" << hex << opcode;
        throw runtime_error(stream.str());
    }

    return handlers->at(opcode);
}