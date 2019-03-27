#include "flag-opcode-handler.h"

#include <stdexcept>
#include <sstream>

const uint8_t FlagOpcodeHandler::CLC;
const uint8_t FlagOpcodeHandler::SEC;
const uint8_t FlagOpcodeHandler::CLI;
const uint8_t FlagOpcodeHandler::SEI;
const uint8_t FlagOpcodeHandler::CLV;
const uint8_t FlagOpcodeHandler::CLD;
const uint8_t FlagOpcodeHandler::SED;

void FlagOpcodeHandler::execute() {
    auto instructionIndex = reg_man->get_program_counter()->get_value();
    auto opcode = program->get_byte_at(instructionIndex);
    auto statusReg = reg_man->get_status_register();

    switch (opcode) {
        case CLC:
            statusReg->set_carry(false);
            break;
        case SEC:
            statusReg->set_carry(true);
            break;
        case CLI:
            statusReg->set_interupt_disable(false);
            break;
        case SEI:
            statusReg->set_interupt_disable(true);
            break;
        case CLV:
            statusReg->set_overflow(false);
            break;
        case CLD:
            statusReg->set_decimal(false);
            break;
        case SED:
            statusReg->set_decimal(true);
            break;
        default:
            stringstream stream;
            stream << "Unexpected opcode 0x" << hex << opcode;
            throw runtime_error(stream.str());
    }

    move_program_counter(1);
}