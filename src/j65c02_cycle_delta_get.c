/**
 * \file j65c02_cycle_delta_get.c
 *
 * \brief Get the cycle delta.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

/**
 * \brief Get the cycle delta for this emulator instance.
 *
 * \param inst              The instance to query.
 *
 * \returns the cycle delta.
 */
int JEMU_SYM(j65c02_cycle_delta_get)(const JEMU_SYM(j65c02)* inst)
{
    return inst->cycle_delta;
}
