#include "gtest/gtest.h"
#include "test-utils.h"

using namespace std;
using namespace emu_6502;

const uint8_t BCS = 0xB0;
const uint8_t BCC = 0x90;

const uint8_t BEQ = 0xF0;
const uint8_t BNE = 0xD0;

const uint8_t BPL = 0x10;
const uint8_t BMI = 0x30;

const uint8_t BVS = 0x70;
const uint8_t BVC = 0x50;

TEST(BranchOpcodeHandlerContainer, BCS_Take_Forward) {
    auto machine = create_machine({BCS, 0x23});
    machine->get_cpu().get_ps().set_carry(true);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 + 0x23, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BCS_Take_Backward) {
    auto machine = create_machine({BCS, 0xF0});
    machine->get_cpu().get_ps().set_carry(true);

    try {
        machine->execute();
    }
    catch (exception) {
    }

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 - 0xf, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BCS_NotTake) {
    auto machine = create_machine({BCS, 0x23});
    machine->get_cpu().get_ps().set_carry(false);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BCC_Take_Forward) {
    auto machine = create_machine({BCC, 0x23});
    machine->get_cpu().get_ps().set_carry(false);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 + 0x23, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BCC_Take_Backward) {
    auto machine = create_machine({BCC, 0xF0});
    machine->get_cpu().get_ps().set_carry(false);

    try {
        machine->execute();
    }
    catch (exception) {
    }

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 - 0xf, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BCC_NotTake) {
    auto machine = create_machine({BCC, 0x23});
    machine->get_cpu().get_ps().set_carry(true);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BEQ_Take_Forward) {
    auto machine = create_machine({BEQ, 0x23});
    machine->get_cpu().get_ps().set_zero(true);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 + 0x23, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BEQ_Take_Backward) {
    auto machine = create_machine({BEQ, 0xF0});
    machine->get_cpu().get_ps().set_zero(true);

    try {
        machine->execute();
    }
    catch (exception) {
    }

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 - 0xf, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BEQ_NotTake) {
    auto machine = create_machine({BEQ, 0x23});
    machine->get_cpu().get_ps().set_zero(false);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BNE_Take_Forward) {
    auto machine = create_machine({BNE, 0x23});
    machine->get_cpu().get_ps().set_zero(false);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 + 0x23, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BNE_Take_Backward) {
    auto machine = create_machine({BNE, 0xF0});
    machine->get_cpu().get_ps().set_zero(false);

    try {
        machine->execute();
    }
    catch (exception) {
    }

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 - 0xf, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BNE_NotTake) {
    auto machine = create_machine({BNE, 0x23});
    machine->get_cpu().get_ps().set_zero(true);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BPL_Take_Forward) {
    auto machine = create_machine({BPL, 0x23});
    machine->get_cpu().get_ps().set_negative(false);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 + 0x23, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BPL_Take_Backward) {
    auto machine = create_machine({BPL, 0xF0});
    machine->get_cpu().get_ps().set_negative(false);

    try {
        machine->execute();
    }
    catch (exception) {
    }

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 - 0xf, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BPL_NotTake) {
    auto machine = create_machine({BPL, 0x23});
    machine->get_cpu().get_ps().set_negative(true);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BMI_Take_Forward) {
    auto machine = create_machine({BMI, 0x23});
    machine->get_cpu().get_ps().set_negative(true);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 + 0x23, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BMI_Take_Backward) {
    auto machine = create_machine({BMI, 0xF0});
    machine->get_cpu().get_ps().set_negative(true);

    try {
        machine->execute();
    }
    catch (exception) {
    }

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 - 0xf, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BMI_NotTake) {
    auto machine = create_machine({BMI, 0x23});
    machine->get_cpu().get_ps().set_negative(false);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BVS_Take_Forward) {
    auto machine = create_machine({BVS, 0x23});
    machine->get_cpu().get_ps().set_overflow(true);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 + 0x23, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BVS_Take_Backward) {
    auto machine = create_machine({BVS, 0xF0});
    machine->get_cpu().get_ps().set_overflow(true);

    try {
        machine->execute();
    }
    catch (exception) {
    }

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 - 0xf, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BVS_NotTake) {
    auto machine = create_machine({BVS, 0x23});
    machine->get_cpu().get_ps().set_overflow(false);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BVC_Take_Forward) {
    auto machine = create_machine({BVC, 0x23});
    machine->get_cpu().get_ps().set_overflow(false);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 + 0x23, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BVC_Take_Backward) {
    auto machine = create_machine({BVC, 0xF0});
    machine->get_cpu().get_ps().set_overflow(false);

    try {
        machine->execute();
    }
    catch (exception) {
    }

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2 - 0xf, machine->get_cpu().get_pc().get_value());
}

TEST(BranchOpcodeHandlerContainer, BVC_NotTake) {
    auto machine = create_machine({BVC, 0x23});
    machine->get_cpu().get_ps().set_overflow(true);
    machine->execute();

    // + 2 to account for op bytes
    ASSERT_EQ(CODE_LOAD_ADDR + 2, machine->get_cpu().get_pc().get_value());
}
