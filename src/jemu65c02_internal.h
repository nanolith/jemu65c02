/**
 * \file jemu65c02_internal.h
 *
 * \brief Internal header for jemu65c02.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <jemu65c02/jemu65c02.h>
#include <stdbool.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief An instruction.
 */
typedef struct JEMU_SYM(j65c02_instruction) JEMU_SYM(j65c02_instruction);

struct JEMU_SYM(j65c02_instruction)
{
    JEMU_SYM(status) (*exec)(JEMU_SYM(j65c02)* inst);
    int cycles;
};

/**
 * The external instruction array global.
 */
extern JEMU_SYM(j65c02_instruction) JEMU_SYM(global_j65c02_instructions)[256];

/**
 * \brief The emulator instance.
 */
struct JEMU_SYM(j65c02)
{
    uint8_t reg_a;
    uint8_t reg_x;
    uint8_t reg_y;
    uint8_t reg_sp;
    uint8_t reg_status;
    uint16_t reg_pc;
    int cycle_delta;
    JEMU_SYM(j65c02_read_fn) read;
    JEMU_SYM(j65c02_write_fn) write;
    void* user_context;
    bool crash;
};

/**
 * \brief Handle an invalid opcode instruction by setting the crash flag.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 *
 * \returns JEMU_ERROR_INVALID_OPCODE.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_invalid_opcode)(JEMU_SYM(j65c02)* inst);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_JEMU_IMPORT_jemu65c02_internal_sym(sym) \
    JEMU_BEGIN_EXPORT \
    typedef JEMU_SYM(j65c02_instruction) sym ## j65c02_instruction; \
    JEMU_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define JEMU_IMPORT_jemu65c02_internal_as(sym) \
    __INTERNAL_JEMU_IMPORT_jemu65c02_internal_sym(sym ## _)
#define JEMU_IMPORT_jemu65c02_internal \
    __INTERNAL_JEMU_IMPORT_jemu65c02_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
