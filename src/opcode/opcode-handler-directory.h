#ifndef INC_6502_EMULATOR_OPCODE_HANDLER_DIRECTORY_H
#define INC_6502_EMULATOR_OPCODE_HANDLER_DIRECTORY_H

#include "../program.h"
#include "../memory.h"
#include "opcode-handler.h"
#include <unordered_map>
#include <vector>
#include <memory>

using namespace std;

class OpcodeHandlerDirectory {
public:
    explicit OpcodeHandlerDirectory(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man, shared_ptr<Memory> memory);

    shared_ptr<OpcodeHandler> get_handler(uint8_t opcode);
private:
    unique_ptr<unordered_map<uint8_t, shared_ptr<OpcodeHandler>>> handlers;

    void register_handler(shared_ptr<OpcodeHandler> handler);
};


#endif //INC_6502_EMULATOR_OPCODE_HANDLER_DIRECTORY_H
