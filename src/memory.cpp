#include "memory.h"
#include <stdexcept>

Memory::Memory() {
    bytes = make_unique<vector<uint8_t>>(vector<uint8_t>(0xFFFF));
    stack = make_unique<Stack>(Stack());
}

void Memory::set_byte_at(uint16_t index, uint8_t value) {
    bytes->at(index) = value;
}

uint8_t Memory::get_byte_at(uint16_t index) {
    return bytes->at(index);
}

void Memory::stack_push(uint8_t data) {
    stack->push(data);
}

uint8_t Memory::stack_pop() {
    return stack->pop();
}