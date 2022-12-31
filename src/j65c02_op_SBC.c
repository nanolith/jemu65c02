/**
 * \file j65c02_op_SBC.c
 *
 * \brief Perform the SBC operation.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Perform the SBC operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value to subtract from the accumulator.
 */
void JEMU_SYM(j65c02_op_SBC)(
    JEMU_SYM(j65c02)* inst, uint8_t val)
{
    unsigned int lhs = inst->reg_a;
    unsigned int rhs = val;
    unsigned int borrow = 0;

    /* set the borrow if the carry flag is clear. */
    if (! (inst->reg_status & JEMU_65c02_STATUS_CARRY))
    {
        borrow = 1;
    }

    /* compute the difference. */
    unsigned int result = lhs - rhs - borrow;

    /* handle the non-BCD case. */
    if (! (inst->reg_status & JEMU_65c02_STATUS_DECIMAL))
    {
        /* if the result is greater than 255, clear the carry flag. */
        if (result > 0xFF)
        {
            inst->reg_status &= ~JEMU_65c02_STATUS_CARRY;
        }
        else
        {
            inst->reg_status |= JEMU_65c02_STATUS_CARRY;
        }
    }
    /* handle BCD case. */
    else
    {
        /* ripple subtract the lower BCD digit. */
        if ((rhs & 0x0F) + borrow > (lhs & 0x0F))
        {
            result -= 0x06;
        }

        /* ripple the upper BCD digit. */
        if (result > 0x99)
        {
            result -= 0x60;
        }

        /* if the result is less than 0x100, set the carry flag. */
        if (result < 0x100)
        {
            inst->reg_status |= JEMU_65c02_STATUS_CARRY;
        }
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
