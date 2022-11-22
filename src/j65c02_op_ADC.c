/**
 * \file j65c02_op_ADC.c
 *
 * \brief Perform the ADC operation.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Perform the ADC operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value to add to the accumulator.
 */
void JEMU_SYM(j65c02_op_ADC)(
    JEMU_SYM(j65c02)* inst, uint8_t val)
{
    uint8_t rhs = val;
    uint8_t carry = 0;

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
        /* TODO - add one to the cycle if this is WDC / Rockwell personality. */

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
}
