#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_TYA);

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
 * 0x98 TYA instruction.
 */
TEST(step_TYA)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_Y_VALUE = 0x12;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a TYA. */
    mem[0x1000] = 0x98;

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

    /* PRECONDITION: set Y to the expected Y value. */
    j65c02_reg_y_set(inst, EXPECTED_Y_VALUE);

    /* PRECONDITION: set A to 0. */
    j65c02_reg_a_set(inst, 0);

    /* PRECONDITION: negative flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITION: zero flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1001. */
    TEST_EXPECT(0x1001 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: A is equal to Y. */
    TEST_EXPECT(EXPECTED_Y_VALUE == j65c02_reg_a_get(inst));

    /* POSTCONDITION: negative flag is clear. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* POSTCONDITION: zero flag is clear. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x98 TYA instruction negative result.
 */
TEST(step_TYA_negative)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_Y_VALUE = 0x82;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a TYA. */
    mem[0x1000] = 0x98;

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

    /* PRECONDITION: set Y to the expected Y value. */
    j65c02_reg_y_set(inst, EXPECTED_Y_VALUE);

    /* PRECONDITION: set A to 0. */
    j65c02_reg_a_set(inst, 0);

    /* PRECONDITION: negative flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITION: zero flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1001. */
    TEST_EXPECT(0x1001 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: A is equal to Y. */
    TEST_EXPECT(EXPECTED_Y_VALUE == j65c02_reg_a_get(inst));

    /* POSTCONDITION: negative flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE);

    /* POSTCONDITION: zero flag is clear. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x98 TYA instruction zero flag is set.
 */
TEST(step_TYA_zero)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_Y_VALUE = 0x00;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a TYA. */
    mem[0x1000] = 0x98;

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

    /* PRECONDITION: set Y to the expected Y value. */
    j65c02_reg_y_set(inst, EXPECTED_Y_VALUE);

    /* PRECONDITION: set A to 0xFF. */
    j65c02_reg_a_set(inst, 0xFF);

    /* PRECONDITION: negative flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* PRECONDITION: zero flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_ZERO);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1001. */
    TEST_EXPECT(0x1001 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: A is equal to Y. */
    TEST_EXPECT(EXPECTED_Y_VALUE == j65c02_reg_a_get(inst));

    /* POSTCONDITION: negative flag is clear. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* POSTCONDITION: zero flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
