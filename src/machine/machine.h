#ifndef INC_6502_EMULATOR_MACHINE_H
#define INC_6502_EMULATOR_MACHINE_H

#include "cpu.h"
#include "memory.h"
#include "stack.h"

#include <memory>
#include <vector>

using namespace std;

namespace emu_6502 {
    class MachineImpl;

    class Machine {
    private:
        unique_ptr<MachineImpl> pimpl;
    public:
        Machine();
        ~Machine();
        Machine(const Machine&) = delete;
        Machine& operator=(const Machine&) = delete;

        Cpu& get_cpu();
        Memory& get_memory();
        Stack& get_stack();

        bool is_eop();
        uint8_t read_program_byte();
        void load(const vector<uint8_t>& program, uint16_t load_at);
        void execute();
    };
}

#endif //INC_6502_EMULATOR_MACHINE_H
