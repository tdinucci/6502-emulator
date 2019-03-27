#include "stack-opcode-handler.h"
#include <sstream>
#include <climits>

const uint8_t StackOpcodeHandler::PHA;
const uint8_t StackOpcodeHandler::PLA;
const uint8_t StackOpcodeHandler::PHP;
const uint8_t StackOpcodeHandler::PLP;

void StackOpcodeHandler::execute() {
    auto instructionIndex = reg_man->get_program_counter()->get_value();
    auto opcode = program->get_byte_at(instructionIndex);

    switch (opcode) {
        case PHA:
            memory->stack_push(reg_man->get_accumulator()->get_value());
            break;

        case PLA:
            reg_man->get_accumulator()->set_value(memory->stack_pop());
            break;

        case PHP: {
            ulong long_data = reg_man->get_status_register()->get_value().to_ulong();
            auto data = static_cast<uint8_t>(long_data);
            memory->stack_push(data);
            break;
        }

        case PLP: {
            auto data = memory->stack_pop();
            reg_man->get_status_register()->set_value(bitset<8>(data));
            break;
        }

        default:
            stringstream stream;
            stream << "Unexpected opcode 0x" << hex << opcode;
            throw runtime_error(stream.str());
    }

    move_program_counter(1);
}