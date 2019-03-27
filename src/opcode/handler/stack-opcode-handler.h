#ifndef INC_6502_EMULATOR_STACK_OPCODE_HANDLER_H
#define INC_6502_EMULATOR_STACK_OPCODE_HANDLER_H

#include "../../program.h"
#include "../opcode-handler.h"

class StackOpcodeHandler : public OpcodeHandler {
public:
    static const uint8_t PHA = 0x48;
    static const uint8_t PLA = 0x68;
    static const uint8_t PHP = 0x08;
    static const uint8_t PLP = 0x28;

    explicit StackOpcodeHandler(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man,
                                shared_ptr<Memory> memory) :
            OpcodeHandler(program, reg_man, memory) {
        handled_opcodes->push_back(PHA);
        handled_opcodes->push_back(PLA);
        handled_opcodes->push_back(PHP);
        handled_opcodes->push_back(PLP);
    }

    virtual void execute() override;
};


#endif //INC_6502_EMULATOR_STACK_OPCODE_HANDLER_H
