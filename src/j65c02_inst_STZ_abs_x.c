/**
 * \file j65c02_inst_STZ_abs_x.c
 *
 * \brief Handle an STZ abs x instruction.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle an STZ ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_STZ_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint16_t addr;

    /* fetch the address. */
    retval = j65c02_addr_abs_x(inst, &addr);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* store 0 at the address. */
    retval = inst->write(inst->user_context, addr, 0);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* this instruction takes 5 cycles. */
    *cycles = 5;

    return STATUS_SUCCESS;
}
