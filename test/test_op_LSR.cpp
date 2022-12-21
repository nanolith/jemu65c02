#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

#include "../src/jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_op_LSR);

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
 * LSR Normal result (not zero; no carry).
 */
TEST(LSR_basics)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    uint8_t val = 0x02;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

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

    /* PRECONDITION: set the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITON: set the carry flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_CARRY);

    /* run the LSR operation. */
    JEMU_SYM(j65c02_op_LSR)(inst, &val);

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: val is set to 0x01. */
    TEST_EXPECT(0x01 == val);

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * LSR high bit set to zero. (not zero; no carry).
 */
TEST(LSR_high_bit)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    uint8_t val = 0x80;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

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

    /* PRECONDITION: set the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITON: set the carry flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_CARRY);

    /* run the LSR operation. */
    JEMU_SYM(j65c02_op_LSR)(inst, &val);

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: val is set to 0x01. */
    TEST_EXPECT(0x40 == val);

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * LSR shift low bit to carry, not zero.
 */
TEST(LSR_low_bit_carry)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    uint8_t val = 0x03;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

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

    /* PRECONDITION: set the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITON: clear the carry flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_CARRY);

    /* run the LSR operation. */
    JEMU_SYM(j65c02_op_LSR)(inst, &val);

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: val is set to 0x01. */
    TEST_EXPECT(0x01 == val);

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * LSR shift low bit to carry, zero.
 */
TEST(LSR_low_bit_carry_zero)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    uint8_t val = 0x01;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

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

    /* PRECONDITION: clear the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITON: clear the carry flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_CARRY);

    /* run the LSR operation. */
    JEMU_SYM(j65c02_op_LSR)(inst, &val);

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: val is set to 0x00. */
    TEST_EXPECT(0x00 == val);

    /* POSTCONDITION: the zero flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO);

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * LSR shift zero is zero.
 */
TEST(LSR_zero)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    uint8_t val = 0x00;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

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

    /* PRECONDITION: clear the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_ZERO);

    /* PRECONDITON: set the negative flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITON: set the carry flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_CARRY);

    /* run the LSR operation. */
    JEMU_SYM(j65c02_op_LSR)(inst, &val);

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: val is set to 0x00. */
    TEST_EXPECT(0x00 == val);

    /* POSTCONDITION: the zero flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO);

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
