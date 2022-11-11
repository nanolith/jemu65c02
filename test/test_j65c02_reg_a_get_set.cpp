#include <minunit/minunit.h>
#include <jemu65c02/jemu65c02.h>

JEMU_IMPORT_jemu65c02;

TEST_SUITE(j65c02_reg_a_get_set);

static status dummy_read(void*, uint16_t, uint8_t*)
{
    return -1;
}

static status dummy_write(void*, uint16_t, uint8_t)
{
    return -1;
}

/**
 * Verify that we can set and get the A register.
 */
TEST(get_set_basics)
{
    j65c02* inst = nullptr;
    int dummy_context = 1234;
    const uint8_t EXPECTED_VALUE = 0x32;

    /* we can create an instance. */
    TEST_ASSERT(
        STATUS_SUCCESS
            == j65c02_create(
                    &inst, &dummy_read, &dummy_write, &dummy_context,
                    JEMU_65c02_PERSONALITY_MOS,
                    JEMU_65c02_EMULATION_MODE_STRICT));

    /* PRECONDITION: A is NOT the expected value. */
    TEST_ASSERT(EXPECTED_VALUE != j65c02_reg_a_get(inst));

    /* Set A to the expected value. */
    j65c02_reg_a_set(inst, EXPECTED_VALUE);

    /* POSTCONDITION: A is the expected value. */
    TEST_EXPECT(EXPECTED_VALUE == j65c02_reg_a_get(inst));

    /* clean up. */
    TEST_ASSERT(STATUS_SUCCESS == j65c02_release(inst));
}
