/**
 * \file j65c02_release.c
 *
 * \brief Release an emulator instance.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdlib.h>
#include <string.h>

#include "jemu65c02_internal.h"

/**
 * \brief Release an emulator instance.
 *
 * \note After this call, the instance pointer is no longer valid.
 *
 * \param inst              The instance to release..
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_release)(JEMU_SYM(j65c02)* inst)
{
    /* clear the emulator memory. */
    memset(inst, 0, sizeof(*inst));

    /* free memory. */
    free(inst);

    /* success. */
    return STATUS_SUCCESS;
}
