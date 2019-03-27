#ifndef INC_6502_EMULATOR_STX_OPCODE_HANDLER_H
#define INC_6502_EMULATOR_STX_OPCODE_HANDLER_H

#include "../opcode-handler.h"

class StxOpcodeHandler : public OpcodeHandler {
public:
    static const uint8_t ZERO_PAGE = 0x86;
    static const uint8_t ZERO_PAGE_Y = 0x96;
    static const uint8_t ABSOLUTE = 0x8E;

    explicit StxOpcodeHandler(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man,
                              shared_ptr<Memory> memory) :
            OpcodeHandler(program, reg_man, memory) {
        handled_opcodes->push_back(ZERO_PAGE);
        handled_opcodes->push_back(ZERO_PAGE_Y);
        handled_opcodes->push_back(ABSOLUTE);
    }

    virtual void execute() override;
};


#endif //INC_6502_EMULATOR_STX_OPCODE_HANDLER_H
