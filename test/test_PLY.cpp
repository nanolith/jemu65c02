#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_PLY);

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
 * 0x7A PLY instruction.
 */
TEST(step_PLY)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_VAL = 0x38;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a PLY instruction. */
    mem[0x1000] = 0x7A;

    /* at 0x0150, set our expected value. */
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

    /* PRECONDITION: Y is set to 0x00. */
    j65c02_reg_y_set(inst, 0x00);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* PRECONDITION: stack pointer is 0x4F. */
    j65c02_reg_sp_set(inst, 0x4F);

    /* PRECONDITION: the zero flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITION: the negative flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1001. */
    TEST_EXPECT(0x1001 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: SP is 0x50. */
    TEST_EXPECT(0x50 == j65c02_reg_sp_get(inst));

    /* POSTCONDITION: Y is set to our expected value. */
    TEST_EXPECT(EXPECTED_VAL == j65c02_reg_y_get(inst));

    /* POSTCONDITION: the zero flag is clear. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is clear. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x7A PLY if the pulled value is zero, the zero flag is set.
 */
TEST(step_PLY_zero)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_VAL = 0x00;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a PLY instruction. */
    mem[0x1000] = 0x7A;

    /* at 0x0150, set our expected value. */
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

    /* PRECONDITION: Y is set to 0x00. */
    j65c02_reg_y_set(inst, 0x00);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* PRECONDITION: stack pointer is 0x4F. */
    j65c02_reg_sp_set(inst, 0x4F);

    /* PRECONDITION: the zero flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_ZERO);

    /* PRECONDITION: the negative flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_NEGATIVE);

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1001. */
    TEST_EXPECT(0x1001 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: SP is 0x50. */
    TEST_EXPECT(0x50 == j65c02_reg_sp_get(inst));

    /* POSTCONDITION: Y is set to our expected value. */
    TEST_EXPECT(EXPECTED_VAL == j65c02_reg_y_get(inst));

    /* POSTCONDITION: the zero flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO);

    /* POSTCONDITION: the negative flag is clear. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x7A PLY if the pulled value is negative, the negative flag is set.
 */
TEST(step_PLY_negative)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_VAL = 0x82;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a PLY instruction. */
    mem[0x1000] = 0x7A;

    /* at 0x0150, set our expected value. */
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

    /* PRECONDITION: Y is set to 0x00. */
    j65c02_reg_y_set(inst, 0x00);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* PRECONDITION: stack pointer is 0x4F. */
    j65c02_reg_sp_set(inst, 0x4F);

    /* PRECONDITION: the zero flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_ZERO);

    /* PRECONDITION: the negative flag is clear. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_NEGATIVE);

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1001. */
    TEST_EXPECT(0x1001 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: SP is 0x50. */
    TEST_EXPECT(0x50 == j65c02_reg_sp_get(inst));

    /* POSTCONDITION: Y is set to our expected value. */
    TEST_EXPECT(EXPECTED_VAL == j65c02_reg_y_get(inst));

    /* POSTCONDITION: the zero flag is clear. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is set. */
    TEST_EXPECT(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
