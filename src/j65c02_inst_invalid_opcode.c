/**
 * \file j65c02_inst_invalid_opcode.c
 *
 * \brief Handle an invalid opcode instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

/**
 * \brief Handle an invalid opcode instruction by setting the crash flag.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns JEMU_ERROR_INVALID_OPCODE.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_invalid_opcode)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    inst->crash = true;

    return JEMU_ERROR_INVALID_OPCODE;
}
