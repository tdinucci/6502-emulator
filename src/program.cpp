#include "program.h"

#include <stdexcept>

Program::Program(shared_ptr<vector<uint8_t>> bytes) {
    this->bytes = bytes;
}

uint16_t Program::get_size() {
    return bytes->size();
}

uint8_t Program::get_byte_at(uint16_t index) {
    auto size = bytes->size();
    if (size == 0 || bytes->size() - 1 < index)
        throw runtime_error("Attempted to read past end of program");

    return bytes->at(index);
}