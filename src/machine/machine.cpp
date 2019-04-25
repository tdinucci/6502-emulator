#include "machine.h"
#include "terminal.h"
#include "keyboard.h"
#include "../opcode/opcode-handler-directory.h"

#include <stdexcept>

namespace emu_6502 {
    class MachineImpl {
    private:
        uint16_t code_loaded_at;
        uint16_t code_size;

        uint32_t instruction_iteration;

        unique_ptr<Cpu> cpu;
        unique_ptr<Memory> memory;
        unique_ptr<Stack> stack;
        unique_ptr<Terminal> terminal;
        unique_ptr<Keyboard> keyboard;
        unique_ptr<OpcodeHandlerDirectory> opcode_handler_dir;
    public:
        MachineImpl(bool init_terminal) {
            cpu = make_unique<Cpu>();
            memory = make_unique<Memory>();
            stack = make_unique<Stack>(*memory, cpu->get_sp());
            keyboard = make_unique<Keyboard>(*memory);

            if (init_terminal)
                terminal = make_unique<Terminal>(*memory);

            opcode_handler_dir = make_unique<OpcodeHandlerDirectory>();
        }

        MachineImpl(const MachineImpl&) = delete;
        MachineImpl& operator=(const MachineImpl&) = delete;

        Cpu& get_cpu() {
            return *cpu;
        }

        Memory& get_memory() {
            return *memory;
        }

        Stack& get_stack() {
            return *stack;
        }

        void load(const vector<uint8_t>& program, uint16_t load_at) {
            code_loaded_at = load_at;
            code_size = program.size();
            uint32_t code_end = load_at + code_size;
            if (code_end > 0xFE00) // need space for graphics, interupts, etc.
                throw runtime_error("Program does not fit into memory");

            for (auto i = 0; i < program.size(); i++)
                memory->set_at(load_at + i, program.at(i));

            cpu->get_pc().set_value(load_at);
        }

        bool is_eop() {
            return cpu->get_pc().get_value() >= code_loaded_at + code_size;
        }

        uint8_t read_program_byte() {
            if (is_eop())
                throw runtime_error("Passed end of program");

            auto byte = memory->get_at(cpu->get_pc().get_value());
            cpu->get_pc().inc();

            return byte;
        }

        void execute(Machine& machine) {
            while (!is_eop()) {
                auto byte = read_program_byte();
                opcode_handler_dir->execute(byte, machine);

                if (instruction_iteration++ >= 100) {
                    keyboard->read();
                    instruction_iteration = 0;
                }
            }
        }
    };

    Machine::Machine(bool init_terminal) : pimpl(make_unique<MachineImpl>(init_terminal)) {
    }

    Machine::~Machine() = default;

    Cpu& Machine::get_cpu() {
        return pimpl->get_cpu();
    }

    Memory& Machine::get_memory() {
        return pimpl->get_memory();
    }

    Stack& Machine::get_stack() {
        return pimpl->get_stack();
    }

    void Machine::load(const vector<uint8_t>& program, uint16_t load_at) {
        pimpl->load(program, load_at);
    }

    bool Machine::is_eop() const {
        return pimpl->is_eop();
    }

    uint8_t Machine::read_program_byte() {
        return pimpl->read_program_byte();
    }

    void Machine::execute() {
        pimpl->execute(*this);
    }
}