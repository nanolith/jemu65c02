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
    JEMU_SYM(status) (*exec)(JEMU_SYM(j65c02)* inst, int* cycles);
    int max_cycles;
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
    int personality;
    int emulation_mode;
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
    bool irq;
};

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
    uint8_t* val, JEMU_SYM(j65c02)* inst);

/**
 * \brief Handle an invalid opcode instruction by setting the crash flag.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns JEMU_ERROR_INVALID_OPCODE.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_invalid_opcode)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Perform the ADC operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value to add to the accumulator.
 */
void JEMU_SYM(j65c02_op_ADC)(
    JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Handle an ADC IMM instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ADC ZER instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ADC ABS instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ADC ABS X instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ADC ABS Y instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_abs_y)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ADC ZER IDR instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_zer_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ADC ZER X instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ADC ZER X IDR instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_zer_x_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ADC ZER Y IDR instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ADC_zer_y_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a NOP instruction.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param cycles            The number of cycles taken to execute this
 *                          instruction.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) JEMU_SYM(j65c02_inst_NOP)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_JEMU_IMPORT_jemu65c02_internal_sym(sym) \
    JEMU_BEGIN_EXPORT \
    typedef JEMU_SYM(j65c02_instruction) sym ## j65c02_instruction; \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_fetch(uint8_t* x, JEMU_SYM(j65c02)* y) { \
        return JEMU_SYM(j65c02_fetch)(x,y); } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_abs(JEMU_SYM(j65c02)* inst, uint8_t* val) { \
        JEMU_SYM(status) retval; \
        uint8_t addr_low, addr_high; \
        /* fetch the low part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_low); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_high); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the value from the address. */ \
        retval = \
            inst->read(inst->user_context, addr_high << 8 | addr_low, val); \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_abs_x(JEMU_SYM(j65c02)* inst, uint8_t* val) { \
        JEMU_SYM(status) retval; \
        uint8_t addr_low, addr_high; \
        uint16_t addr; \
        /* fetch the low part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_low); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_high); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* add X to this address. */ \
        addr = ((addr_high << 8) | addr_low) + inst->reg_x; \
        /* fetch the value from the address. */ \
        retval = \
            inst->read(inst->user_context, addr, val); \
        return STATUS_SUCCESS; \
    } \
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
