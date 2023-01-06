/**
 * \file jemu65c02/jemu65c02.h
 *
 * \brief The main header for the jemu65c02 emulator.
 *
 * \copyright 2022-2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <jemu65c02/function_decl.h>
#include <jemu65c02/status.h>
#include <stdbool.h>
#include <stdint.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

#define JEMU_65c02_PERSONALITY_MOS                  1
#define JEMU_65c02_PERSONALITY_ROCKWELL             2
#define JEMU_65c02_PERSONALITY_WDC                  3

#define JEMU_65c02_EMULATION_MODE_STRICT            1
#define JEMU_65c02_EMULATION_MODE_NOP               2

#define JEMU_65c02_STATUS_NEGATIVE               0x80
#define JEMU_65c02_STATUS_OVERFLOW               0x40
#define JEMU_65c02_STATUS_NC                     0x20
#define JEMU_65c02_STATUS_BREAK                  0x10
#define JEMU_65c02_STATUS_DECIMAL                0x08
#define JEMU_65c02_STATUS_INTERRUPT              0x04
#define JEMU_65c02_STATUS_ZERO                   0x02
#define JEMU_65c02_STATUS_CARRY                  0x01

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
    int emulation_mode);

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
 * \brief Step through a single instruction.
 *
 * \note This call may generate calls to the read and write callbacks.
 *
 * \param inst              The instance to run.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_step)(JEMU_SYM(j65c02)* inst);

/**
 * \brief Set the IRQ flag to active (true) or inactive (false).
 *
 * \param inst              The instance to interrupt.
 * \param irq               The flag value to set.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_interrupt)(JEMU_SYM(j65c02)* inst, bool irq);

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

/**
 * \brief Trigger a reset of the processor in the emulator instance.
 *
 * \param inst              The instance to reset.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_reset)(JEMU_SYM(j65c02)* inst);

/**
 * \brief Release an emulator instance.
 *
 * \note After this call, the instance pointer is no longer valid.
 *
 * \param inst              The instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_release)(JEMU_SYM(j65c02)* inst);

/**
 * \brief Get the A register value.
 *
 * \param inst              The instance to query.
 *
 * \returns the A register value.
 */
uint8_t JEMU_SYM(j65c02_reg_a_get)(const JEMU_SYM(j65c02)* inst);

/**
 * \brief Set the A register value.
 *
 * \param inst              The instance for this operation.
 * \param val               The value to which the A register is set.
 */
