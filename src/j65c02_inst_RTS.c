/**
 * \file j65c02_inst_RTS.c
 *
 * \brief Handle an RTS instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle an RTS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_RTS)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint8_t addr_low, addr_high;

    /* pull in the return address. */
    retval = j65c02_pull(inst, &addr_low);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }
    retval = j65c02_pull(inst, &addr_high);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* set the address. */
    inst->reg_pc = (addr_high << 8) | addr_low;

    /* this instruction takes 6 cycles. */
    *cycles = 6;

    /* success. */
    return STATUS_SUCCESS;
}
