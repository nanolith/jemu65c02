#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_STX_zer);

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
 * 0x86 STX zer instruction.
 */
TEST(step_STX_zer_basics)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];
    const uint8_t EXPECTED_X_VALUE = 0x12;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an STX instruction. */
    mem[0x1000] = 0x86;
    mem[0x1001] = 0x05;

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

    /* PRECONDITION: set X to the expected X value. */
    j65c02_reg_x_set(inst, EXPECTED_X_VALUE);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1002. */
    TEST_EXPECT(0x1002 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: X is stored in mem[0x0005]. */
    TEST_EXPECT(EXPECTED_X_VALUE == mem[0x0005]);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
