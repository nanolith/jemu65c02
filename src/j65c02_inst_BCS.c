/**
 * \file j65c02_inst_BCS.c
 *
 * \brief Handle a BCS instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle a BCS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BCS)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    int8_t val;
    int addr;

    /* read the branch offset. */
    retval = inst->read(inst->user_context, inst->reg_pc++, (uint8_t*)&val);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* get the program counter address. */
    addr = inst->reg_pc;

    /* calculate the new branch address. */
    addr += val;

    /* if the carry flag is set, take the branch. */
    if (inst->reg_status & JEMU_65c02_EMULATION_MODE_STRICT)
    {
        inst->reg_pc = (uint16_t)addr;
        *cycles = 3;
    }
    else
    {
        *cycles = 2;
    }

    /* success. */
    return STATUS_SUCCESS;
}
