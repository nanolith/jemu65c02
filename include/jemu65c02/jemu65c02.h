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
typedef JEMU_SYM(status) (*j65c02_read_fn)(void*, uint16_t, uint8_t*);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
