/**
 * \file j65c02_create.c
 *
 * \brief Create an emulator instance.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Create an emulator instance.
 *
 * \note On success, the caller is given ownership of the emulator instance and
 * must release it by calling \ref j65c02_release when it is no longer needed.
 *
 * \param inst              Pointer to the instance pointer to set to the
 *                          created instance on success.
 * \param read              The read callback function.
 * \param write             The write callback function.
 * \param context           The user context to be passed to the callback
 *                          functions.
 * \param personality       The processor personality (MOS, ROCKWELL, or WDC).
 * \param emulation_mode    The emulation mode (strict or map invalid opcodes as
 *                          NOPs).
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_create)(
    JEMU_SYM(j65c02)** inst, JEMU_SYM(j65c02_read_fn) read,
    JEMU_SYM(j65c02_write_fn) write, void* context, int personality,
    int emulation_mode)
{
    status retval, release_retval;
    j65c02* tmp;

    /* allocate memory for the emulator instance. */
    tmp = malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = JEMU_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* clear out the structure. */
    memset(tmp, 0, sizeof(*tmp));

    /* start the processor in crash mode; reset must be called to reset it. */
    tmp->crash = true;

    /* verify and set the personality. */
    switch (personality)
    {
        case JEMU_65c02_PERSONALITY_MOS:
        case JEMU_65c02_PERSONALITY_ROCKWELL:
        case JEMU_65c02_PERSONALITY_WDC:
            tmp->personality = personality;
            break;

        default:
            retval = JEMU_ERROR_INVALID_PERSONALITY;
            goto cleanup_tmp;
    }

    /* verify and set the emulation mode. */
    switch (emulation_mode)
    {
        case JEMU_65c02_EMULATION_MODE_STRICT:
        case JEMU_65c02_EMULATION_MODE_NOP:
            tmp->emulation_mode = emulation_mode;
            break;

        default:
            retval = JEMU_ERROR_INVALID_EMULATION_MODE;
            goto cleanup_tmp;
    }

    /* set user values. */
    tmp->user_context = context;
    tmp->read = read;
    tmp->write = write;

    /* success. */
    *inst = tmp;
    retval = STATUS_SUCCESS;
    goto done;

cleanup_tmp:
    release_retval = j65c02_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
