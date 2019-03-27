#include "../program.h"
#include "opcode-handler.h"

OpcodeHandler::OpcodeHandler(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man) {
    this->program = program;
    this->reg_man = reg_man;
}

void OpcodeHandler::move_program_counter(uint8_t forward_by) {
    auto pc = reg_man->get_program_counter();
    pc->set_value(pc->get_value() + forward_by);
}