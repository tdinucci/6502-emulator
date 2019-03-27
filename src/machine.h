#ifndef INC_6502_EMULATOR_MACHINE_H
#define INC_6502_EMULATOR_MACHINE_H

#include "program.h"
#include "memory.h"
#include "register/register-manager.h"
#include "opcode/opcode-handler-directory.h"
#include "instruction/instruction-executor.h"
#include <vector>

using namespace std;

class Machine {
public:
    explicit Machine(shared_ptr<Program> program);

    shared_ptr<RegisterManager> get_reg_man();
    shared_ptr<Memory> get_memory();

    void execute();

private:
    shared_ptr<Program> program;
    shared_ptr<Memory> memory;
    shared_ptr<RegisterManager> reg_man;
    shared_ptr<OpcodeHandlerDirectory> opcode_handler_dir;
    shared_ptr<InstructionExecutor> instruction_executor;
};


#endif //INC_6502_EMULATOR_MACHINE_H
