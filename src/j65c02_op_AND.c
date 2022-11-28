/**
 * \file j65c02_op_AND.c
 *
 * \brief Perform the AND operation.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Perform the AND operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value for this operation.
 */
void JEMU_SYM(j65c02_op_AND)(
    JEMU_SYM(j65c02)* inst, uint8_t val)
{
    /* compute the result. */
    inst->reg_a &= val;

    /* set the negative flag if the MSB is set. */
    if (inst->reg_a & 0x80)
    {
        inst->reg_status |= JEMU_65c02_STATUS_NEGATIVE;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_NEGATIVE;
    }

    /* set the zero flag if the A register is zero. */
    if (!inst->reg_a)
    {
        inst->reg_status |= JEMU_65c02_STATUS_ZERO;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_ZERO;
    }
}
