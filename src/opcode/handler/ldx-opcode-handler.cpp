#include "ldx-opcode-handler.h"
#include <sstream>

const uint8_t LdxOpcodeHandler::IMMEDIATE;
const uint8_t LdxOpcodeHandler::ZERO_PAGE;
const uint8_t LdxOpcodeHandler::ZERO_PAGE_X;
const uint8_t LdxOpcodeHandler::ABSOLUTE;
const uint8_t LdxOpcodeHandler::ABSOLUTE_X;
const uint8_t LdxOpcodeHandler::ABSOLUTE_Y;
const uint8_t LdxOpcodeHandler::INDIRECT_X;
const uint8_t LdxOpcodeHandler::INDIRECT_Y;

void LdxOpcodeHandler::execute() {
    auto instructionIndex = reg_man->get_program_counter()->get_value();
    auto opcode = program->get_byte_at(instructionIndex);
    auto byte2 = program->get_byte_at(instructionIndex + 1);
    auto accumulator = reg_man->get_accumulator();

    switch (opcode) {
        case IMMEDIATE:
            accumulator->set_value(byte2);
            move_program_counter(2);
            break;

        default:
            stringstream stream;
            stream << "Unexpected opcode 0x" << hex << opcode;
            throw runtime_error(stream.str());
    }
}