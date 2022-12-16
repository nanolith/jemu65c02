#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>
#include <string.h>

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_BRK);

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
 * 0x00 BRK instruction.
 */
TEST(step_BRK)
{
    j65c02* inst = nullptr;
    uint8_t mem[65536];

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* set the reset vector. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;

    /* set the IRQ vector. */
    mem[0xFFFE] = 0x00;
    mem[0xFFFF] = 0x20;

    /* at 0x1000, add a BRK instruction. */
    mem[0x1000] = 0x00;
    mem[0x1001] = 7;

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

    /* PRECONDITION: PC is 0x1000. */
    TEST_ASSERT(0x1000 == j65c02_reg_pc_get(inst));

    /* PRECONDITION: stack pointer is 0x50. */
    j65c02_reg_sp_set(inst, 0x50);

    /* PRECONDITION: break is not set. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_BREAK);

    /* PRECONDITION: interrupts are enabled. */
    j65c02_reg_status_set(
        inst, j65c02_reg_status_get(inst) & ~JEMU_65c02_STATUS_INTERRUPT);

    /* single step. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_step(inst));

    /* POSTCONDITION: PC is 0x2000. */
    TEST_EXPECT(0x2000 == j65c02_reg_pc_get(inst));

    /* POSTCONDITION: SP is 0x4D. */
    TEST_EXPECT(0x4D == j65c02_reg_sp_get(inst));

    /* POSTCONDITION: 0x0150 is set to 0x02. */
    TEST_EXPECT(0x10 == mem[0x0150]);

    /* POSTCONDITION: 0x014F is set to 0x10. */
    TEST_EXPECT(0x02 == mem[0x014F]);

    /* POSTCONDITION: 0x014E is set to (STATUS | BRK | ~INT). */
    TEST_EXPECT(
        ((j65c02_reg_status_get(inst) | JEMU_65c02_STATUS_BREAK)
          & ~JEMU_65c02_STATUS_INTERRUPT)
            == mem[0x014E]);

    /* POSTCONDITION: interrupts are disabled. */
    TEST_EXPECT((j65c02_reg_status_get(inst) & JEMU_65c02_STATUS_INTERRUPT));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
