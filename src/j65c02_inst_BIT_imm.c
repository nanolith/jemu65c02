/**
 * \file j65c02_inst_BIT_imm.c
 *
 * \brief Handle a BIT imm instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle a BIT IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BIT_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint16_t addr;
    uint8_t val;

    /* read the address. */
    retval = j65c02_addr_imm(inst, &addr);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* read the value. */
    retval = inst->read(inst->user_context, addr, &val);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* and the value with A. */
    val &= inst->reg_a;

    /* set the zero flag based on the value. */
    if (val)
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_ZERO;
    }
    else
    {
        inst->reg_status |= JEMU_65c02_STATUS_ZERO;
    }

    /* this instruction takes two cycles to execute. */
    *cycles = 2;

    /* success. */
    return STATUS_SUCCESS;
}