void JEMU_SYM(j65c02_reg_a_set)(JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Get the X register value.
 *
 * \param inst              The instance to query.
 *
 * \returns the X register value.
 */
uint8_t JEMU_SYM(j65c02_reg_x_get)(const JEMU_SYM(j65c02)* inst);

/**
 * \brief Set the X register value.
 *
 * \param inst              The instance for this operation.
 * \param val               The value to which the X register is set.
 */
void JEMU_SYM(j65c02_reg_x_set)(JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Get the Y register value.
 *
 * \param inst              The instance to query.
 *
 * \returns the Y register value.
 */
uint8_t JEMU_SYM(j65c02_reg_y_get)(const JEMU_SYM(j65c02)* inst);

/**
 * \brief Set the Y register value.
 *
 * \param inst              The instance for this operation.
 * \param val               The value to which the Y register is set.
 */
void JEMU_SYM(j65c02_reg_y_set)(JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Get the SP register value.
 *
 * \param inst              The instance to query.
 *
 * \returns the SP register value.
 */
uint8_t JEMU_SYM(j65c02_reg_sp_get)(const JEMU_SYM(j65c02)* inst);

/**
 * \brief Set the SP register value.
 *
 * \param inst              The instance for this operation.
 * \param val               The value to which the SP register is set.
 */
void JEMU_SYM(j65c02_reg_sp_set)(JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Get the STATUS register value.
 *
 * \param inst              The instance to query.
 *
 * \returns the STATUS register value.
 */
uint8_t JEMU_SYM(j65c02_reg_status_get)(const JEMU_SYM(j65c02)* inst);

/**
 * \brief Set the STATUS register value.
 *
 * \param inst              The instance for this operation.
 * \param val               The value to which the STATUS register is set.
 */
void JEMU_SYM(j65c02_reg_status_set)(JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Get the PC register value.
 *
 * \param inst              The instance to query.
 *
 * \returns the PC register value.
 */
uint16_t JEMU_SYM(j65c02_reg_pc_get)(const JEMU_SYM(j65c02)* inst);

/**
 * \brief Set the PC register value.
 *
 * \param inst              The instance for this operation.
 * \param val               The value to which the PC register is set.
 */
void JEMU_SYM(j65c02_reg_pc_set)(JEMU_SYM(j65c02)* inst, uint16_t val);

/**
 * \brief Get the crash flag.
 *
 * \param inst              The instance to query.
 *
 * \returns the crash flag.
 */
bool JEMU_SYM(j65c02_crash_flag_get)(const JEMU_SYM(j65c02)* inst);

/**
 * \brief Get the stopped flag.
 *
 * \param inst              The instance to query.
 *
 * \returns the stopped flag.
 */
bool JEMU_SYM(j65c02_stopped_flag_get)(const JEMU_SYM(j65c02)* inst);

/**
 * \brief Get the wait flag.
 *
 * \param inst              The instance to query.
 *
 * \returns the wait flag.
 */
bool JEMU_SYM(j65c02_wait_flag_get)(const JEMU_SYM(j65c02)* inst);

/**
 * \brief Get the cycle delta for this emulator instance.
 *
 * \param inst              The instance to query.
 *
 * \returns the cycle delta.
 */
int JEMU_SYM(j65c02_cycle_delta_get)(const JEMU_SYM(j65c02)* inst);

/**
 * \brief Set the cycle delta for this emulator instance.
 *
 * \param inst              The instance for this operation.
 * \param val               The value to which the cycle delta is set.
 */
void JEMU_SYM(j65c02_cycle_delta_set)(JEMU_SYM(j65c02)* inst, int val);

/**
 * \brief Get the processor personality for this emulator instance.
 *
 * \param inst              The instance to query.
 *
 * \returns the processor personality.
 */
int JEMU_SYM(j65c02_personality_get)(const JEMU_SYM(j65c02)* inst);

/**
 * \brief Get the emulation mode for this emulator instance.
 *
 * \param inst              The instance to query.
 *
 * \returns the processor emulation mode.
 */
int JEMU_SYM(j65c02_emulation_mode_get)(const JEMU_SYM(j65c02)* inst);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_JEMU_IMPORT_jemu65c02_sym(sym) \
    JEMU_BEGIN_EXPORT \
    typedef JEMU_SYM(status) sym ## status; \
    typedef JEMU_SYM(j65c02) sym ## j65c02; \
    typedef JEMU_SYM(j65c02_read_fn) j65c02_read_fn; \
    typedef JEMU_SYM(j65c02_write_fn) j65c02_write_fn; \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_create( \
        JEMU_SYM(j65c02)** u, JEMU_SYM(j65c02_read_fn) v, \
        JEMU_SYM(j65c02_write_fn) w, void* x, int y, int z) { \
            return JEMU_SYM(j65c02_create)(u,v,w,x,y,z); } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_run(JEMU_SYM(j65c02)* x, int y) { \
            return JEMU_SYM(j65c02_run)(x,y); } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_step(JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_step)(x); } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_interrupt(JEMU_SYM(j65c02)* x, bool y) { \
            return JEMU_SYM(j65c02_interrupt)(x,y); } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_nmi(JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_nmi)(x); } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_reset(JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_reset)(x); } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_release(JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_release)(x); } \
    static inline uint8_t \
    sym ## j65c02_reg_a_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_reg_a_get)(x); } \
    static inline void \
    sym ## j65c02_reg_a_set(JEMU_SYM(j65c02)* x, uint8_t y) { \
            JEMU_SYM(j65c02_reg_a_set)(x,y); } \
    static inline uint8_t \
    sym ## j65c02_reg_x_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_reg_x_get)(x); } \
    static inline void \
    sym ## j65c02_reg_x_set(JEMU_SYM(j65c02)* x, uint8_t y) { \
            JEMU_SYM(j65c02_reg_x_set)(x,y); } \
    static inline uint8_t \
    sym ## j65c02_reg_y_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_reg_y_get)(x); } \
    static inline void \
    sym ## j65c02_reg_y_set(JEMU_SYM(j65c02)* x, uint8_t y) { \
            JEMU_SYM(j65c02_reg_y_set)(x,y); } \
    static inline uint8_t \
    sym ## j65c02_reg_sp_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_reg_sp_get)(x); } \
    static inline void \
    sym ## j65c02_reg_sp_set(JEMU_SYM(j65c02)* x, uint8_t y) { \
            JEMU_SYM(j65c02_reg_sp_set)(x,y); } \
    static inline uint8_t \
    sym ## j65c02_reg_status_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_reg_status_get)(x); } \
    static inline void \
    sym ## j65c02_reg_status_set(JEMU_SYM(j65c02)* x, uint8_t y) { \
            JEMU_SYM(j65c02_reg_status_set)(x,y); } \
    static inline uint16_t \
    sym ## j65c02_reg_pc_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_reg_pc_get)(x); } \
    static inline void \
    sym ## j65c02_reg_pc_set(JEMU_SYM(j65c02)* x, uint16_t y) { \
            JEMU_SYM(j65c02_reg_pc_set)(x,y); } \
    static inline bool \
    sym ## j65c02_crash_flag_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_crash_flag_get)(x); } \
    static inline bool \
    sym ## j65c02_stopped_flag_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_stopped_flag_get)(x); } \
    static inline bool \
    sym ## j65c02_wait_flag_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_wait_flag_get)(x); } \
    static inline int \
    sym ## j65c02_cycle_delta_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_cycle_delta_get)(x); } \
    static inline void \
    sym ## j65c02_cycle_delta_set(JEMU_SYM(j65c02)* x, int y) { \
            JEMU_SYM(j65c02_cycle_delta_set)(x,y); } \
    static inline int \
    sym ## j65c02_personality_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_personality_get)(x); } \
    static inline int \
    sym ## j65c02_emulation_mode_get(const JEMU_SYM(j65c02)* x) { \
            return JEMU_SYM(j65c02_emulation_mode_get)(x); } \
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
