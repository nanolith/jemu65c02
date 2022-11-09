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
 * \note On success, the caller is given ownership of the emulator instance and
 * must release it by calling \ref j65c02_release when it is no longer needed.
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
    JEMU_SYM(j65c02)** inst, JEMU_SYM(j65c02_read_fn)* read,
    JEMU_SYM(j65c02_write_fn)* write, void* context);

/**
 * \brief Run the emulator instance for the given number of cycles.
 *
 * \note This call may generate calls to the read and write callbacks.
 *
 * \param inst              The instance to run.
 * \param cycles            The number of cycles to run the instance.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_run)(JEMU_SYM(j65c02)* inst, int cycles);

/**
 * \brief Trigger an interrupt in the given emulator instance.
 *
 * \param inst              The instance to interrupt.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_interrupt)(JEMU_SYM(j65c02)* inst);

/**
 * \brief Trigger a non-maskable interrupt in the given emulator instance.
 *
 * \param inst              The instance to interrupt.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_nmi)(JEMU_SYM(j65c02)* inst);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_JEMU_IMPORT_jemu65c02_sym(sym) \
    JEMU_BEGIN_EXPORT \
    typedef JEMU_SYM(jemu65c02) sym ## jemu65c02; \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_create( \
        JEMU_SYM(j65c02)** w, JEMU_SYM(j65c02_read_fn)* x, \
        JEMU_SYM(j65c02_write_fn)* y, void* z) { \
            return JEMU_SYM(j65c02_create)(w,x,y,z); } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_run(JEMU_SYM(j65c02)* x, int y) { \
            return JEMU_SYM(j65c02_run)(x,y); } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_interrupt(JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_interrupt)(x); } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_nmi(JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_nmi)(x); } \
    JEMU_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define JEMU_IMPORT_jemu65c02_as(sym) \
    __INTERNAL_JEMU_IMPORT_jemu65c02_sym(sym ## _)
#define JEMU_IMPORT_jemu65c02 \
    __INTERNAL_JEMU_IMPORT_jemu65c02_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
