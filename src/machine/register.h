#ifndef INC_6502_EMULATOR_REGISTER_H
#define INC_6502_EMULATOR_REGISTER_H

#include <string>
#include <bitset>

using namespace std;

namespace emu_6502 {
    template<typename T>
    class Register {
    private:
        string name;

    protected:
        T value;

    public:
        Register<T>(string name);
        Register<T>(const Register<T>&) = delete;
        Register<T>& operator=(const Register<T>&) = delete;

        const string& get_name() const;

        T get_value() const;
        void set_value(T value);
    };
}

#endif //INC_6502_EMULATOR_REGISTER_H
