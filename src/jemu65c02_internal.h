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
 * \brief Push a value onto the stack, decrementing the stack pointer after.
 *
 * \param inst              The emulator instance on which this operation is
 *                          performed.
 * \param val               The value to push onto the stack.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_push)(JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Compare two values, setting the status flags accordingly.
 *
 * \param inst              The emulator instance on which this operation is
 *                          performed.
 * \param lhs               The left-hand side of the comparison (A, X, Y, etc).
 * \param rhs               The right-hand side of the comparison (e.g. memory).
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
void JEMU_SYM(j65c02_compare)(JEMU_SYM(j65c02)* inst, uint8_t lhs, uint8_t rhs);

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

/**
 * \brief Perform the AND operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value for this operation.
 */
void JEMU_SYM(j65c02_op_AND)(
    JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Handle an AND IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_AND_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an AND ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_AND_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an AND ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_AND_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an AND ZER IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_AND_zer_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an AND ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_AND_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an AND ABS Y instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_AND_abs_y)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an AND ZER X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_AND_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an AND ZER X IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_AND_zer_x_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an AND ZER Y IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_AND_zer_y_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Perform the ASL operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               Pointer to the value to shift.
 */
void JEMU_SYM(j65c02_op_ASL)(
    JEMU_SYM(j65c02)* inst, uint8_t* val);

/**
 * \brief Handle an ASL A instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ASL_a)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ASL abs instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ASL_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ASL zer instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ASL_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ASL abs x instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ASL_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ASL zer x instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ASL_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BCC instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BCC)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BCS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BCS)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BEQ instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BEQ)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Perform the BIT operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value to compare.
 */
void JEMU_SYM(j65c02_op_BIT)(
    JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Handle a BIT IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BIT_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BIT ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BIT_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BIT ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BIT_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BIT ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BIT_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BIT ZER X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BIT_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BMI instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BMI)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BNE instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BNE)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BPL instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BPL)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BRA instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BRA)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BRK instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BRK)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BVC instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BVC)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a BVS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_BVS)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CLC instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CLC)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CLD instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CLD)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CLI instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CLI)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CLV instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CLV)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CMP IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CMP_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CMP ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CMP_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CMP ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CMP_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CMP ZER IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CMP_zer_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CMP ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CMP_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CMP ABS Y instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CMP_abs_y)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CMP ZER X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CMP_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CMP ZER X IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CMP_zer_x_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CMP ZER Y IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CMP_zer_y_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CPX IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CPX_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CPX ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CPX_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CPX ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CPX_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CPY IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CPY_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CPY ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CPY_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a CPY ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_CPY_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a DEC A instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_DEC_a)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a DEC abs instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_DEC_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a DEC zer instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_DEC_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a DEC ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_DEC_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a DEC ZER X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_DEC_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a DEX instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_DEX)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a DEY instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_DEY)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Perform the EOR operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value to exclusive-OR with the accumulator.
 */
void JEMU_SYM(j65c02_op_EOR)(
    JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Handle an EOR IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_EOR_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an EOR ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_EOR_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an EOR ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_EOR_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an EOR ZER IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_EOR_zer_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an EOR ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_EOR_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an EOR ABS Y instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_EOR_abs_y)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an EOR ZER X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_EOR_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an EOR ZER X IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_EOR_zer_x_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an EOR ZER Y IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_EOR_zer_y_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an INC A instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_INC_a)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an INC ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_INC_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an INC ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_INC_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an INC ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_INC_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an INC ZER X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_INC_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an INX instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_INX)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an INY instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_INY)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a JMP ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_JMP_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a JMP ABS IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_JMP_abs_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a JMP ABS X IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_JMP_abs_x_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle a JSR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_JSR)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Perform the LDA operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value to exclusive-OR with the accumulator.
 */
void JEMU_SYM(j65c02_op_LDA)(
    JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Handle an LDA IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDA_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDA ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDA_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDA ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDA_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDA ZER IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDA_zer_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDA ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDA_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDA ABS Y instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDA_abs_y)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDA ZER X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDA_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDA ZER X IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDA_zer_x_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDA ZER Y IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDA_zer_y_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Perform the LDX operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value to exclusive-OR with the accumulator.
 */
void JEMU_SYM(j65c02_op_LDX)(
    JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Handle an LDX IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDX_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDX ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDX_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDX ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDX_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDX ABS Y instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDX_abs_y)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDX ZER Y instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDX_zer_y)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Perform the LDY operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value to exclusive-OR with the accumulator.
 */
