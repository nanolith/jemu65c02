#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_ADC_zer_x_idr);

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
 * 0x61 ADC ZER X IDR (test without carry).
 */
TEST(step_ADC_zer_x_idr_without_carry)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_ADD_INPUT = 0x12;
    const uint8_t EXPECTED_A_VALUE = 0x01;
    const uint8_t EXPECTED_SUM = EXPECTED_ADD_INPUT + EXPECTED_A_VALUE;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an ADC instruction. */
    mem[0x1000] = 0x61;
    mem[0x1001] = 0x05;

    /* at zero-page offset A and B, set the address for the input. */
    mem[0x000A] = 0x00;
    mem[0x000B] = 0x20;

    /* at 0x2000, set the add input. */
    mem[0x2000] = EXPECTED_ADD_INPUT;

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

    /* POSTCONDITION: A is set to the sum. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_SUM);

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
 * 0x61 ADC ZER X IDR (test with carry).
 */
TEST(step_ADC_zer_x_idr_with_carry)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_ADD_INPUT = 0x12;
    const uint8_t EXPECTED_A_VALUE = 0x01;
    const uint8_t EXPECTED_SUM = EXPECTED_ADD_INPUT + EXPECTED_A_VALUE;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an ADC instruction. */
    mem[0x1000] = 0x61;
    mem[0x1001] = 0x05;

    /* at zero-page offset A and B, set the address for the input. */
    mem[0x000A] = 0x00;
    mem[0x000B] = 0x20;

    /* at 0x2000, set the add input. */
    mem[0x2000] = EXPECTED_ADD_INPUT;

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

    /* PRECONDITION: the carry flag is set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_CARRY);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1002. */
    TEST_EXPECT(0x1002 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: A is set to the sum plus carry. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_SUM + 1);

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x61 ADC ZER X IDR (test set carry).
 */
