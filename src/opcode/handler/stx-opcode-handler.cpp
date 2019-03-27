#include "stx-opcode-handler.h"

const uint8_t StxOpcodeHandler::ZERO_PAGE;
const uint8_t StxOpcodeHandler::ZERO_PAGE_Y;
const uint8_t StxOpcodeHandler::ABSOLUTE;

void StxOpcodeHandler::execute() {
    auto instructionIndex = reg_man->get_program_counter()->get_value();
    auto opcode = program->get_byte_at(instructionIndex);
    auto byte2 = program->get_byte_at(instructionIndex + 1);
    auto x_reg = reg_man->get_x_index();

    switch (opcode) {
        case ZERO_PAGE:
            memory->set_byte_at(byte2, x_reg->get_value());
            move_program_counter(2);
            break;

        case ZERO_PAGE_Y: {
            // expect wrap around
            uint8_t address = reg_man->get_y_index()->get_value() + byte2;
            memory->set_byte_at(address, x_reg->get_value());
            move_program_counter(2);
            break;
        }

        case ABSOLUTE: {
            auto low = byte2;
            auto high = program->get_byte_at(instructionIndex + 2);
            uint16_t address = (high << 8) + low;
            memory->set_byte_at(address, x_reg->get_value());
            move_program_counter(3);
            break;
        }

        default:
            throw_unexpected_opcode(opcode);
    }
}