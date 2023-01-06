/**
 * \file j65c02_wait_flag_get.c
 *
 * \brief Get the wait flag.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

/**
 * \brief Get the wait flag.
 *
 * \param inst              The instance to query.
 *
 * \returns the wait flag.
 */
bool JEMU_SYM(j65c02_wait_flag_get)(const JEMU_SYM(j65c02)* inst)
{
    return inst->wait;
}
