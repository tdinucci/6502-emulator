#ifndef INC_6502_EMULATOR_REGISTER_OPCODE_HANDLER_H
#define INC_6502_EMULATOR_REGISTER_OPCODE_HANDLER_H

#include "../../program.h"
#include "../opcode-handler.h"

class RegisterOpcodeHandler : public OpcodeHandler {
public:
    static const uint8_t TAX = 0xAA;
    static const uint8_t TXA = 0x8A;
    static const uint8_t DEX = 0xCA;
    static const uint8_t INX = 0xE8;
    static const uint8_t TAY = 0xA8;
    static const uint8_t TYA = 0x98;
    static const uint8_t DEY = 0x88;
    static const uint8_t INY = 0xC8;

    explicit RegisterOpcodeHandler(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man) :
            OpcodeHandler(program, reg_man) {
        handled_opcodes->push_back(TAX);
        handled_opcodes->push_back(TXA);
        handled_opcodes->push_back(DEX);
        handled_opcodes->push_back(INX);
        handled_opcodes->push_back(TAY);
        handled_opcodes->push_back(TYA);
        handled_opcodes->push_back(DEY);
        handled_opcodes->push_back(INY);
    }

    virtual void execute() override;
};


#endif //INC_6502_EMULATOR_REGISTER_OPCODE_HANDLER_H
