/**
 * \file j65c02_inst_ADC_imm.c
 *
 * \brief Handle an ADC imm instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Handle an ADC IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint8_t rhs = 0;
    uint8_t carry = 0;

    /* fetch the immediate value. */
    retval = inst->read(inst->user_context, inst->reg_pc++, &rhs);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* set a carry if the carry flag is set. */
    if (inst->reg_status & JEMU_65c02_STATUS_CARRY)
    {
        carry = 1;
    }

    /* compute the result. */
    unsigned int lhs = inst->reg_a;
    unsigned int result = lhs;
    result += rhs;
    result += carry;

    /* handle the non-BCD case. */
    if (! (inst->reg_status & JEMU_65c02_STATUS_DECIMAL))
    {
        /* if the result is greater than 255, set the carry flag. */
        if (result > 0xFF)
        {
            inst->reg_status |= JEMU_65c02_STATUS_CARRY;
        }
        /* otherwise, clear it. */
        else
        {
            inst->reg_status &= ~JEMU_65c02_STATUS_CARRY;
        }
    }
    /* BCD case. */
    else
    {
        /* ripple add the lower BCD digit. */
        if ((lhs & 0x0F) + (rhs & 0x0F) + carry > 9)
        {
            result += 6;
        }

        /* ripple the upper BCD digit. */
        if (result > 0x99)
        {
            result += 0x60;
        }

        /* if the result is greater than 0x99, set the carry flag. */
        if (result > 0x99)
        {
            inst->reg_status |= JEMU_65c02_STATUS_CARRY;
        }
        /* otherwise, clear it. */
        else
        {
            inst->reg_status &= ~JEMU_65c02_STATUS_CARRY;
        }
    }

    /* handle the negative flag. */
    if (result & 0x80)
    {
        inst->reg_status |= JEMU_65c02_STATUS_NEGATIVE;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_NEGATIVE;
    }

    /* handle the zero flag. */
    if (0 == (result & 0xFF))
    {
        inst->reg_status |= JEMU_65c02_STATUS_ZERO;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_ZERO;
    }

    /* handle the overflow flag. */
    if ((lhs ^ result) & (rhs ^ result) & 0x80)
    {
        inst->reg_status |= JEMU_65c02_STATUS_OVERFLOW;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_OVERFLOW;
    }

    /* store A. */
    inst->reg_a = (uint8_t)(result & 0xFF);
    *cycles = 2;

    return STATUS_SUCCESS;
}
