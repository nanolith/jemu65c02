/**
 * \file j65c02_inst_DEC_zer.c
 *
 * \brief Handle a DEC zer instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle a DEC zer instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_DEC_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint16_t addr;
    uint8_t val;

    /* fetch the address. */
    retval = j65c02_addr_zer(inst, &addr);
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

    /* decrement the value. */
    --val;

    /* write the value. */
    retval = inst->write(inst->user_context, addr, val);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* if negative, set the negative flag. */
    if (val & 0x80)
    {
        inst->reg_status |= JEMU_65c02_STATUS_NEGATIVE;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_NEGATIVE;
    }

    /* if zero, set the zero flag. */
    if (0x00 == val)
    {
        inst->reg_status |= JEMU_65c02_STATUS_ZERO;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_ZERO;
    }

    /* this instruction takes 5 cycles. */
    *cycles = 5;

    return STATUS_SUCCESS;
}
