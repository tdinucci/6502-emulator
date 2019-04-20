#include "store-opcode-handler-container.h"
#include "../../utils.h"

namespace emu_6502 {
    StoreOpcodeHandlerContainer::StoreOpcodeHandlerContainer() : OpcodeHandlerContainer() {
        handlers.insert({Op::STA_ZPG, [this](Machine& machine) { st_zpg(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::STA_ZPG_X, [this](Machine& machine) { st_zpg_x(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::STA_ABS, [this](Machine& machine) { st_abs(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::STA_ABS_X, [this](Machine& machine) { st_abs_x(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::STA_ABS_Y, [this](Machine& machine) { st_abs_y(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::STA_IND_X, [this](Machine& machine) { st_ind_x(machine, machine.get_cpu().get_a()); }});
        handlers.insert({Op::STA_IND_Y, [this](Machine& machine) { st_ind_y(machine, machine.get_cpu().get_a()); }});

        handlers.insert({Op::STX_ZPG, [this](Machine& machine) { st_zpg(machine, machine.get_cpu().get_x()); }});
        handlers.insert({Op::STX_ZPG_Y, [this](Machine& machine) { st_zpg_y(machine, machine.get_cpu().get_x()); }});
        handlers.insert({Op::STX_ABS, [this](Machine& machine) { st_abs(machine, machine.get_cpu().get_x()); }});

        handlers.insert({Op::STY_ZPG, [this](Machine& machine) { st_zpg(machine, machine.get_cpu().get_y()); }});
        handlers.insert({Op::STY_ZPG_X, [this](Machine& machine) { st_zpg_x(machine, machine.get_cpu().get_y()); }});
        handlers.insert({Op::STY_ABS, [this](Machine& machine) { st_abs(machine, machine.get_cpu().get_y()); }});
    }

    void StoreOpcodeHandlerContainer::store_to(Machine& machine, Register<uint8_t>& reg, uint16_t address) {
        machine.get_memory().set_at(address, reg.get_value());
    }

    void StoreOpcodeHandlerContainer::st_zpg(Machine& machine, Register<uint8_t>& reg) {
        store_to(machine, reg, get_zpg_address(machine));
    }

    void StoreOpcodeHandlerContainer::st_zpg_x(Machine& machine, Register<uint8_t>& reg) {
        store_to(machine, reg, get_zpg_x_address(machine));
    }

    void StoreOpcodeHandlerContainer::st_zpg_y(Machine& machine, Register<uint8_t>& reg) {
        store_to(machine, reg, get_zpg_y_address(machine));
    }

    void StoreOpcodeHandlerContainer::st_abs(Machine& machine, Register<uint8_t>& reg) {
        store_to(machine, reg, get_abs_address(machine));
    }

    void StoreOpcodeHandlerContainer::st_abs_x(Machine& machine, Register<uint8_t>& reg) {
        store_to(machine, reg, get_abs_x_address(machine));
    }

    void StoreOpcodeHandlerContainer::st_abs_y(Machine& machine, Register<uint8_t>& reg) {
        store_to(machine, reg, get_abs_y_address(machine));
    }

    void StoreOpcodeHandlerContainer::st_ind_x(Machine& machine, Register<uint8_t>& reg) {
        store_to(machine, reg, get_ind_x_address(machine));
    }

    void StoreOpcodeHandlerContainer::st_ind_y(Machine& machine, Register<uint8_t>& reg) {
        store_to(machine, reg, get_ind_y_address(machine));
    }
}