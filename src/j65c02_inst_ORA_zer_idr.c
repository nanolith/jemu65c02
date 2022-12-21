/**
 * \file j65c02_inst_ORA_zer_idr.c
 *
 * \brief Handle an ORA zer idr instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle an ORA ZER IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ORA_zer_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint8_t rhs;
    uint16_t addr;

    /* this instruction is invalid on MOS silicon. */
    if (JEMU_65c02_PERSONALITY_MOS == inst->personality)
    {
        inst->crash = true;
        return JEMU_ERROR_INVALID_OPCODE;
    }

    /* fetch the address. */
    retval = j65c02_addr_zer_idr(inst, &addr);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* fetch the value at the address. */
    retval = inst->read(inst->user_context, addr, &rhs);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* perform the ORA operation. */
    JEMU_SYM(j65c02_op_ORA)(inst, rhs);

    /* this mode takes 5 cycles. */
    *cycles = 5;

    return STATUS_SUCCESS;
}
