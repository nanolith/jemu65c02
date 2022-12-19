#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

#include "../src/jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_EOR_abs_x);

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
 * 0x5D EOR abs x normal result (not negative or zero).
 */
TEST(step_EOR_abs_x_basics)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_A_VALUE = 0x10;
    const uint8_t EXPECTED_EOR_INPUT = 0x7F;
    const uint8_t EXPECTED_OUTPUT = EXPECTED_A_VALUE ^ EXPECTED_EOR_INPUT;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an EOR instruction. */
    mem[0x1000] = 0x5D;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, add the EOR input. */
    mem[0x2005] = EXPECTED_EOR_INPUT;

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

    /* PRECONDITION: A is set to the expected A value. */
    j65c02_reg_a_set(inst, EXPECTED_A_VALUE);

    /* PRECONDITION: X is set to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: set the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITON: PC is set to 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: PC is set to 0x1003. */
    TEST_EXPECT(0x1003 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: A is set to the expected output. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_OUTPUT);

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x5D EOR abs x Zero result.
 */
TEST(step_EOR_abs_x_zero)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_A_VALUE = 0xFF;
    const uint8_t EXPECTED_EOR_INPUT = 0xFF;
    const uint8_t EXPECTED_OUTPUT = EXPECTED_A_VALUE ^ EXPECTED_EOR_INPUT;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an EOR instruction. */
    mem[0x1000] = 0x5D;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, add the EOR input. */
    mem[0x2005] = EXPECTED_EOR_INPUT;

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

    /* PRECONDITION: A is set to the expected A value. */
    j65c02_reg_a_set(inst, EXPECTED_A_VALUE);

    /* PRECONDITION: X is set to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: clear the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITON: PC is set to 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: PC is set to 0x1003. */
    TEST_EXPECT(0x1003 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: A is set to the expected output. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_OUTPUT);

    /* POSTCONDITION: the zero flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO);

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x5D EOR abs x, the negative flag is set.
 */
TEST(step_EOR_abs_x_negative)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_A_VALUE = 0x80;
    const uint8_t EXPECTED_EOR_INPUT = 0x00;
    const uint8_t EXPECTED_OUTPUT = EXPECTED_A_VALUE ^ EXPECTED_EOR_INPUT;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an EOR instruction. */
    mem[0x1000] = 0x5D;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, add the EOR input. */
    mem[0x2005] = EXPECTED_EOR_INPUT;

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

    /* PRECONDITION: A is set to the expected A value. */
    j65c02_reg_a_set(inst, EXPECTED_A_VALUE);

    /* PRECONDITION: X is set to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: set the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: clear the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITON: PC is set to 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: PC is set to 0x1003. */
    TEST_EXPECT(0x1003 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: A is set to the expected output. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_OUTPUT);

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
