#ifndef INC_6502_EMULATOR_OPCODE_HANDLER_H
#define INC_6502_EMULATOR_OPCODE_HANDLER_H

#include "../program.h"
#include "../memory.h"
#include "../register/register-manager.h"
#include <vector>
#include <memory>

using namespace std;

class OpcodeHandler {
public:
    OpcodeHandler(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man, shared_ptr<Memory> memory);

    virtual void execute() = 0;

    shared_ptr<vector<uint8_t>> get_handled_opcodes() { return handled_opcodes; }
    void throw_unexpected_opcode(uint8_t opcode);

protected:
    shared_ptr<vector<uint8_t>> handled_opcodes = make_shared<vector<uint8_t>>();
    shared_ptr<Program> program;
    shared_ptr<Memory> memory;
    shared_ptr<RegisterManager> reg_man;

    void move_program_counter(uint8_t forward_by);
};


#endif //INC_6502_EMULATOR_OPCODE_HANDLER_H
