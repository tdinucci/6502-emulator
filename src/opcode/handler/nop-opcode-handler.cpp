#include "nop-opcode-handler.h"

const uint8_t NopOpcodeHandler::IMPLIED;

void NopOpcodeHandler::execute() {
    auto instructionIndex = reg_man->get_program_counter()->get_value();
    auto opcode = program->get_byte_at(instructionIndex);

    switch (opcode) {
        case IMPLIED:
            move_program_counter(1);
            break;

        default:
            throw_unexpected_opcode(opcode);
    }
}