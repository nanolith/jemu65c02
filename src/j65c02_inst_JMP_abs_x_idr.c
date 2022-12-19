/**
 * \file j65c02_inst_JMP_abs_x_idr.c
 *
 * \brief Handle a JMP abs x idr instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle a JMP ABS X IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_JMP_abs_x_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint16_t addr;

    /* fetch the address. */
    retval = j65c02_addr_abs_x_idr(inst, &addr);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* set PC to this address. */
    inst->reg_pc = addr;

    /* this instruction takes 6 cycles. */
    *cycles = 6;

    return STATUS_SUCCESS;
}
