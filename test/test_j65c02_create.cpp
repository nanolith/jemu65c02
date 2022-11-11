#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_create);

static status dummy_read(void*, uint16_t, uint8_t*)
{
    return -1;
}

static status dummy_write(void*, uint16_t, uint8_t)
{
    return -1;
}

/**
 * Verify that we can create an emulator instance.
 */
TEST(create_basics)
{
    j65c02* inst = nullptr;
    int dummy_context = 1234;

    /* we can create an instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == j65c02_create(
                    &inst, &dummy_read, &dummy_write, &dummy_context,
                    JEMU_65c02_PERSONALITY_MOS,
                    JEMU_65c02_EMULATION_MODE_STRICT));

    /* verify that the personality was set correctly. */
    TEST_EXPECT(JEMU_65c02_PERSONALITY_MOS == j65c02_personality_get(inst));

    /* verify that the emulation mode was set correctly. */
    TEST_EXPECT(
        JEMU_65c02_EMULATION_MODE_STRICT == j65c02_emulation_mode_get(inst));

    /* verify that the A register is zeroed. */
    TEST_EXPECT(0 == j65c02_reg_a_get(inst));

    /* verify that the X register is zeroed. */
    TEST_EXPECT(0 == j65c02_reg_x_get(inst));

    /* verify that the Y register is zeroed. */
    TEST_EXPECT(0 == j65c02_reg_y_get(inst));

    /* verify that the SP register is zeroed. */
    TEST_EXPECT(0 == j65c02_reg_sp_get(inst));

    /* verify that the STATUS register is zeroed. */
    TEST_EXPECT(0 == j65c02_reg_status_get(inst));

    /* verify that the PC register is zeroed. */
    TEST_EXPECT(0 == j65c02_reg_pc_get(inst));

    /* verify that the cycle delta is zeroed. */
    TEST_EXPECT(0 == j65c02_cycle_delta_get(inst));

    /* verify that the processor starts in crashed mode. */
    TEST_EXPECT(j65c02_crash_flag_get(inst));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}

/**
 * Verify that passing an invalid personality causes the create method to fail.
 */
TEST(create_bad_personality)
{
    j65c02* inst = nullptr;
    int dummy_context = 1234;

    /* we can create an instance. */
    TEST_ASSERT(
        JEMU_ERROR_INVALID_PERSONALITY
            == j65c02_create(
                    &inst, &dummy_read, &dummy_write, &dummy_context,
                    17,
                    JEMU_65c02_EMULATION_MODE_STRICT));
}

/**
 * Verify that passing an invalid emulation mode causes the create method to
 * fail.
 */
TEST(create_bad_emulation_mode)
{
    j65c02* inst = nullptr;
    int dummy_context = 1234;

    /* we can create an instance. */
    TEST_ASSERT(
        JEMU_ERROR_INVALID_EMULATION_MODE
            == j65c02_create(
                    &inst, &dummy_read, &dummy_write, &dummy_context,
                    JEMU_65c02_PERSONALITY_MOS,
                    41));
}
