/**
 * \file j65c02_inst_TXS.c
 *
 * \brief Handle a TXS instruction.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle a TXS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_TXS)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    /* set SP to X. */
    inst->reg_sp = inst->reg_x;

    /* this instruction takes 2 cycles. */
    *cycles = 2;

    return STATUS_SUCCESS;
}
