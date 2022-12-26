/**
 * \file j65c02_inst_RTI.c
 *
 * \brief Handle an RTI instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle an RTI instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_RTI)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint8_t addr_low, addr_high;

    /* pull the status register off of the stack. */
    retval = j65c02_pull(inst, &inst->reg_status);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* mask out BRK. */
    inst->reg_status &= ~JEMU_65c02_STATUS_BREAK;
    /* mask in NC. */
    inst->reg_status |= JEMU_65c02_STATUS_NC;

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
