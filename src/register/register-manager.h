#ifndef INC_6502_EMULATOR_REGISTER_MANAGER_H
#define INC_6502_EMULATOR_REGISTER_MANAGER_H

#include "register.h"
#include "status-register.h"
#include <memory>

using namespace std;

class RegisterManager {
public:
    explicit RegisterManager();

    shared_ptr<Register<uint8_t>> get_accumulator();

    shared_ptr<Register<uint8_t>> get_x_index();

    shared_ptr<Register<uint8_t>> get_y_index();

    shared_ptr<Register<uint8_t>> get_stack_pointer();

    shared_ptr<StatusRegister> get_status_register();

    shared_ptr<Register<uint16_t>> get_program_counter();

private:
    shared_ptr<Register<uint8_t>> accumulator;
    shared_ptr<Register<uint8_t>> x_index;
    shared_ptr<Register<uint8_t>> y_index;
    shared_ptr<Register<uint8_t>> stack_pointer;
    shared_ptr<StatusRegister> status_register;
    shared_ptr<Register<uint16_t>> program_counter;
};


#endif //INC_6502_EMULATOR_REGISTER_MANAGER_H
