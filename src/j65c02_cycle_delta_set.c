/**
 * \file j65c02_cycle_delta_set.c
 *
 * \brief Set the cycle delta.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

/**
 * \brief Set the cycle delta for this emulator instance.
 *
 * \param inst              The instance for this operation.
 * \param val               The value to which the cycle delta is set.
 */
void JEMU_SYM(j65c02_cycle_delta_set)(JEMU_SYM(j65c02)* inst, int val)
{
    inst->cycle_delta = val;
}
