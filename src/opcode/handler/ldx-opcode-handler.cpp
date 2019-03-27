#include "ldx-opcode-handler.h"
#include <sstream>

const uint8_t LdxOpcodeHandler::IMMEDIATE;
const uint8_t LdxOpcodeHandler::ZERO_PAGE;
const uint8_t LdxOpcodeHandler::ZERO_PAGE_Y;
const uint8_t LdxOpcodeHandler::ABSOLUTE;
const uint8_t LdxOpcodeHandler::ABSOLUTE_Y;

void LdxOpcodeHandler::execute() {
    auto instructionIndex = reg_man->get_program_counter()->get_value();
    auto opcode = program->get_byte_at(instructionIndex);
    auto byte2 = program->get_byte_at(instructionIndex + 1);
    auto x_reg = reg_man->get_x_index();

    switch (opcode) {
        case IMMEDIATE:
            x_reg->set_value(byte2);
            move_program_counter(2);
            break;

        case ZERO_PAGE:
            x_reg->set_value(memory->get_byte_at(byte2));
            move_program_counter(2);
            break;

        case ZERO_PAGE_Y: {
            uint16_t address = byte2 + reg_man->get_y_index()->get_value();

            x_reg->set_value(memory->get_byte_at(address));
            move_program_counter(2);
            break;
        }

        case ABSOLUTE: {
            auto low = byte2;
            auto high = program->get_byte_at(instructionIndex + 2);
            uint16_t address = (high << 8) + low;

            x_reg->set_value(memory->get_byte_at(address));
            move_program_counter(3);
            break;
        }

        case ABSOLUTE_Y: {
            auto low = byte2;
            auto high = program->get_byte_at(instructionIndex + 2);
            uint16_t address = (high << 8) + low + reg_man->get_y_index()->get_value();

            x_reg->set_value(memory->get_byte_at(address));
            move_program_counter(3);
            break;
        }

        default:
            stringstream stream;
            stream << "Unexpected opcode 0x" << hex << opcode;
            throw runtime_error(stream.str());
    }
}