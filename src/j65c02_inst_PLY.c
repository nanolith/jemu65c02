/**
 * \file j65c02_inst_PLY.c
 *
 * \brief Handle a PLY instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle a PLY instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_PLY)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;

    /* pull Y from the stack. */
    retval = j65c02_pull(inst, &inst->reg_y);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if Y is negative, set the negative flag. */
    if (inst->reg_y & 0x80)
    {
        inst->reg_status |= JEMU_65c02_STATUS_NEGATIVE;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_NEGATIVE;
    }

    /* if Y is zero, set the zero flag. */
    if (!inst->reg_y)
    {
        inst->reg_status |= JEMU_65c02_STATUS_ZERO;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_ZERO;
    }

    /* this instruction takes 4 cycles. */
    *cycles = 4;

    return STATUS_SUCCESS;
}
