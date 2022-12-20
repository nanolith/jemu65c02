/**
 * \file j65c02_op_LDY.c
 *
 * \brief Perform the LDY operation.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Perform the LDY operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value to exclusive-OR with the accumulator.
 */
void JEMU_SYM(j65c02_op_LDY)(
    JEMU_SYM(j65c02)* inst, uint8_t val)
{
    /* set Y to val. */
    inst->reg_y = val;

    /* set the negative flag if the MSB is set. */
    if (inst->reg_y & 0x80)
    {
        inst->reg_status |= JEMU_65c02_STATUS_NEGATIVE;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_NEGATIVE;
    }

    /* set the zero flag if the Y register is zero. */
    if (!inst->reg_y)
    {
        inst->reg_status |= JEMU_65c02_STATUS_ZERO;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_ZERO;
    }
}
