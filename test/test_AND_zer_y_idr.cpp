#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_AND_zer_y_idr);

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
 * 0x31 AND ZER Y IDR.
 */
TEST(step_AND_zer_y_idr)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_AND_INPUT = 0x12;
    const uint8_t EXPECTED_A_VALUE = 0xFF;
    const uint8_t EXPECTED_OUTPUT = EXPECTED_AND_INPUT & EXPECTED_A_VALUE;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an AND instruction. */
    mem[0x1000] = 0x31;
    mem[0x1001] = 0x05;

    /* at zero-page offset 5 and 6, set the address for the input. */
    mem[0x0005] = 0x00;
    mem[0x0006] = 0x20;

    /* at 0x2005, set the and input. */
    mem[0x2005] = EXPECTED_AND_INPUT;

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

    /* PRECONDITION: Y is set to 0x05. */
    j65c02_reg_y_set(inst, 0x05);

    /* PRECONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* PRECONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

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

    /* POSTCONDITION: PC is 0x1002. */
    TEST_EXPECT(0x1002 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: A is set to the output. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_OUTPUT);

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

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
 * 0x31 AND ZER Y IDR zero flag.
 */
TEST(step_AND_zer_y_idr_zero_flag)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_AND_INPUT = 0x12;
    const uint8_t EXPECTED_A_VALUE = 001;
    const uint8_t EXPECTED_OUTPUT = EXPECTED_AND_INPUT & EXPECTED_A_VALUE;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an AND instruction. */
    mem[0x1000] = 0x31;
    mem[0x1001] = 0x05;

    /* at zero-page offset 5 and 6, set the address for the input. */
    mem[0x0005] = 0x00;
    mem[0x0006] = 0x20;

    /* at 0x2005, set the and input. */
    mem[0x2005] = EXPECTED_AND_INPUT;

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

    /* PRECONDITION: Y is set to 0x05. */
    j65c02_reg_y_set(inst, 0x05);

    /* PRECONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* PRECONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

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

    /* POSTCONDITION: PC is 0x1002. */
    TEST_EXPECT(0x1002 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: A is set to the output. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_OUTPUT);

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* POSTCONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* POSTCONDITION: the zero flag is set. */
    TEST_EXPECT((j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x31 AND ZER Y IDR negative flag.
 */
TEST(step_AND_zer_y_idr_negative_flag)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_AND_INPUT = 0x82;
    const uint8_t EXPECTED_A_VALUE = 0x80;
    const uint8_t EXPECTED_OUTPUT = EXPECTED_AND_INPUT & EXPECTED_A_VALUE;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an AND instruction. */
    mem[0x1000] = 0x31;
    mem[0x1001] = 0x05;

    /* at zero-page offset 5 and 6, set the address for the input. */
    mem[0x0005] = 0x00;
    mem[0x0006] = 0x20;

    /* at 0x2005, set the and input. */
    mem[0x2005] = EXPECTED_AND_INPUT;

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

    /* PRECONDITION: Y is set to 0x05. */
    j65c02_reg_y_set(inst, 0x05);

    /* PRECONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* PRECONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

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

    /* POSTCONDITION: PC is 0x1002. */
    TEST_EXPECT(0x1002 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: A is set to the output. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_OUTPUT);

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* POSTCONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the negative flag is set. */
    TEST_EXPECT((j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_NEGATIVE));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
