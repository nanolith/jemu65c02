/**
 * \file j65c02_inst_AND_abs.c
 *
 * \brief Handle an AND abs instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle an AND ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_AND_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint8_t rhs = 0;

    /* fetch the value. */
    retval = j65c02_addr_abs(inst, &rhs);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* perform the AND operation. */
    JEMU_SYM(j65c02_op_AND(inst, rhs));

    /* this mode takes 4 cycles. */
    *cycles = 4;

    return STATUS_SUCCESS;
}
