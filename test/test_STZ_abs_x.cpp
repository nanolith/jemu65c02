#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_STZ_abs_x);

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
 * 0x9E STZ abs x instruction.
 */
TEST(step_STZ_abs_x_basics)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* at 0x1000, add an STZ instruction. */
    mem[0x1000] = 0x9E;
    mem[0x1001] = 0x00;
    mem[0x1002] = 0x20;

    /* at 0x2005, make the value non-zero. */
    mem[0x2005] = 0xFF;

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

    /* PRECONDITION: set X to 0x05. */
    j65c02_reg_x_set(inst, 0x05);

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x1003. */
    TEST_EXPECT(0x1003 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: 0 is stored in mem[0x2005]. */
    TEST_EXPECT(0 == mem[0x2005]);

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
