/**
 * \file j65c02_inst_JSR.c
 *
 * \brief Handle a JSR abs instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle a JSR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_JSR)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint16_t addr;

    /* fetch the address. */
    retval = j65c02_addr_abs(inst, &addr);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* decrement PC (we save the PC just before the instruction). */
    --(inst->reg_pc);

    /* push the low byte of PC onto the stack. */
    retval = j65c02_push(inst, inst->reg_pc & 0xFF);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* push the high byte of PC onto the stack. */
    retval = j65c02_push(inst, inst->reg_pc >> 8);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* set PC to the address. */
    inst->reg_pc = addr;

    /* this instruction takes 6 cycles. */
    *cycles = 6;

    return STATUS_SUCCESS;
}
