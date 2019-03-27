#include "lda-opcode-handler.h"

const uint8_t LdaOpcodeHandler::IMMEDIATE;
const uint8_t LdaOpcodeHandler::ZERO_PAGE;
const uint8_t LdaOpcodeHandler::ZERO_PAGE_X;
const uint8_t LdaOpcodeHandler::ABSOLUTE;
const uint8_t LdaOpcodeHandler::ABSOLUTE_X;
const uint8_t LdaOpcodeHandler::ABSOLUTE_Y;
const uint8_t LdaOpcodeHandler::INDIRECT_X;
const uint8_t LdaOpcodeHandler::INDIRECT_Y;

void LdaOpcodeHandler::execute() {
    auto instructionIndex = reg_man->get_program_counter()->get_value();
    auto opcode = program->get_byte_at(instructionIndex);
    auto byte2 = program->get_byte_at(instructionIndex + 1);
    auto accumulator = reg_man->get_accumulator();

    switch (opcode) {
        case IMMEDIATE:
            accumulator->set_value(byte2);
            move_program_counter(2);
            break;

        case ZERO_PAGE:
            accumulator->set_value(memory->get_byte_at(byte2));
            move_program_counter(2);
            break;

        case ZERO_PAGE_X: {
            // expect wrap around
            uint8_t address = byte2 + reg_man->get_x_index()->get_value();

            accumulator->set_value(memory->get_byte_at(address));
            move_program_counter(2);
            break;
        }

        case ABSOLUTE: {
            auto low = byte2;
            auto high = program->get_byte_at(instructionIndex + 2);
            uint16_t address = (high << 8) + low;

            accumulator->set_value(memory->get_byte_at(address));
            move_program_counter(3);
            break;
        }

        case ABSOLUTE_X: {
            auto low = byte2;
            auto high = program->get_byte_at(instructionIndex + 2);
            uint16_t address = (high << 8) + low + reg_man->get_x_index()->get_value();

            accumulator->set_value(memory->get_byte_at(address));
            move_program_counter(3);
            break;
        }

        case ABSOLUTE_Y: {
            auto low = byte2;
            auto high = program->get_byte_at(instructionIndex + 2);
            uint16_t address = (high << 8) + low + reg_man->get_y_index()->get_value();

            accumulator->set_value(memory->get_byte_at(address));
            move_program_counter(3);
            break;
        }

        case INDIRECT_X: {
            auto paddress = reg_man->get_x_index()->get_value() + byte2;
            auto low = memory->get_byte_at(paddress);
            auto high = memory->get_byte_at(paddress + 1);
            uint16_t address = (high << 8) + low;

            accumulator->set_value(memory->get_byte_at(address));
            move_program_counter(2);
            break;
        }

        case INDIRECT_Y : {
            auto initial = byte2;
            auto low = memory->get_byte_at(initial);
            auto high = memory->get_byte_at(initial + 1);
            auto y = reg_man->get_y_index()->get_value();
            uint16_t address = (high << 8) + low + y;

            accumulator->set_value(memory->get_byte_at(address));
            move_program_counter(2);
            break;
        }

        default:
            throw_unexpected_opcode(opcode);
    }
}