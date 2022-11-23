/**
 * \file j65c02_inst_ADC_zer_x_idr.c
 *
 * \brief Handle an ADC zer x idr instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Handle an ADC ZER X IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_zer_x_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint8_t offL = 0;
    uint8_t offH = 0;
    uint8_t addrL = 0;
    uint8_t addrH = 0;
    uint8_t rhs = 0;

    /* fetch the zero-page offset. */
    retval = inst->read(inst->user_context, inst->reg_pc++, &offL);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* increment the offset by X. */
    offL += inst->reg_x;

    /* set the high offset to be one plus the low offset. */
    offH = offL + 1;

    /* fetch the low zero-page value. */
    retval = inst->read(inst->user_context, offL, &addrL);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* fetch the high zero-page value. */
    retval = inst->read(inst->user_context, offH, &addrH);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* fetch the value. */
    retval = inst->read(inst->user_context, (addrH << 8) | addrL, &rhs);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* perform the ADC operation. */
    JEMU_SYM(j65c02_op_ADC)(inst, rhs);

    /* this mode normally takes 6 cycles. */
    *cycles = 6;

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
