#include "sty-opcode-handler.h"

const uint8_t StyOpcodeHandler::ZERO_PAGE;
const uint8_t StyOpcodeHandler::ZERO_PAGE_X;
const uint8_t StyOpcodeHandler::ABSOLUTE;

void StyOpcodeHandler::execute() {
    auto instructionIndex = reg_man->get_program_counter()->get_value();
    auto opcode = program->get_byte_at(instructionIndex);
    auto byte2 = program->get_byte_at(instructionIndex + 1);
    auto y_reg = reg_man->get_y_index();

    switch (opcode) {
        case ZERO_PAGE:
            memory->set_byte_at(byte2, y_reg->get_value());
            move_program_counter(2);
            break;

        case ZERO_PAGE_X: {
            // expect wrap around
            uint8_t address = reg_man->get_x_index()->get_value() + byte2;
            memory->set_byte_at(address, y_reg->get_value());
            move_program_counter(2);
            break;
        }

        case ABSOLUTE: {
            auto low = byte2;
            auto high = program->get_byte_at(instructionIndex + 2);
            uint16_t address = (high << 8) + low;
            memory->set_byte_at(address, y_reg->get_value());
            move_program_counter(3);
            break;
        }

        default:
            throw_unexpected_opcode(opcode);
    }
}
