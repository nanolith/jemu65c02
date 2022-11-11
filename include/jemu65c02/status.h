/**
 * \file jemu65c02/status.h
 *
 * \brief Status codes for jemu65c02.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <jemu65c02/function_decl.h>
#include <stdint.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief Status is a 32-bit integer.
*/
typedef int32_t JEMU_SYM(status);

/**
 * \brief The operation completed successfully.
 */
#define STATUS_SUCCESS                                              0x00000000

/**
 * \brief An invalid opcode was encountered.
 */
#define JEMU_ERROR_INVALID_OPCODE                                   0x80000000

/**
 * \brief An invalid processor personality was selected.
 */
#define JEMU_ERROR_INVALID_PERSONALITY                              0x80000001

/**
 * \brief An invalid emulation mode was selected.
 */
#define JEMU_ERROR_INVALID_EMULATION_MODE                           0x80000002

/**
 * \brief An out-of-memory condition was encountered.
 */
#define JEMU_ERROR_OUT_OF_MEMORY                                    0x80000003

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
