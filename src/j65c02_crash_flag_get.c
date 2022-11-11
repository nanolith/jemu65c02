/**
 * \file j65c02_crash_flag_get.c
 *
 * \brief Get the crash flag.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

/**
 * \brief Get the crash flag.
 *
 * \param inst              The instance to query.
 *
 * \returns the crash flag.
 */
bool JEMU_SYM(j65c02_crash_flag_get)(const JEMU_SYM(j65c02)* inst)
{
    return inst->crash;
}
