#ifndef INC_6502_EMULATOR_REGISTER_H
#define INC_6502_EMULATOR_REGISTER_H

#include <cstdint>
#include <string>

using namespace std;

template <class T>
class Register
{
public:
    explicit Register<T>(string name);

    string get_name();

    T get_value();
    void set_value(T value);

protected:
    T value;

private:
    string name;
};


#endif //INC_6502_EMULATOR_REGISTER_H
