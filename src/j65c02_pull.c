/**
 * \file j65c02_pull.c
 *
 * \brief Pull a value off of the stack.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Increment the stack pointer then pull the value at the new stack
 * pointer location off of the stack.
 *
 * \param inst              The emulator instance on which this operation is
 *                          performed.
 * \param val               The pointer to the variable assigned to the value
 *                          read from the updated stack location.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_pull)(JEMU_SYM(j65c02)* inst, uint8_t* val)
{
    status retval;

    /* increment sp. */
    ++(inst->reg_sp);

    /* read the value from 0x0100 + sp. */
    retval = inst->read(inst->user_context, 0x0100 + inst->reg_sp, val);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* success. */
    return STATUS_SUCCESS;
}
