#ifndef INC_6502_EMULATOR_FLAG_OPCODE_HANDLER_H
#define INC_6502_EMULATOR_FLAG_OPCODE_HANDLER_H

#include "../../program.h"
#include "../opcode-handler.h"

class FlagOpcodeHandler : public OpcodeHandler {
public:
    static const uint8_t CLC = 0x18;
    static const uint8_t SEC = 0x38;
    static const uint8_t CLI = 0x58;
    static const uint8_t SEI = 0x78;
    static const uint8_t CLV = 0xB8;
    static const uint8_t CLD = 0xD8;
    static const uint8_t SED = 0xF8;

    explicit FlagOpcodeHandler(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man) :
            OpcodeHandler(program, reg_man) {
        handled_opcodes->push_back(CLC);
        handled_opcodes->push_back(SEC);
        handled_opcodes->push_back(CLI);
        handled_opcodes->push_back(SEI);
        handled_opcodes->push_back(CLV);
        handled_opcodes->push_back(CLD);
        handled_opcodes->push_back(SED);
    }

    virtual void execute() override;
};

#endif //INC_6502_EMULATOR_FLAG_OPCODE_HANDLER_H
