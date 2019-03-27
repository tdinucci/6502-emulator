#include "register.h"
#include <stdexcept>
#include <bitset>

using namespace std;

template<class T>
Register<T>::Register(string name) {
    this->name = name;
    this->value = 0;
}

template<class T>
string Register<T>::get_name() {
    return name;
}

template<class T>
T Register<T>::get_value() {
    return value;
}

template<class T>
void Register<T>::set_value(T value) {
    this->value = value;
}

template class Register<uint8_t>;
template class Register<uint16_t>;
template class Register<bitset<8>>;