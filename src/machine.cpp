#include "machine.h"

#include <iostream>

Machine::Machine(shared_ptr<Program> program) {
    this->program = program;
    memory = make_shared<Memory>(Memory());
    reg_man = make_shared<RegisterManager>(RegisterManager());
    opcode_handler_dir = make_shared<OpcodeHandlerDirectory>(OpcodeHandlerDirectory(program, reg_man, memory));
    instruction_executor =
            make_unique<InstructionExecutor>(InstructionExecutor(program, reg_man, opcode_handler_dir));
}

shared_ptr<Memory> Machine::get_memory() {
    return memory;
}

shared_ptr<RegisterManager> Machine::get_reg_man() {
    return reg_man;
}

void Machine::execute() {
    instruction_executor->execute();
}