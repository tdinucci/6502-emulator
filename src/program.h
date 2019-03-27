#ifndef INC_6502_EMULATOR_PROGRAM_H
#define INC_6502_EMULATOR_PROGRAM_H

#include <memory>
#include <vector>

using namespace std;

class Program {
public:
    explicit Program(shared_ptr<vector<uint8_t>> bytes);

    uint8_t get_byte_at(uint16_t index);
    uint16_t get_size();

private:
    shared_ptr<vector<uint8_t>> bytes;
};


#endif //INC_6502_EMULATOR_PROGRAM_H
