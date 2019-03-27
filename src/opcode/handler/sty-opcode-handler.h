#ifndef INC_6502_EMULATOR_STY_OPCODE_HANDLER_H
#define INC_6502_EMULATOR_STY_OPCODE_HANDLER_H

#include "../opcode-handler.h"

class StyOpcodeHandler : public OpcodeHandler {
public:
    static const uint8_t ZERO_PAGE = 0x84;
    static const uint8_t ZERO_PAGE_X = 0x94;
    static const uint8_t ABSOLUTE = 0x8C;

    explicit StyOpcodeHandler(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man,
                              shared_ptr<Memory> memory) :
            OpcodeHandler(program, reg_man, memory) {
        handled_opcodes->push_back(ZERO_PAGE);
        handled_opcodes->push_back(ZERO_PAGE_X);
        handled_opcodes->push_back(ABSOLUTE);
    }

    virtual void execute() override;
};


#endif //INC_6502_EMULATOR_STY_OPCODE_HANDLER_H
