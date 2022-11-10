/**
 * \file j65c02_reg_x_set.c
 *
 * \brief Setter for register X.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

/**
 * \brief Set the X register value.
 *
 * \param inst              The instance for this operation.
 * \param val               The value to which the X register is set.
 */
void JEMU_SYM(j65c02_reg_x_set)(JEMU_SYM(j65c02)* inst, uint8_t val)
{
    inst->reg_x = val;
}
