#ifndef INC_6502_EMULATOR_MEMORY_H
#define INC_6502_EMULATOR_MEMORY_H


#include <memory>
#include <vector>

using namespace std;

class Memory {
public:
    explicit Memory();

    uint8_t get_byte_at(uint16_t index);

private:
    shared_ptr<vector<uint8_t>> bytes;
};


#endif //INC_6502_EMULATOR_MEMORY_H
