/**
 * \file j65c02_compare.c
 *
 * \brief Compare two values, setting the status flags accordingly.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Compare two values, setting the status flags accordingly.
 *
 * \param inst              The emulator instance on which this operation is
 *                          performed.
 * \param lhs               The left-hand side of the comparison (A, X, Y, etc).
 * \param rhs               The right-hand side of the comparison (e.g. memory).
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
void JEMU_SYM(j65c02_compare)(JEMU_SYM(j65c02)* inst, uint8_t lhs, uint8_t rhs)
{
    /* compute the result. */
    unsigned int result = lhs - rhs;

    /* if no borrow was required, then set the carry. */
    if (result < 0x100)
    {
        inst->reg_status |= JEMU_65c02_STATUS_CARRY;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_CARRY;
    }

    /* if the highest bit is set, set the negative flag. */
    if (result & 0x80)
    {
        inst->reg_status |= JEMU_65c02_STATUS_NEGATIVE;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_NEGATIVE;
    }

    /* if the result is zero, set the zero flag. */
    if (result & 0xFF)
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_ZERO;
    }
    else
    {
        inst->reg_status |= JEMU_65c02_STATUS_ZERO;
    }
}
