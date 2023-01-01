#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

#include "../src/jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_SBC_abs_x);

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
 * 0xFD SBC abs x binary subtract without carry.
 */
TEST(step_SBC_abs_x_binary_subtract_no_carry)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_SUB_INPUT = 0x05;
    const uint8_t EXPECTED_A_VALUE = 0x0A;
    const uint8_t EXPECTED_DIFFERENCE = EXPECTED_A_VALUE - EXPECTED_SUB_INPUT;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* add an SBC instruction. */
    mem[0x1000] = 0xFD;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, add the input. */
    mem[0x2005] = EXPECTED_SUB_INPUT;

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

    /* PRECONDITION: A is set to EXPECTED_A_VALUE. */
    j65c02_reg_a_set(inst, EXPECTED_A_VALUE);

    /* PRECONDITION: X is set to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: the carry flag is set to indicate no borrow. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: the decimal flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_DECIMAL);

    /* PRECONDITION: the overflow flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_OVERFLOW);

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

    /* POSTCONDITION: A is set to the difference. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_DIFFERENCE);

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY);

    /* POSTCONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0xFD SBC abs x binary subtract with borrow input.
 */
TEST(step_SBC_abs_x_binary_subtract_with_borrow_input)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_SUB_INPUT = 0x05;
    const uint8_t EXPECTED_A_VALUE = 0x0A;
    const uint8_t EXPECTED_DIFFERENCE =
        EXPECTED_A_VALUE - EXPECTED_SUB_INPUT - 1;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* add an SBC instruction. */
    mem[0x1000] = 0xFD;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, add the input. */
    mem[0x2005] = EXPECTED_SUB_INPUT;

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

    /* PRECONDITION: A is set to EXPECTED_A_VALUE. */
    j65c02_reg_a_set(inst, EXPECTED_A_VALUE);

    /* PRECONDITION: X is set to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: the carry flag is clear to indicate borrow. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: the decimal flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_DECIMAL);

    /* PRECONDITION: the overflow flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_OVERFLOW);

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

    /* POSTCONDITION: A is set to the difference. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_DIFFERENCE);

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY);

    /* POSTCONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0xFD SBC abs x binary subtract causes borrow.
 */
TEST(step_SBC_abs_x_binary_subtract_causes_borrow)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_SUB_INPUT = 0x05;
    const uint8_t EXPECTED_A_VALUE = 0x04;
    const uint8_t EXPECTED_DIFFERENCE = EXPECTED_A_VALUE - EXPECTED_SUB_INPUT;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* add an SBC instruction. */
    mem[0x1000] = 0xFD;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, add the input. */
    mem[0x2005] = EXPECTED_SUB_INPUT;

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

    /* PRECONDITION: A is set to EXPECTED_A_VALUE. */
    j65c02_reg_a_set(inst, EXPECTED_A_VALUE);

    /* PRECONDITION: X is set to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: the carry flag is set to indicate no borrow. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: the decimal flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_DECIMAL);

    /* PRECONDITION: the overflow flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_OVERFLOW);

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

    /* POSTCONDITION: A is set to the difference. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_DIFFERENCE);

    /* POSTCONDITION: the carry flag is clear to indicate borrow. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* POSTCONDITION: the overflow flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW);

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0xFD SBC abs x binary subtract causes zero flag.
 */
TEST(step_SBC_abs_x_binary_subtract_zero)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_SUB_INPUT = 0x05;
    const uint8_t EXPECTED_A_VALUE = 0x05;
    const uint8_t EXPECTED_DIFFERENCE = EXPECTED_A_VALUE - EXPECTED_SUB_INPUT;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* add an SBC instruction. */
    mem[0x1000] = 0xFD;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, add the input. */
    mem[0x2005] = EXPECTED_SUB_INPUT;

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

    /* PRECONDITION: A is set to EXPECTED_A_VALUE. */
    j65c02_reg_a_set(inst, EXPECTED_A_VALUE);

    /* PRECONDITION: X is set to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: the carry flag is set to indicate no borrow. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: the decimal flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_DECIMAL);

    /* PRECONDITION: the overflow flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_OVERFLOW);

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

    /* POSTCONDITION: A is set to the difference. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_DIFFERENCE);

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY);

    /* POSTCONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* POSTCONDITION: the zero flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO);

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0xFD SBC abs x decimal subtract without carry.
 */
