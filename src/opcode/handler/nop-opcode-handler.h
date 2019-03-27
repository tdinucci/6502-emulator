#ifndef INC_6502_EMULATOR_NOP_OPCODE_HANDLER_H
#define INC_6502_EMULATOR_NOP_OPCODE_HANDLER_H

#include "../opcode-handler.h"

class NopOpcodeHandler : public OpcodeHandler {
public:
    static const uint8_t IMPLIED = 0xEA;

    explicit NopOpcodeHandler(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man,
                              shared_ptr<Memory> memory) :
            OpcodeHandler(program, reg_man, memory) {
        handled_opcodes->push_back(IMPLIED);
    }

    virtual void execute() override;
};


#endif //INC_6502_EMULATOR_NOP_OPCODE_HANDLER_H
