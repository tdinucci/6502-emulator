#ifndef INC_6502_EMULATOR_INSTRUCTION_EXECUTOR_H
#define INC_6502_EMULATOR_INSTRUCTION_EXECUTOR_H

#include "../program.h"
#include "../register/register-manager.h"
#include "../opcode/opcode-handler-directory.h"

#include <memory>
#include <vector>

using namespace std;

class InstructionExecutor {
public:
    explicit InstructionExecutor(shared_ptr<Program> program, shared_ptr<RegisterManager> reg_man,
            shared_ptr<OpcodeHandlerDirectory> opcode_handler_dir);

    void execute();

private:
    shared_ptr<Program> program;
    shared_ptr<RegisterManager> reg_man;
    shared_ptr<OpcodeHandlerDirectory> opcode_handler_dir;
};


#endif //INC_6502_EMULATOR_INSTRUCTION_EXECUTOR_H
