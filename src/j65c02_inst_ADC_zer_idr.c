/**
 * \file j65c02_inst_ADC_zer_idr.c
 *
 * \brief Handle an ADC zer idr instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Handle an ADC ZER IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_zer_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint8_t idx = 0;
    uint8_t addr_low = 0;
    uint8_t addr_high = 0;
    uint8_t rhs = 0;

    /* this instruction is invalid on MOS silicon. */
    if (JEMU_65c02_PERSONALITY_MOS == inst->personality)
    {
        inst->crash = true;
        return JEMU_ERROR_INVALID_OPCODE;
    }

    /* fetch the zero-page index. */
    retval = inst->read(inst->user_context, inst->reg_pc++, &idx);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* fetch the low address from the zero-page. */
    retval = inst->read(inst->user_context, idx++, &addr_low);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* fetch the high address from the zero-page. */
    retval = inst->read(inst->user_context, idx++, &addr_high);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* fetch the value. */
    retval = inst->read(inst->user_context, (addr_high << 8) | addr_low, &rhs);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* perform the ADC operation. */
    JEMU_SYM(j65c02_op_ADC)(inst, rhs);

    /* this mode normally takes 5 cycles. */
    *cycles = 5;

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
