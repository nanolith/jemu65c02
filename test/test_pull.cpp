#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

#include "../src/jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

TEST_SUITE(j65c02_pull);

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
 * Verify that the pull instruction works for an arbitrary stack location.
 */
TEST(pull_basics)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_VAL = 0x12;
    uint8_t val = 0;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* save a value to the stack. */
    mem[0x0150] = EXPECTED_VAL;

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

    /* PRECONDITION: sp is set to 0x4F. */
    j65c02_reg_sp_set(inst, 0x4F);

    /* pull a value off of the stack. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_pull(inst, &val));

    /* POSTCONDITION: sp is incremented. */
    TEST_EXPECT(0x50 == j65c02_reg_sp_get(inst));

    /* POSTCONDITION: val is set to the expected value. */
    TEST_EXPECT(EXPECTED_VAL == val);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * When SP is 0xFF, pull causes it to wrap back around to 0x00.
 */
TEST(push_wrap)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_VAL = 0x12;
    uint8_t val = 0;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* save our value to 0x0100. */
    mem[0x0100] = EXPECTED_VAL;

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

    /* PRECONDITION: sp is set to 0xFF. */
    j65c02_reg_sp_set(inst, 0xFF);

    /* pull a value off of the stack. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_pull(inst, &val));

    /* POSTCONDITION: sp is incremented. */
    TEST_EXPECT(0x00 == j65c02_reg_sp_get(inst));

    /* POSTCONDITION: val is set to our expected value. */
    TEST_EXPECT(EXPECTED_VAL == val);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
