/**
 * \file j65c02_op_BIT.c
 *
 * \brief Perform the BIT operation.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Perform the BIT operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value to compare.
 */
void JEMU_SYM(j65c02_op_BIT)(
    JEMU_SYM(j65c02)* inst, uint8_t val)
{
    /* test the high bit of val. */
    if (val & 0x80)
    {
        inst->reg_status |= JEMU_65c02_STATUS_NEGATIVE;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_NEGATIVE;
    }

    /* test the second-highest bit bit of val. */
    if (val & 0x40)
    {
        inst->reg_status |= JEMU_65c02_STATUS_OVERFLOW;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_OVERFLOW;
    }

    /* and the value with A. */
    val &= inst->reg_a;

    /* set the zero flag based on the value. */
    if (val)
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_ZERO;
    }
    else
    {
        inst->reg_status |= JEMU_65c02_STATUS_ZERO;
    }
}
