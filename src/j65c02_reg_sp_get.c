/**
 * \file j65c02_reg_sp_get.c
 *
 * \brief Getter for register SP.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

/**
 * \brief Get the SP register value.
 *
 * \param inst              The instance to query.
 *
 * \returns the SP register value.
 */
uint8_t JEMU_SYM(j65c02_reg_sp_get)(const JEMU_SYM(j65c02)* inst)
{
    return inst->reg_sp;
}
