#include "utils.h"

namespace emu_6502 {
    string uint_to_hex(uint64_t value) {
        stringstream ss;
        ss << hex << value;

        return ss.str();
    }

    uint8_t get_zpg_address(Machine& machine) {
        return machine.read_program_byte();
    }

    uint8_t get_zpg_x_address(Machine& machine) {
        // expect wrap around
        return machine.read_program_byte() + machine.get_cpu().get_x().get_value();
    }

    uint8_t get_zpg_y_address(Machine& machine) {
        // expect wrap around
        return machine.read_program_byte() + machine.get_cpu().get_y().get_value();
    }

    uint16_t get_abs_address(Machine& machine) {
        auto low_byte = machine.read_program_byte();
        auto high_byte = machine.read_program_byte();
        uint16_t address = (high_byte << 8) + low_byte;
        return address;
    }

    uint16_t get_abs_x_address(Machine& machine) {
        auto low_byte = machine.read_program_byte();
        auto high_byte = machine.read_program_byte();
        uint16_t address = (high_byte << 8) + low_byte + machine.get_cpu().get_x().get_value();
        return address;
    }

    uint16_t get_abs_y_address(Machine& machine) {
        auto low_byte = machine.read_program_byte();
        auto high_byte = machine.read_program_byte();
        uint16_t address = (high_byte << 8) + low_byte + machine.get_cpu().get_y().get_value();
        return address;
    }

    uint16_t get_ind_x_address(Machine& machine) {
        uint8_t paddress = machine.get_cpu().get_x().get_value() + machine.read_program_byte();
        auto low = machine.get_memory().get_at(paddress);
        auto high = machine.get_memory().get_at(paddress + 1);
        uint16_t address = (high << 8) + low;

        return address;
    }

    uint16_t get_ind_y_address(Machine& machine) {
        auto offset = machine.read_program_byte();
        auto low = machine.get_memory().get_at(offset);
        auto high = machine.get_memory().get_at(offset + 1);
        auto y = machine.get_cpu().get_y().get_value();
        uint16_t address = (high << 8) + low + y;

        return address;
    }
}