#include "register/register-manager.h"

#include <iostream>
#include <memory>

using namespace std;

void stack_test(string astring) {
    astring.push_back('x');
}

void heap_test(shared_ptr<string> astring){
    astring->push_back('y');
}

int main() {
    auto reg = unique_ptr<Register<uint8_t>>(new Register<uint8_t>("PC"));

    cout << "Register: " << reg->get_name() << " " << to_string(56) << endl;

    string astr = "hello";
    shared_ptr<string> bstr = make_shared<string>("there");

    cout << astr << " - " << bstr->c_str() << endl;

    stack_test(astr);
    heap_test(bstr);

    cout << astr << " - " << bstr->c_str() << endl;

    auto reg_man = new RegisterManager();
    auto accum = reg_man->get_accumulator();

    cout << "****** " << accum->get_name() << " ******" << endl;
    cout << "****** " << reg_man->get_x_index()->get_name() << " ******" << endl;
    cout << "****** " << reg_man->get_y_index()->get_name() << " ******" << endl;
    cout << "****** " << reg_man->get_stack_pointer()->get_name() << " ******" << endl;
    cout << "****** " << reg_man->get_status_register()->get_name() << " ******" << endl;
    cout << "****** " << reg_man->get_program_counter()->get_name() << " ******" << endl;

    return 0;
}