#include "stack.h"

#include <stdexcept>

const uint8_t Stack::MAX_SIZE;

Stack::Stack() {
    data = make_unique<stack<uint8_t>>(stack<uint8_t>());
}

void Stack::push(uint8_t byte) {
    if (data->size() >= MAX_SIZE)
        throw runtime_error("Stack overflow");

    data->push(byte);
}

uint8_t Stack::pop() {
    if (data->empty())
        throw runtime_error("Stack is empty");

    auto result = data->top();
    data->pop();

    return result;
}