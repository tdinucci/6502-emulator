#ifndef INC_6502_EMULATOR_LDX_OPCODE_HANDLER_H
#define INC_6502_EMULATOR_LDX_OPCODE_HANDLER_H

#include "../../program.h"
#include "../opcode-handler.h"

class LdxOpcodeHandler : public OpcodeHandler {
public:
    static const uint8_t IMMEDIATE = 0xA2;
    static const uint8_t ZERO_PAGE = 0xA6;
    static const uint8_t ZERO_PAGE_Y = 0xB6;
    static const uint8_t ABSOLUTE = 0xAE;
    static const uint8_t ABSOLUTE_Y = 0xBE;

    explicit LdxOpcodeHandler(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man,
                              shared_ptr<Memory> memory) :
            OpcodeHandler(program, reg_man, memory) {
        handled_opcodes->push_back(IMMEDIATE);
        handled_opcodes->push_back(ZERO_PAGE);
        handled_opcodes->push_back(ZERO_PAGE_Y);
        handled_opcodes->push_back(ABSOLUTE);
        handled_opcodes->push_back(ABSOLUTE_Y);
    }

    virtual void execute() override;
};

#endif //INC_6502_EMULATOR_LDX_OPCODE_HANDLER_H
