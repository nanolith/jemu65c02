/**
 * \file j65c02_personality_get.c
 *
 * \brief Get the processor personality for this emulator instance.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

/**
 * \brief Get the processor personality for this emulator instance.
 *
 * \param inst              The instance to query.
 *
 * \returns the processor personality.
 */
int JEMU_SYM(j65c02_personality_get)(const JEMU_SYM(j65c02)* inst)
{
    return inst->personality;
}
