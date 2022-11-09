/**
 * \file jemu65c02/jemu65c02.h
 *
 * \brief The main header for the jemu65c02 emulator.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <jemu65c02/function_decl.h>
#include <jemu65c02/status.h>
#include <stdint.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The emulator instance.
 */
typedef struct JEMU_SYM(j65c02) JEMU_SYM(j65c02);

/**
 * \brief Read callback function.
 */
typedef JEMU_SYM(status) (*JEMU_SYM(j65c02_read_fn))(void*, uint16_t, uint8_t*);

/**
 * \brief Write callback function.
 */
typedef JEMU_SYM(status) (*JEMU_SYM(j65c02_write_fn))(void*, uint16_t, uint8_t);

/**
 * \brief Create an emulator instance.
 *
 * \param inst              Pointer to the instance pointer to set to the
 *                          created instance on success.
 * \param read              The read callback function.
 * \param write             The write callback function.
 * \param context           The user context to be passed to the callback
 *                          functions.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_create)(
    JEMU_SYM(j65c02)* inst, JEMU_SYM(j65c02_read_fn)* read,
    JEMU_SYM(j65c02_write_fn)* write, void* context);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
