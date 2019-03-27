#ifndef INC_6502_EMULATOR_MEMORY_H
#define INC_6502_EMULATOR_MEMORY_H

#include "stack.h"
#include <memory>
#include <vector>

using namespace std;

class Memory {
public:
    explicit Memory();

    void set_byte_at(uint16_t index, uint8_t value);
    uint8_t get_byte_at(uint16_t index);

    void stack_push(uint8_t data);
    uint8_t stack_pop();
private:
    unique_ptr<vector<uint8_t>> bytes;
    unique_ptr<Stack> stack;
};


#endif //INC_6502_EMULATOR_MEMORY_H
