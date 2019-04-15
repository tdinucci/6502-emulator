#include "utils.h"

namespace emu_6502 {
    string uint_to_hex(uint64_t value) {
        stringstream ss;
        ss << hex << value;

        return ss.str();
    }

    uint8_t get_zpg_address(uint8_t offset) {
        return offset;
    }

    uint8_t get_zpg_x_address(uint8_t offset, Cpu& cpu) {
        // expect wrap around
        return offset + cpu.get_x().get_value();
    }

    uint8_t get_zpg_y_address(uint8_t offset, Cpu& cpu) {
        // expect wrap around
        return offset + cpu.get_y().get_value();
    }

    uint16_t get_abs_address(uint8_t low_byte, uint8_t high_byte) {
        uint16_t address = (high_byte << 8) + low_byte;
        return address;
    }

    uint16_t get_abs_x_address(uint8_t low_byte, uint8_t high_byte, Cpu& cpu) {
        uint16_t address = (high_byte << 8) + low_byte + cpu.get_x().get_value();
        return address;
    }

    uint16_t get_abs_y_address(uint8_t low_byte, uint8_t high_byte, Cpu& cpu) {
        uint16_t address = (high_byte << 8) + low_byte + cpu.get_y().get_value();
        return address;
    }

    uint16_t get_ind_x_address(uint8_t offset, Machine& machine) {
        uint8_t paddress = machine.get_cpu().get_x().get_value() + offset;
        auto low = machine.get_memory().get_at(paddress);
        auto high = machine.get_memory().get_at(paddress + 1);
        uint16_t address = (high << 8) + low;

        return address;
    }

    uint16_t get_ind_y_address(uint8_t offset, Machine& machine) {
        auto low = machine.get_memory().get_at(offset);
        auto high = machine.get_memory().get_at(offset + 1);
        auto y = machine.get_cpu().get_y().get_value();
        uint16_t address = (high << 8) + low + y;

        return address;
    }
}