TEST(step_SBC_abs_x_decimal_subtract_no_carry)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_SUB_INPUT = 0x01;
    const uint8_t EXPECTED_A_VALUE = 0x10;
    const uint8_t EXPECTED_DIFFERENCE = 0x09;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* add an SBC instruction. */
    mem[0x1000] = 0xFD;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, add the input. */
    mem[0x2005] = EXPECTED_SUB_INPUT;

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

    /* PRECONDITION: A is set to EXPECTED_A_VALUE. */
    j65c02_reg_a_set(inst, EXPECTED_A_VALUE);

    /* PRECONDITION: X is set to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: the carry flag is set to indicate no borrow. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: the decimal flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_DECIMAL);

    /* PRECONDITION: the overflow flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_OVERFLOW);

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

    /* POSTCONDITION: A is set to the difference. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_DIFFERENCE);

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY);

    /* POSTCONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0xFD SBC abs x decimal subtract with borrow input.
 */
TEST(step_SBC_abs_x_decimal_subtract_with_borrow_input)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_SUB_INPUT = 0x01;
    const uint8_t EXPECTED_A_VALUE = 0x10;
    const uint8_t EXPECTED_DIFFERENCE = 0x08;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* add an SBC instruction. */
    mem[0x1000] = 0xFD;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, add the input. */
    mem[0x2005] = EXPECTED_SUB_INPUT;

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

    /* PRECONDITION: A is set to EXPECTED_A_VALUE. */
    j65c02_reg_a_set(inst, EXPECTED_A_VALUE);

    /* PRECONDITION: X is set to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: the carry flag is clear to indicate borrow. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: the decimal flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_DECIMAL);

    /* PRECONDITION: the overflow flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_OVERFLOW);

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

    /* POSTCONDITION: A is set to the difference. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_DIFFERENCE);

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY);

    /* POSTCONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0xFD SBC abs x decimal subtract causes borrow.
 */
TEST(step_SBC_abs_x_decimal_subtract_causes_borrow)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_SUB_INPUT = 0x01;
    const uint8_t EXPECTED_A_VALUE = 0x00;
    const uint8_t EXPECTED_DIFFERENCE = 0x99;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* add an SBC instruction. */
    mem[0x1000] = 0xFD;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, add the input. */
    mem[0x2005] = EXPECTED_SUB_INPUT;

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

    /* PRECONDITION: A is set to EXPECTED_A_VALUE. */
    j65c02_reg_a_set(inst, EXPECTED_A_VALUE);

    /* PRECONDITION: X is set to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: the carry flag is set to indicate no borrow. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: the decimal flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_DECIMAL);

    /* PRECONDITION: the overflow flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_OVERFLOW);

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

    /* POSTCONDITION: A is set to the difference. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_DIFFERENCE);

    /* POSTCONDITION: the carry flag is clear to indicate borrow. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* POSTCONDITION: the overflow flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW);

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0xFD SBC abs x decimal subtract causes zero flag.
 */
TEST(step_SBC_abs_x_decimal_subtract_zero)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_SUB_INPUT = 0x05;
    const uint8_t EXPECTED_A_VALUE = 0x05;
    const uint8_t EXPECTED_DIFFERENCE = EXPECTED_A_VALUE - EXPECTED_SUB_INPUT;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* add an SBC instruction. */
    mem[0x1000] = 0xFD;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, add the input. */
    mem[0x2005] = EXPECTED_SUB_INPUT;

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

    /* PRECONDITION: A is set to EXPECTED_A_VALUE. */
    j65c02_reg_a_set(inst, EXPECTED_A_VALUE);

    /* PRECONDITION: X is set to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: the carry flag is set to indicate no borrow. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: the decimal flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_DECIMAL);

    /* PRECONDITION: the overflow flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_OVERFLOW);

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

    /* POSTCONDITION: A is set to the difference. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_DIFFERENCE);

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY);

    /* POSTCONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* POSTCONDITION: the zero flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO);

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
