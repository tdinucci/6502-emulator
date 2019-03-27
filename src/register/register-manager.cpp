#include "register-manager.h"
#include "register.h"
#include <memory>
#include <cstring>

using namespace std;

RegisterManager::RegisterManager() {
    accumulator = std::make_shared<Register<uint8_t>>(Register<uint8_t>("A"));
    x_index = make_shared<Register<uint8_t>>(Register<uint8_t>("X"));
    y_index = make_shared<Register<uint8_t>>(Register<uint8_t>("Y"));
    stack_pointer = make_shared<Register<uint8_t>>(Register<uint8_t>("SP"));
    status_register = make_shared<StatusRegister>(StatusRegister());
    program_counter = make_shared<Register<uint16_t>>(Register<uint16_t>("PC"));
}

shared_ptr<Register<uint8_t>> RegisterManager::get_accumulator() {
    return accumulator;
}

shared_ptr<Register<uint8_t>> RegisterManager::get_x_index() {
    return x_index;
}

shared_ptr<Register<uint8_t>> RegisterManager::get_y_index() {
    return y_index;
}

shared_ptr<Register<uint8_t>> RegisterManager::get_stack_pointer() {
    return stack_pointer;
}

shared_ptr<StatusRegister> RegisterManager::get_status_register() {
    return status_register;
}

shared_ptr<Register<uint16_t>> RegisterManager::get_program_counter() {
    return program_counter;
}