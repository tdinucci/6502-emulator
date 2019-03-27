#include "register-opcode-handler.h"

const uint8_t RegisterOpcodeHandler::TAX;
const uint8_t RegisterOpcodeHandler::TXA;
const uint8_t RegisterOpcodeHandler::DEX;
const uint8_t RegisterOpcodeHandler::INX;
const uint8_t RegisterOpcodeHandler::TAY;
const uint8_t RegisterOpcodeHandler::TYA;
const uint8_t RegisterOpcodeHandler::DEY;
const uint8_t RegisterOpcodeHandler::INY;

void RegisterOpcodeHandler::execute() {
    auto instructionIndex = reg_man->get_program_counter()->get_value();
    auto opcode = program->get_byte_at(instructionIndex);
    auto accumulator = reg_man->get_accumulator();
    auto x_index = reg_man->get_x_index();
    auto y_index = reg_man->get_y_index();

    switch (opcode) {
        case TAX:
            x_index->set_value(accumulator->get_value());
            break;

        case TXA:
            accumulator->set_value(x_index->get_value());
            break;

        case DEX:
            x_index->set_value(x_index->get_value() - 1);
            break;

        case INX:
            x_index->set_value(x_index->get_value() + 1);
            break;

        case TAY:
            y_index->set_value(accumulator->get_value());
            break;

        case TYA:
            accumulator->set_value(y_index->get_value());
            break;

        case DEY:
            y_index->set_value(y_index->get_value() - 1);
            break;

        case INY:
            y_index->set_value(y_index->get_value() + 1);
            break;

        default:
            throw_unexpected_opcode(opcode);
    }

    move_program_counter(1);
}
