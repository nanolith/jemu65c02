/**
 * \file j65c02_inst_STP.c
 *
 * \brief Handle a STP instruction.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle a STP instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_STP)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    /* stop the processor. */
    inst->stopped = true;

    /* this instruction takes three cycles. */
    *cycles = 3;

    /* success. */
    return STATUS_SUCCESS;
}
