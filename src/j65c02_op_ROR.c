/**
 * \file j65c02_op_ROR.c
 *
 * \brief Perform the ROR operation.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Perform the ROR operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               Pointer to the value to shift.
 */
void JEMU_SYM(j65c02_op_ROR)(
    JEMU_SYM(j65c02)* inst, uint8_t* val)
{
    uint8_t carry = 0;

    /* cache the carry flag. */
    if (inst->reg_status & JEMU_65c02_STATUS_CARRY)
    {
        carry = 1;
    }

    /* if the low bit is set, it will be shifted into the carry flag. */
    if (*val & 0x01)
    {
        inst->reg_status |= JEMU_65c02_STATUS_CARRY;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_CARRY;
    }

    /* shift the value right by one. */
    *val >>= 1;
    /* OR in the carry. */
    *val |= (carry ? 0x80 : 0x00);

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
