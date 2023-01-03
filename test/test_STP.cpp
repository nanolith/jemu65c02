#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_STP);

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
 * 0xDB STP instruction.
 */
TEST(step_STP)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a STP instruction. */
    mem[0x1000] = 0xDB;

    /* at 0x1000, add a NOP instruction. */
    mem[0x1001] = 0xEA;

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

    /* PRECONDITION: processor is NOT stopped. */
    TEST_EXPECT(!j65c02_stopped_flag_get(inst));

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1001. */
    TEST_EXPECT(0x1001 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: processor is stopped. */
    TEST_EXPECT(j65c02_stopped_flag_get(inst));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * 0xDB STP instruction halts the processor until it is reset.
 */
TEST(step_STP_reset)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add a STP instruction. */
    mem[0x1000] = 0xDB;

    /* at 0x1000, add a NOP instruction. */
    mem[0x1001] = 0xEA;

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

    /* PRECONDITION: processor is NOT stopped. */
    TEST_EXPECT(!j65c02_stopped_flag_get(inst));

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1001. */
    TEST_EXPECT(0x1001 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: processor is stopped. */
    TEST_EXPECT(j65c02_stopped_flag_get(inst));

    /* single step should fail with a stopped error. */
    TEST_ASSERT(JEMU_ERROR_PROCESSOR_STOPPED == j65c02_step(inst));

    /* reset the processor. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_reset(inst));

    /* PRECONDITION: processor is NOT stopped. */
    TEST_EXPECT(!j65c02_stopped_flag_get(inst));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}