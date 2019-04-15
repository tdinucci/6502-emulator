#include <iostream>
#include <memory>
#include <vector>
#include "machine/machine.h"
#include "machine/terminal.h"
#include "machine/memory.h"
#include "opcode/opcode-handler-directory.h"
#include "opcode/handler/load-opcode-handler-container.h"

using namespace std;
using namespace emu_6502;

int main() {

    vector<uint8_t> code{0xa9, 53, 0xA5, 16};

    auto machine = make_unique<Machine>();
    machine->load(code, 0x600);

    machine->execute();

//    auto memory = make_shared<Memory>();
//    auto term = make_unique<Terminal>(memory);
//
//    term->refresh();



    return 0;
}