/**
 * \file j65c02_fetch.c
 *
 * \brief Fetch a value from the current program counter and increment.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;

/**
 * \brief Fetch a byte from the program counter, then increment the program
 * counter.
 *
 * \param val               Pointer to hold the value fetched from the program
 *                          counter.
 * \param inst              The emulator instance on which this operation is
 *                          performed.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_fetch)(
    uint8_t* val, JEMU_SYM(j65c02)* inst)
{
    status retval;

    /* read a value. */
    retval = inst->read(inst->user_context, inst->reg_pc, val);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* increment pc. */
    inst->reg_pc += 1;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
