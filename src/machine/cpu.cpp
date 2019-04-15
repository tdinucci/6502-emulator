#include "cpu.h"
#include <iostream>

namespace emu_6502 {
    Cpu::Cpu() {
        a = make_unique<Register<uint8_t>>("A");
        x = make_unique<Register<uint8_t>>("X");
        y = make_unique<Register<uint8_t>>("Y");
        sp = make_unique<Register<uint8_t>>("SP");
        pc = make_unique<ProgramCounter>();
        ps = make_unique<StatusRegister>();
    }

    Register<uint8_t>& Cpu::get_a() {
        return *a;
    }

    Register<uint8_t>& Cpu::get_x() {
        return *x;
    }

    Register<uint8_t>& Cpu::get_y() {
        return *y;
    }

    Register<uint8_t>& Cpu::get_sp() {
        return *sp;
    }

    ProgramCounter& Cpu::get_pc() {
        return *pc;
    }

    StatusRegister& Cpu::get_ps() {
        return *ps;
    }

    void Cpu::dump() {
        cout << "--------------" << endl;
        cout << "A=0x" << hex << (int) a->get_value() <<
             " X=0x" << hex << (int) x->get_value() <<
             " Y=0x" << hex << (int) y->get_value() << endl;

        cout << "SP=0x" << hex << (int) sp->get_value() <<
             " PC=0x" << hex << (int) pc->get_value() << endl;

        cout << "NV-BDIZC" << endl << ps->get_value() << endl;
    }
}