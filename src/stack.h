#ifndef INC_6502_EMULATOR_STACK_H
#define INC_6502_EMULATOR_STACK_H

#include <memory>
#include <stack>

using namespace std;

class Stack {
public:
    explicit Stack();

    void push(uint8_t byte);
    uint8_t pop();

private:
    static const uint8_t MAX_SIZE = 0xFF;
    unique_ptr<stack<uint8_t>> data;
};


#endif //INC_6502_EMULATOR_STACK_H
