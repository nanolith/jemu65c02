#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_ROL_abs);

static status mem_read(void* varr, uint16_t addr, uint8_t* val)
{
    const uint8_t* arr = (const uint8_t*)varr;

    *val = arr[addr];

    return STATUS_SUCCESS;
}

static status mem_write(void* varr, uint16_t addr, uint8_t val)
{
    uint8_t* arr = (uint8_t*)varr;

    arr[addr] = val;

    return STATUS_SUCCESS;
}

/**
 * 0x2E ROL ABS normal result.
 */
TEST(step_ROL_abs)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_INPUT = 0x20;
    const uint8_t EXPECTED_OUTPUT = 0x40;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a ROL instruction. */
    mem[0x1000] = 0x2E;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2000, add our input. */
    mem[0x2000] = EXPECTED_INPUT;

    /* create an instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == j65c02_create(
                    &inst, &mem_read, &mem_write, mem,
                    JEMU_65c02_PERSONALITY_WDC,
                    JEMU_65c02_EMULATION_MODE_STRICT));

    /* PRECONDITION: crash flag is set. */
    TEST_EXPECT(j65c02_crash_flag_get(inst));

    /* reset the processor. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_reset(inst));

    /* PRECONDITION: the carry flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: set the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1003. */
    TEST_EXPECT(0x1003 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: mem[0x2000] is set to the output. */
    TEST_EXPECT(mem[0x2000] == EXPECTED_OUTPUT);

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x2E ROL ABS carry in.
 */
TEST(step_ROL_abs_carry_in)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_INPUT = 0x20;
    const uint8_t EXPECTED_OUTPUT = 0x41;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a ROL instruction. */
    mem[0x1000] = 0x2E;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2000, add our input. */
    mem[0x2000] = EXPECTED_INPUT;

    /* create an instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == j65c02_create(
                    &inst, &mem_read, &mem_write, mem,
                    JEMU_65c02_PERSONALITY_WDC,
                    JEMU_65c02_EMULATION_MODE_STRICT));

    /* PRECONDITION: crash flag is set. */
    TEST_EXPECT(j65c02_crash_flag_get(inst));

    /* reset the processor. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_reset(inst));

    /* PRECONDITION: the carry flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: set the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1003. */
    TEST_EXPECT(0x1003 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: mem[0x2000] is set to the output. */
    TEST_EXPECT(mem[0x2000] == EXPECTED_OUTPUT);

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x2E ROL ABS non-zero carry result.
 */
TEST(step_ROL_abs_carry_non_zero)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_INPUT = 0x81;
    const uint8_t EXPECTED_OUTPUT = 0x02;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a ROL instruction. */
    mem[0x1000] = 0x2E;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2000, add our input. */
    mem[0x2000] = EXPECTED_INPUT;

    /* create an instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == j65c02_create(
                    &inst, &mem_read, &mem_write, mem,
                    JEMU_65c02_PERSONALITY_WDC,
                    JEMU_65c02_EMULATION_MODE_STRICT));

    /* PRECONDITION: crash flag is set. */
    TEST_EXPECT(j65c02_crash_flag_get(inst));

    /* reset the processor. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_reset(inst));

    /* PRECONDITION: the carry flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: set the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1003. */
    TEST_EXPECT(0x1003 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: mem[0x2000] is set to the output. */
    TEST_EXPECT(mem[0x2000] == EXPECTED_OUTPUT);

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY);

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x2E ROL ABS zero carry result.
 */
TEST(step_ROL_abs_carry_zero)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_INPUT = 0x80;
    const uint8_t EXPECTED_OUTPUT = 0x00;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a ROL instruction. */
    mem[0x1000] = 0x2E;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2000, add our input. */
    mem[0x2000] = EXPECTED_INPUT;

    /* create an instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == j65c02_create(
                    &inst, &mem_read, &mem_write, mem,
                    JEMU_65c02_PERSONALITY_WDC,
                    JEMU_65c02_EMULATION_MODE_STRICT));

    /* PRECONDITION: crash flag is set. */
    TEST_EXPECT(j65c02_crash_flag_get(inst));

    /* reset the processor. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_reset(inst));

    /* PRECONDITION: the carry flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: clear the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1003. */
    TEST_EXPECT(0x1003 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: mem[0x2000] is set to the output. */
    TEST_EXPECT(mem[0x2000] == EXPECTED_OUTPUT);

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY);

    /* POSTCONDITION: the zero flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO);

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x2E ROL ABS negative flag.
 */
TEST(step_ROL_abs_negative)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_INPUT = 0x41;
    const uint8_t EXPECTED_OUTPUT = 0x82;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a ROL instruction. */
    mem[0x1000] = 0x2E;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2000, add our input. */
    mem[0x2000] = EXPECTED_INPUT;

    /* create an instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == j65c02_create(
                    &inst, &mem_read, &mem_write, mem,
                    JEMU_65c02_PERSONALITY_WDC,
                    JEMU_65c02_EMULATION_MODE_STRICT));

    /* PRECONDITION: crash flag is set. */
    TEST_EXPECT(j65c02_crash_flag_get(inst));

    /* reset the processor. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_reset(inst));

    /* PRECONDITION: the carry flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: set the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: clear the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1003. */
    TEST_EXPECT(0x1003 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: mem[0x2000] is set to the output. */
    TEST_EXPECT(mem[0x2000] == EXPECTED_OUTPUT);

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x2E ROL ABS zero result.
 */
TEST(step_ROL_abs_zero)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_INPUT = 0x00;
    const uint8_t EXPECTED_OUTPUT = 0x00;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a ROL instruction. */
    mem[0x1000] = 0x2E;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2000, add our input. */
    mem[0x2000] = EXPECTED_INPUT;

    /* create an instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == j65c02_create(
                    &inst, &mem_read, &mem_write, mem,
                    JEMU_65c02_PERSONALITY_WDC,
                    JEMU_65c02_EMULATION_MODE_STRICT));

    /* PRECONDITION: crash flag is set. */
    TEST_EXPECT(j65c02_crash_flag_get(inst));

    /* reset the processor. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_reset(inst));

    /* PRECONDITION: the carry flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: clear the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1003. */
    TEST_EXPECT(0x1003 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: mem[0x2000] is set to the output. */
    TEST_EXPECT(mem[0x2000] == EXPECTED_OUTPUT);

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* POSTCONDITION: the zero flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO);

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
