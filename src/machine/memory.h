#ifndef INC_6502_EMULATOR_MEMORY_H
#define INC_6502_EMULATOR_MEMORY_H

#include <vector>
#include <cstdint>

using namespace std;

namespace emu_6502 {
    class Memory {
    private:
        vector<uint8_t> memory;

        uint16_t get_page_offset(uint8_t page);

    public:
        Memory();
        Memory(const Memory&) = delete;
        Memory& operator=(const Memory&) = delete;

        uint8_t get_at(uint16_t address);
        void set_at(uint16_t address, uint8_t value);

        uint8_t get_from_page(uint8_t page, uint8_t offset);
        void set_on_page(uint8_t page, uint8_t offset, uint8_t value);
    };
}

#endif //INC_6502_EMULATOR_MEMORY_H
