/**
 * \file j65c02_reset.c
 *
 * \brief Reset the processor state.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Trigger a reset of the processor in the emulator instance.
 *
 * \param inst              The instance to reset.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_reset)(JEMU_SYM(j65c02)* inst)
{
    status retval;

    inst->reg_a = 0;
    inst->reg_x = 0;
    inst->reg_y = 0;
    inst->reg_sp = 0xFD;
    inst->reg_status = JEMU_65c02_STATUS_NC | JEMU_65c02_STATUS_BREAK;
    inst->crash = 0;
    inst->stopped = false;
    inst->wait = false;

    /* read the low PC counter. */
    uint8_t pc_low;
    retval = inst->read(inst->user_context, 0xFFFC, &pc_low);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* set the low PC counter. */
    inst->reg_pc = pc_low;

    /* read the high PC counter. */
    uint8_t pc_high;
    retval = inst->read(inst->user_context, 0xFFFD, &pc_high);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* set the high PC counter. */
    inst->reg_pc |= ((uint16_t)pc_high) << 8;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
