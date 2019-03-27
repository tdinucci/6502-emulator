#include "instruction-executor.h"
#include <stdexcept>

#include <iostream>

void dump_cpu_state(shared_ptr<RegisterManager> reg_man) {
    cout << "--------------" << endl;
    cout << "A=0x" << hex << (int) reg_man->get_accumulator()->get_value() <<
         " X=0x" << hex << (int) reg_man->get_x_index()->get_value() <<
         " Y=0x" << hex << (int) reg_man->get_y_index()->get_value() << endl;

    cout << "SP=0x" << hex << (int) reg_man->get_stack_pointer()->get_value() <<
         " PC=0x" << hex << (int) reg_man->get_program_counter()->get_value() << endl;

    cout << "NV-BDIZC" << endl <<
         reg_man->get_status_register()->get_value() << endl;
}

InstructionExecutor::InstructionExecutor(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man,
                                         shared_ptr<OpcodeHandlerDirectory> opcode_handler_dir) {
    this->program = program;
    this->reg_man = reg_man;
    this->opcode_handler_dir = opcode_handler_dir;
}

void InstructionExecutor::execute() {
    auto pc = reg_man->get_program_counter();

    do {
        auto opcode = program->get_byte_at(pc->get_value());
        auto handler = opcode_handler_dir->get_handler(opcode);

        handler->execute();

        dump_cpu_state(reg_man);

    } while (pc->get_value() < program->get_size());
}