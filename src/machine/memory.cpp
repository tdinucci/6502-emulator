#include "memory.h"

namespace emu_6502 {
    inline uint16_t Memory::get_page_offset(uint8_t page) {
        return page * 0xFF;
    }

    Memory::Memory() {
        memory = vector<uint8_t>(0xFFFF);
    }

    uint8_t Memory::get_at(uint16_t address) {
        return memory.at(address);
    }

    void Memory::set_at(uint16_t address, uint8_t value) {
        memory.at(address) = value;
    }

    uint8_t Memory::get_from_page(uint8_t page, uint8_t offset) {
        return get_at(get_page_offset(page) + offset);
    }

    void Memory::set_on_page(uint8_t page, uint8_t offset, uint8_t value) {
        set_at(get_page_offset(page) + offset, value);
    }
}