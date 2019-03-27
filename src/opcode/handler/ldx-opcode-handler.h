#ifndef INC_6502_EMULATOR_LDX_OPCODE_HANDLER_H
#define INC_6502_EMULATOR_LDX_OPCODE_HANDLER_H

#include "../../program.h"
#include "../opcode-handler.h"

class LdxOpcodeHandler : public OpcodeHandler {
public:
    static const uint8_t IMMEDIATE = 0xA9;
    static const uint8_t ZERO_PAGE = 0xA5;
    static const uint8_t ZERO_PAGE_X = 0xB5;
    static const uint8_t ABSOLUTE = 0xAD;
    static const uint8_t ABSOLUTE_X = 0xBD;
    static const uint8_t ABSOLUTE_Y = 0xB9;
    static const uint8_t INDIRECT_X = 0xA1;
    static const uint8_t INDIRECT_Y = 0xB1;

    explicit LdxOpcodeHandler(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man) :
            OpcodeHandler(program, reg_man) {
        handled_opcodes->push_back(IMMEDIATE);
        handled_opcodes->push_back(ZERO_PAGE);
        handled_opcodes->push_back(ZERO_PAGE_X);
        handled_opcodes->push_back(ABSOLUTE);
        handled_opcodes->push_back(ABSOLUTE_X);
        handled_opcodes->push_back(ABSOLUTE_Y);
        handled_opcodes->push_back(INDIRECT_X);
        handled_opcodes->push_back(INDIRECT_Y);
    }

    virtual void execute() override;
};

#endif //INC_6502_EMULATOR_LDX_OPCODE_HANDLER_H