void JEMU_SYM(j65c02_op_LDY)(
    JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Handle an LDY IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDY_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDY ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDY_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDY ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDY_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDY ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDY_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LDY ZER X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LDY_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Perform the LSR operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               Pointer to the value to shift.
 */
void JEMU_SYM(j65c02_op_LSR)(
    JEMU_SYM(j65c02)* inst, uint8_t* val);

/**
 * \brief Handle an LSR A instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LSR_a)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LSR ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LSR_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LSR ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LSR_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LSR ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LSR_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an LSR ZER X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_LSR_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Perform the ORA operation.
 *
 * \param inst              The emulator instance on which this instruction
 *                          executes.
 * \param val               The value for this operation.
 */
void JEMU_SYM(j65c02_op_ORA)(
    JEMU_SYM(j65c02)* inst, uint8_t val);

/**
 * \brief Handle an ORA IMM instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ORA_imm)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ORA ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ORA_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ORA ZER instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ORA_zer)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ORA ZER IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ORA_zer_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ORA ABS X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ORA_abs_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ORA ABS Y instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ORA_abs_y)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ORA ZER X instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ORA_zer_x)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ORA ZER X IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ORA_zer_x_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an ORA ZER Y IDR instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_ORA_zer_y_idr)(
    JEMU_SYM(j65c02)* inst, int* cycles);

/**
 * \brief Handle an PHA instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_PHA)(
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
    sym ## j65c02_addr_abs(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        JEMU_SYM(status) retval; \
        uint8_t addr_low, addr_high; \
        /* fetch the low part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_low); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_high); \
        if (STATUS_SUCCESS != retval) return retval; \
        *addr = addr_high << 8 | addr_low; \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_abs_idr(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        JEMU_SYM(status) retval; \
        uint8_t addr_low, addr_high; \
        uint16_t tmp; \
        uint8_t eff_low, eff_high; \
        /* fetch the low part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_low); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_high); \
        if (STATUS_SUCCESS != retval) return retval; \
        tmp = addr_high << 8 | addr_low; \
        /* fetch the low part of the real address. */ \
        retval = inst->read(inst->user_context, tmp, &eff_low); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high part of the real address. */ \
        retval = inst->read(inst->user_context, tmp+1, &eff_high); \
        if (STATUS_SUCCESS != retval) return retval; \
        *addr = eff_high << 8 | eff_low; \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_abs_x_idr(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        JEMU_SYM(status) retval; \
        uint8_t addr_low, addr_high; \
        uint16_t tmp; \
        uint8_t eff_low, eff_high; \
        /* fetch the low part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_low); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_high); \
        if (STATUS_SUCCESS != retval) return retval; \
        tmp = addr_high << 8 | addr_low; \
        /* add X to this temporary address. */ \
        tmp += inst->reg_x; \
        /* fetch the low part of the real address. */ \
        retval = inst->read(inst->user_context, tmp, &eff_low); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high part of the real address. */ \
        retval = inst->read(inst->user_context, tmp+1, &eff_high); \
        if (STATUS_SUCCESS != retval) return retval; \
        *addr = eff_high << 8 | eff_low; \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_abs_x(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        JEMU_SYM(status) retval; \
        uint8_t addr_low, addr_high; \
        /* fetch the low part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_low); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_high); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* add X to this address. */ \
        *addr = ((addr_high << 8) | addr_low) + inst->reg_x; \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_abs_y(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        JEMU_SYM(status) retval; \
        uint8_t addr_low, addr_high; \
        /* fetch the low part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_low); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high part of the address. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &addr_high); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* add Y to this address. */ \
        *addr = ((addr_high << 8) | addr_low) + inst->reg_y; \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_imm(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        *addr = inst->reg_pc++; \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_zer(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        JEMU_SYM(status) retval; \
        uint8_t offset; \
        /* fetch the zero-page index. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &offset); \
        if (STATUS_SUCCESS != retval) return retval; \
        *addr = offset; \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_zer_idr(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        JEMU_SYM(status) retval; \
        uint8_t offset, addr_low, addr_high; \
        /* fetch the zero-page index. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &offset); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the low address from the zero-page. */ \
        retval = inst->read(inst->user_context, offset++, &addr_low); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high address from the zero-page. */ \
        retval = inst->read(inst->user_context, offset++, &addr_high); \
        if (STATUS_SUCCESS != retval) return retval; \
        *addr = (addr_high << 8) | addr_low; \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_zer_x(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        JEMU_SYM(status) retval; \
        uint8_t offset; \
        /* fetch the zero-page index. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &offset); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* increment the offset by X. */ \
        offset += inst->reg_x; \
        *addr = offset; \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_zer_y(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        JEMU_SYM(status) retval; \
        uint8_t offset; \
        /* fetch the zero-page index. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &offset); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* increment the offset by Y. */ \
        offset += inst->reg_y; \
        *addr = offset; \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_push(JEMU_SYM(j65c02)* inst, uint8_t val) { \
        return JEMU_SYM(j65c02_push)(inst, val); } \
    static inline void sym ## j65c02_compare( \
        JEMU_SYM(j65c02)* inst, uint8_t lhs, uint8_t rhs) { \
        JEMU_SYM(j65c02_compare)(inst, lhs, rhs); } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_zer_x_idr(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        JEMU_SYM(status) retval; \
        uint8_t offset, addrL, addrH; \
        /* fetch the zero-page index. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &offset); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* increment the offset by X. */ \
        offset += inst->reg_x; \
        /* fetch the low address. */ \
        retval = inst->read(inst->user_context, offset++, &addrL); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high address. */ \
        retval = inst->read(inst->user_context, offset++, &addrH); \
        if (STATUS_SUCCESS != retval) return retval; \
        *addr = (addrH << 8) | addrL; \
        return STATUS_SUCCESS; \
    } \
    static inline JEMU_SYM(status) FN_DECL_MUST_CHECK \
    sym ## j65c02_addr_zer_y_idr(JEMU_SYM(j65c02)* inst, uint16_t* addr) { \
        JEMU_SYM(status) retval; \
        uint8_t offset, addrL, addrH; \
        /* fetch the zero-page index. */ \
        retval = inst->read(inst->user_context, inst->reg_pc++, &offset); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the low address. */ \
        retval = inst->read(inst->user_context, offset++, &addrL); \
        if (STATUS_SUCCESS != retval) return retval; \
        /* fetch the high address. */ \
        retval = inst->read(inst->user_context, offset++, &addrH); \
        if (STATUS_SUCCESS != retval) return retval; \
        *addr = (addrH << 8) + addrL + inst->reg_y; \
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
