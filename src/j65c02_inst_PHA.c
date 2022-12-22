/**
 * \file j65c02_inst_PHA.c
 *
 * \brief Handle a PHA instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle an PHA instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_PHA)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;

    /* push A onto the stack. */
    retval = j65c02_push(inst, inst->reg_a);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* this instruction takes 3 cycles. */
    *cycles = 3;

    return STATUS_SUCCESS;
}
