#include "register.h"

namespace emu_6502 {
    template<typename T>
    Register<T>::Register(string name) {
        this->name = name;
        this->value = 0;
    }

    template<class T>
    void Register<T>::set_value(T value) {
        this->value = value;
    }

    template<typename T>
    T Register<T>::get_value() const {
        return value;
    }

    template<typename T>
    const string& Register<T>::get_name() const {
        return name;
    }
}

template
class emu_6502::Register<uint8_t>;

template
class emu_6502::Register<uint16_t>;

template
class emu_6502::Register<bitset<8>>;