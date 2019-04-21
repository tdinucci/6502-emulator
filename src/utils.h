#ifndef INC_6502_EMULATOR_UTILS_H
#define INC_6502_EMULATOR_UTILS_H

#include "machine/machine.h"
#include <string>
#include <sstream>

using namespace std;

namespace emu_6502 {
    string uint_to_hex(uint64_t value);

    void set_zero_and_neg_flags(StatusRegister& ps, uint8_t value);

    uint8_t get_zpg_address(Machine& machine);
    uint8_t get_zpg_x_address(Machine& machine);
    uint8_t get_zpg_y_address(Machine& machine);

    uint16_t get_abs_address(Machine& machine);
    uint16_t get_abs_x_address(Machine& machine);
    uint16_t get_abs_y_address(Machine& machine);

    uint16_t get_ind_address(Machine& machine);
    uint16_t get_ind_x_address(Machine& machine);
    uint16_t get_ind_y_address(Machine& machine);
}

#endif // INC_6502_EMULATOR_UTILS_H