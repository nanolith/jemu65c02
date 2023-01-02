/**
 * \file j65c02_inst_STA_abs_y.c
 *
 * \brief Handle an STA abs y instruction.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle an STA ABS Y instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_STA_abs_y)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint16_t addr;

    /* fetch the address. */
    retval = j65c02_addr_abs_y(inst, &addr);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* store A at the address. */
    retval = inst->write(inst->user_context, addr, inst->reg_a);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* this instruction takes 5 cycles. */
    *cycles = 5;

    return STATUS_SUCCESS;
}
