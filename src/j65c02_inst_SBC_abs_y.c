/**
 * \file j65c02_inst_SBC_abs_y.c
 *
 * \brief Handle an SBC abs Y instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle an SBC ABS Y instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_SBC_abs_y)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint8_t rhs;
    uint16_t addr;

    /* fetch the address. */
    retval = j65c02_addr_abs_y(inst, &addr);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* fetch the value at the address. */
    retval = inst->read(inst->user_context, addr, &rhs);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* perform the SBC operation. */
    JEMU_SYM(j65c02_op_SBC)(inst, rhs);

    /* this mode normally takes 4 cycles. */
    *cycles = 4;

    /* add a cycle if we are in BCD mode. */
    if ((inst->reg_status & JEMU_65c02_STATUS_DECIMAL))
    {
        if (
            inst->personality == JEMU_65c02_PERSONALITY_ROCKWELL
         || inst->personality == JEMU_65c02_PERSONALITY_WDC)
        {
            *cycles += 1;
        }
    }

    return STATUS_SUCCESS;
}
