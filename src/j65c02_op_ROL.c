/**
 * \file j65c02_op_ROL.c
 *
 * \brief Perform the ROL operation.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Perform the ROL operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               Pointer to the value to shift.
 */
void JEMU_SYM(j65c02_op_ROL)(
    JEMU_SYM(j65c02)* inst, uint8_t* val)
{
    uint8_t carry = 0;

    /* cache the carry flag. */
    if (inst->reg_status & JEMU_65c02_STATUS_CARRY)
    {
        carry = 1;
    }

    /* if the high bit is set, it will be shifted into the carry flag. */
    if (*val & 0x80)
    {
        inst->reg_status |= JEMU_65c02_STATUS_CARRY;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_CARRY;
    }

    /* shift the value left by one. */
    *val <<= 1;
    /* OR in the carry. */
    *val |= carry;

    /* if the result has the high bit set, set the negative flag. */
    if (*val & 0x80)
    {
        inst->reg_status |= JEMU_65c02_STATUS_NEGATIVE;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_NEGATIVE;
    }

    /* if the result is zero, set the zero flag. */
    if (*val)
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_ZERO;
    }
    else
    {
        inst->reg_status |= JEMU_65c02_STATUS_ZERO;
    }
}
