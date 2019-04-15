#ifndef INC_6502_EMULATOR_CPU_H
#define INC_6502_EMULATOR_CPU_H

#include "register.h"
#include "status-register.h"
#include "program-counter.h"

#include <memory>

using namespace std;

namespace emu_6502 {
    class Cpu {
    private:
        unique_ptr<Register<uint8_t>> a;
        unique_ptr<Register<uint8_t>> x;
        unique_ptr<Register<uint8_t>> y;
        unique_ptr<Register<uint8_t>> sp;
        unique_ptr<ProgramCounter> pc;
        unique_ptr<StatusRegister> ps;

    public:
        Cpu();
        Cpu(const Cpu&) = delete;
        Cpu& operator=(const Cpu&) = delete;

        Register<uint8_t>& get_a();
        Register<uint8_t>& get_x();
        Register<uint8_t>& get_y();
        Register<uint8_t>& get_sp();
        ProgramCounter& get_pc();
        StatusRegister& get_ps();

        void dump();
    };
}

#endif //INC_6502_EMULATOR_CPU_H
