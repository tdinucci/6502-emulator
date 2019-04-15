#ifndef INC_6502_EMULATOR_UTILS_H
#define INC_6502_EMULATOR_UTILS_H

#include "machine/machine.h"
#include <string>
#include <sstream>

using namespace std;

namespace emu_6502 {
    string uint_to_hex(uint64_t value);
    uint8_t get_zpg_address(uint8_t offset);
    uint8_t get_zpg_x_address(uint8_t offset, Cpu& cpu);
    uint8_t get_zpg_y_address(uint8_t offset, Cpu& cpu);
    uint16_t get_abs_address(uint8_t low_byte, uint8_t high_byte);
    uint16_t get_abs_x_address(uint8_t low_byte, uint8_t high_byte, Cpu& cpu);
    uint16_t get_abs_y_address(uint8_t low_byte, uint8_t high_byte, Cpu& cpu);
    uint16_t get_ind_x_address(uint8_t offset, Machine& machine);
    uint16_t get_ind_y_address(uint8_t offset, Machine& machine);
}

#endif // INC_6502_EMULATOR_UTILS_H