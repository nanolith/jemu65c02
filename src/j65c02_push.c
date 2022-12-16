/**
 * \file j65c02_push.c
 *
 * \brief Push a value onto the stack.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Push a value onto the stack, decrementing the stack pointer after.
 *
 * \param inst              The emulator instance on which this operation is
 *                          performed.
 * \param val               The value to push onto the stack.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_push)(JEMU_SYM(j65c02)* inst, uint8_t val)
{
    status retval;

    /* write the value to 0x0100 + sp. */
    retval = inst->write(inst->user_context, 0x0100 + inst->reg_sp, val);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* decrement sp. */
    --(inst->reg_sp);

    /* success. */
    return STATUS_SUCCESS;
}
