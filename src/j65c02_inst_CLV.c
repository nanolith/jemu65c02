/**
 * \file j65c02_inst_CLV.c
 *
 * \brief Handle a CLV instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle a CLV instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CLV)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    /* clear the overflow flag. */
    inst->reg_status &= ~JEMU_65c02_STATUS_OVERFLOW;

    /* this takes two cycles. */
    *cycles = 2;

    /* success. */
    return STATUS_SUCCESS;
}
