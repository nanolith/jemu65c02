/**
 * \file j65c02_inst_NOP.c
 *
 * \brief Handle a NOP instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

/**
 * \brief Handle a NOP instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_NOP)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    (void)inst;
    *cycles = 2;

    return STATUS_SUCCESS;
}
