/**
 * \file j65c02_inst_ADC_zer_x.c
 *
 * \brief Handle an ADC zer x instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Handle an ADC ZER X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint8_t off = 0;
    uint8_t rhs = 0;

    /* fetch the zero-page offset. */
    retval = inst->read(inst->user_context, inst->reg_pc++, &off);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* increment the offset by X. */
    off += inst->reg_x;

    /* fetch the zero-page value. */
    retval = inst->read(inst->user_context, off, &rhs);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* perform the ADC operation. */
    JEMU_SYM(j65c02_op_ADC)(inst, rhs);

    /* this mode normally takes 2 cycles. */
    *cycles = 2;

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
