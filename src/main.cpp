#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include "machine/machine.h"
#include "machine/terminal.h"
#include "machine/memory.h"
#include "opcode/opcode-handler-directory.h"
#include "opcode/handler/load-opcode-handler-container.h"

using namespace std;
using namespace emu_6502;

int main() {
    string binary = "/home/tony/CLionProjects/6502-emulator/sample/a.o65";
    //string binary = "/home/tony/Downloads/6502_functional_test.bin";
    ifstream in(binary, ios::binary);
    if (in.fail())
        throw runtime_error("Failed to read program file");

    vector<uint8_t> code(
            (istreambuf_iterator<char>(in)),
            (istreambuf_iterator<char>()));

    auto machine = make_unique<Machine>();
    machine->load(code, 0x600);
    machine->execute();

    return 0;
}