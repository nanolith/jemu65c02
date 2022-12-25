/**
 * \file j65c02_inst_ROL_abs_x.c
 *
 * \brief Handle a ROL abs x instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle a ROL ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ROL_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint8_t val;
    uint16_t addr;

    /* get the address. */
    retval = j65c02_addr_abs_x(inst, &addr);
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

    /* perform the ROL operation. */
    JEMU_SYM(j65c02_op_ROL)(inst, &val);

    /* write the value. */
    retval = inst->write(inst->user_context, addr, val);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* this instruction takes 7 cycles. */
    *cycles = 7;

    return STATUS_SUCCESS;
}
