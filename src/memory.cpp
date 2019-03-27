#include "memory.h"
#include <stdexcept>

Memory::Memory() {
    bytes = make_shared<vector<uint8_t>>(vector<uint8_t>((1024 * 64) - 1));
}

uint8_t Memory::get_byte_at(uint16_t index) {
    auto size = bytes->size();
    if (size == 0 || bytes->size() - 1 < index)
        throw runtime_error("Attempted to read past end of memory");

    return bytes->at(index);
}