TEST(step_ADC_zer_x_idr_set_carry)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_ADD_INPUT = 0x7F;
    const uint8_t EXPECTED_A_VALUE = 0x81;
    const uint8_t EXPECTED_SUM = 0x00;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an ADC instruction. */
    mem[0x1000] = 0x61;
    mem[0x1001] = 0x05;

    /* at zero-page offset A and B, set the address for the input. */
    mem[0x000A] = 0x00;
    mem[0x000B] = 0x20;

    /* at 0x2000, set the add input. */
    mem[0x2000] = EXPECTED_ADD_INPUT;

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

    /* PRECONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* PRECONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* PRECONDITION: clear the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_ZERO);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1002. */
    TEST_EXPECT(0x1002 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: A is set to the sum. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_SUM);

    /* POSTCONDITION: the zero flag is set. */
    TEST_EXPECT((j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT((j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* POSTCONDITION: the overflow flag is not set. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x61 ADC ZER X IDR (overflow 1)
 */
TEST(step_ADC_zer_x_idr_overflow1)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_ADD_INPUT = 0x50;
    const uint8_t EXPECTED_A_VALUE = 0x50;
    const uint8_t EXPECTED_SUM = 0xa0;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an ADC instruction. */
    mem[0x1000] = 0x61;
    mem[0x1001] = 0x05;

    /* at zero-page offset A and B, set the address for the input. */
    mem[0x000A] = 0x00;
    mem[0x000B] = 0x20;

    /* at 0x2000, set the add input. */
    mem[0x2000] = EXPECTED_ADD_INPUT;

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

    /* PRECONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* PRECONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* PRECONDITION: clear the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_ZERO);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1002. */
    TEST_EXPECT(0x1002 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: A is set to the sum. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_SUM);

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the carry flag is not set. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* POSTCONDITION: the overflow flag is set. */
    TEST_EXPECT((j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x61 ADC ZER X IDR (overflow 2)
 */
TEST(step_ADC_zer_x_idr_overflow2)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_ADD_INPUT = 0xd0;
    const uint8_t EXPECTED_A_VALUE = 0x90;
    const uint8_t EXPECTED_SUM = 0x60;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an ADC instruction. */
    mem[0x1000] = 0x61;
    mem[0x1001] = 0x05;

    /* at zero-page offset A and B, set the address for the input. */
    mem[0x000A] = 0x00;
    mem[0x000B] = 0x20;

    /* at 0x2000, set the add input. */
    mem[0x2000] = EXPECTED_ADD_INPUT;

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

    /* PRECONDITION: the carry flag is not set. */
    TEST_EXPECT(0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* PRECONDITION: the overflow flag is not set. */
    TEST_EXPECT(
        0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* PRECONDITION: clear the zero flag. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_ZERO);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1002. */
    TEST_EXPECT(0x1002 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: crash flag is not set. */
    TEST_EXPECT(!j65c02_crash_flag_get(inst));

    /* POSTCONDITION: A is set to the sum. */
    TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_SUM);

    /* POSTCONDITION: the zero flag is not set. */
    TEST_EXPECT(!(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_ZERO));

    /* POSTCONDITION: the carry flag is set. */
    TEST_EXPECT((j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

    /* POSTCONDITION: the overflow flag is set. */
    TEST_EXPECT((j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_OVERFLOW));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0x61 ADC ZER X IDR (BCD no carry).
 */
TEST(step_ADC_zer_x_idr_BCD)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_ADD_INPUT[10] = {
        0x00, 0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88, 0x99 };
    const uint8_t EXPECTED_SUM[10] = {
        0x00, 0x22, 0x44, 0x66, 0x88,
        0x10, 0x32, 0x54, 0x76, 0x98 };
    const uint8_t EXPECTED_CARRY[10] = {
           0,    0,    0,    0,    0,
           1,    1,    1,    1,    1 };

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* create an instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == j65c02_create(
                    &inst, &mem_read, &mem_write, mem,
                    JEMU_65c02_PERSONALITY_WDC,
                    JEMU_65c02_EMULATION_MODE_STRICT));

    /* PRECONDITION: crash flag is set. */
    TEST_EXPECT(j65c02_crash_flag_get(inst));

    for (int i = 0; i <= 10; ++i)
    {
        /* set the reset vector. */
        mem[0xFFFC] = 0x00;
        mem[0xFFFD] = 0x10;

        /* at 0x1000, add an ADC instruction. */
        mem[0x1000] = 0x61;
        mem[0x1001] = 0x05;

        /* at zero-page offset A and B, set the address for the input. */
        mem[0x000A] = 0x00;
        mem[0x000B] = 0x20;

        /* at 0x2000, set the add input. */
        mem[0x2000] = EXPECTED_ADD_INPUT[i];

        /* reset the processor. */
        TEST_ASSERT(STATUS_SUCCESS == j65c02_reset(inst));

        /* PRECONDITION: A is set to the add input. */
        j65c02_reg_a_set(inst, EXPECTED_ADD_INPUT[i]);

        /* PRECONDITION: X is set to 0x05. */
        j65c02_reg_x_set(inst, 0x05);

        /* PRECONDITION: the carry flag is not set. */
        TEST_EXPECT(
            0 == (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));

        /* PRECONDITION: the decimal flag is set. */
        j65c02_reg_status_set(
            inst, j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_DECIMAL);

        /* PRECONDITION: PC is 0x1000. */
        TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

        /* single step. */
        TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

        /* POSTCONDITION: PC is 0x1002. */
        TEST_EXPECT(0x1002 == j65c02_reg_pc_get(inst));

        /* POSTCONDITION: crash flag is not set. */
        TEST_EXPECT(!j65c02_crash_flag_get(inst));

        /* POSTCONDITION: A is set to the sum. */
        TEST_EXPECT(j65c02_reg_a_get(inst) == EXPECTED_SUM[i]);

        /* POSTCONDITION: the carry flag is set based on our array. */
        if (EXPECTED_CARRY[i])
        {
            TEST_EXPECT(
                (j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));
        }
        else
        {
            TEST_EXPECT(
                !(j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_CARRY));
        }
    }

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}


