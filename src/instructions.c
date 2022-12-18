/**
 * \file instructions.c
 *
 * \brief List of all supported 65c02 instructions.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02_internal;

/**
 * The instruction array global.
 */
JEMU_SYM(j65c02_instruction) JEMU_SYM(global_j65c02_instructions)[256] = {
    /* opcodes 0x00 - 0x0F. */
    /* Opcode 0x00 - BRK instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BRK), .max_cycles = 7 },
    /* Opcode 0x01 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x02 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x03 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x04 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x05 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x06 - ASL ZER instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ASL_zer), .max_cycles = 5 },
    /* Opcode 0x07 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x08 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x09 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x0A - ASL A instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ASL_a), .max_cycles = 2 },
    /* Opcode 0x0B - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x0C - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x0D - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x0E - ASL abs instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ASL_abs), .max_cycles = 6 },
    /* Opcode 0x0F - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0x10 - 0x1F. */
    /* Opcode 0x10 - BPL instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BPL), .max_cycles = 3 },
    /* Opcode 0x11 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x12 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x13 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x14 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x15 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x16 - ASL ZER X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ASL_zer_x), .max_cycles = 6 },
    /* Opcode 0x17 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x18 - CLC instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CLC), .max_cycles = 2 },
    /* Opcode 0x19 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x1A - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x1B - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x1C - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x1D - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x1E - ASL ABS X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ASL_abs_x), .max_cycles = 7 },
    /* Opcode 0x1F - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0x20 - 0x2F. */
    /* Opcode 0x20 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x21 - AND ZER X IDR instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_AND_zer_x_idr), .max_cycles = 6 },
    /* Opcode 0x22 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x23 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x24 - BIT ZER instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BIT_zer), .max_cycles = 3 },
    /* Opcode 0x25 - AND ZER instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_AND_zer), .max_cycles = 3 },
    /* Opcode 0x26 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x27 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x28 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x29 - AND IMM instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_AND_imm), .max_cycles = 2 },
    /* Opcode 0x2A - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x2B - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x2C - BIT ABS instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BIT_abs), .max_cycles = 4 },
    /* Opcode 0x2D - AND ABS instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_AND_abs), .max_cycles = 4 },
    /* Opcode 0x2E - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x2F - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0x30 - 0x3F. */
    /* Opcode 0x30 - BMI instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BMI), .max_cycles = 3 },
    /* Opcode 0x31 - AND ZER Y IDR instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_AND_zer_y_idr), .max_cycles = 5 },
    /* Opcode 0x32 - AND ZER IDR instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_AND_zer_idr), .max_cycles = 5 },
    /* Opcode 0x33 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x34 - BIT ZER X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BIT_zer_x), .max_cycles = 4 },
    /* Opcode 0x35 - AND ZER X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_AND_zer_x), .max_cycles = 4 },
    /* Opcode 0x36 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x37 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x38 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x39 - AND ABS Y instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_AND_abs_y), .max_cycles = 4 },
    /* Opcode 0x3A - DEC A instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_DEC_a), .max_cycles = 2 },
    /* Opcode 0x3B - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x3C - BIT ABS X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BIT_abs_x), .max_cycles = 4 },
    /* Opcode 0x3D - AND ABS X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_AND_abs_x), .max_cycles = 4 },
    /* Opcode 0x3E - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x3F - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0x40 - 0x4F. */
    /* Opcode 0x40 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x41 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x42 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x43 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x44 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x45 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x46 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x47 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x48 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x49 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x4A - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x4B - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x4C - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x4D - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x4E - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x4F - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0x50 - 0x5F. */
    /* Opcode 0x50 - BVC instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BVC), .max_cycles = 3 },
    /* Opcode 0x51 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x52 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x53 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x54 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x55 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x56 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x57 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x58 - CLI instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CLI), .max_cycles = 2 },
    /* Opcode 0x59 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x5A - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x5B - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x5C - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x5D - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x5E - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x5F - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0x60 - 0x6F. */
    /* Opcode 0x60 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x61 - ADC ZER X IDR instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ADC_zer_x_idr), .max_cycles = 7 },
    /* Opcode 0x62 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x63 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x64 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x65 - ADC ZER instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ADC_zer), .max_cycles = 4 },
    /* Opcode 0x66 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x67 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x68 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x69 - ADC IMM instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ADC_imm), .max_cycles = 3 },
    /* Opcode 0x6A - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x6B - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x6C - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x6D - ADC ABS instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ADC_abs), .max_cycles = 5 },
    /* Opcode 0x6E - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x6F - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0x70 - 0x7F. */
    /* Opcode 0x70 - BVS instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BVS), .max_cycles = 3 },
    /* Opcode 0x71 - ADC ZER Y IDR instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ADC_zer_y_idr), .max_cycles = 6 },
    /* Opcode 0x72 - ADC ZER IDR instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ADC_zer_idr), .max_cycles = 6 },
    /* Opcode 0x73 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x74 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x75 - ADC ZER X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ADC_zer_x), .max_cycles = 5 },
    /* Opcode 0x76 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x77 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x78 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x79 - ADC ABS Y instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ADC_abs_y), .max_cycles = 5 },
    /* Opcode 0x7A - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x7B - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x7C - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x7D - ADC ABS X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_ADC_abs_x), .max_cycles = 5 },
    /* Opcode 0x7E - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x7F - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0x80 - 0x8F. */
    /* Opcode 0x80 - BRA instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BRA), .max_cycles = 3 },
    /* Opcode 0x81 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x82 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x83 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x84 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x85 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x86 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x87 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x88 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x89 - BIT IMM instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BIT_imm), .max_cycles = 2 },
    /* Opcode 0x8A - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x8B - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x8C - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x8D - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x8E - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x8F - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0x90 - 0x9F. */
    /* Opcode 0x90 - BCC instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BCC), .max_cycles = 3 },
    /* Opcode 0x91 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x92 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x93 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x94 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x95 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x96 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x97 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x98 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x99 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x9A - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x9B - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x9C - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x9D - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x9E - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0x9F - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0xA0 - 0xAF. */
    /* Opcode 0xA0 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xA1 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xA2 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xA3 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xA4 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xA5 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xA6 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xA7 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xA8 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xA9 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xAA - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xAB - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xAC - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xAD - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xAE - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xAF - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0xB0 - 0xBF. */
    /* Opcode 0xB0 - BCS instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BCS), .max_cycles = 3 },
    /* Opcode 0xB1 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xB2 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xB3 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xB4 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xB5 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xB6 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xB7 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xB8 - CLV instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CLV), .max_cycles = 2 },
    /* Opcode 0xB9 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xBA - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xBB - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xBC - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xBD - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xBE - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xBF - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0xC0 - 0xCF. */
    /* Opcode 0xC0 - CPY IMM instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CPY_imm), .max_cycles = 2 },
    /* Opcode 0xC1 - CMP ZER X IDR instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CMP_zer_x_idr), .max_cycles = 6 },
    /* Opcode 0xC2 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xC3 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xC4 - CPY ZER instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CPY_zer), .max_cycles = 3 },
    /* Opcode 0xC5 - CMP ZER instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CMP_zer), .max_cycles = 3 },
    /* Opcode 0xC6 - DEC ZER instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_DEC_zer), .max_cycles = 5 },
    /* Opcode 0xC7 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xC8 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xC9 - CMP IMM instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CMP_imm), .max_cycles = 2 },
    /* Opcode 0xCA - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xCB - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xCC - CPY ABS instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CPY_abs), .max_cycles = 4 },
    /* Opcode 0xCD - CMP ABS instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CMP_abs), .max_cycles = 4 },
    /* Opcode 0xCE - DEC abs instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_DEC_abs), .max_cycles = 6 },
    /* Opcode 0xCF - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0xD0 - 0xDF. */
    /* Opcode 0xD0 - BNE instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BNE), .max_cycles = 3 },
    /* Opcode 0xD1 - CMP ZER Y IDR instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CMP_zer_y_idr), .max_cycles = 5 },
    /* Opcode 0xD2 - CMP ZER IDR instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CMP_zer_idr), .max_cycles = 5 },
    /* Opcode 0xD3 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xD4 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xD5 - CMP ZER X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CMP_zer_x), .max_cycles = 4 },
    /* Opcode 0xD6 - DEC ZER X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_DEC_zer_x), .max_cycles = 6 },
    /* Opcode 0xD7 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xD8 - CLD instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CLD), .max_cycles = 2 },
    /* Opcode 0xD9 - CMP ABS Y instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CMP_abs_y), .max_cycles = 4 },
    /* Opcode 0xDA - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xDB - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xDC - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xDD - CMP ABS X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CMP_abs_x), .max_cycles = 4 },
    /* Opcode 0xDE - DEC ABS X instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_DEC_abs_x), .max_cycles = 7 },
    /* Opcode 0xDF - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0xE0 - 0xEF. */
    /* Opcode 0xE0 - CPX IMM instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CPX_imm), .max_cycles = 2 },
    /* Opcode 0xE1 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xE2 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xE3 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xE4 - CPX ZER instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CPX_zer), .max_cycles = 3 },
    /* Opcode 0xE5 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xE6 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xE7 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xE8 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xE9 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xEA - NOP instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_NOP), .max_cycles = 2 },
    /* Opcode 0xEB - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xEC - CPX ABS instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_CPX_abs), .max_cycles = 4 },
    /* Opcode 0xED - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xEE - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xEF - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },

    /* opcodes 0xF0 - 0xFF. */
    /* Opcode 0xF0 - BEQ instruction. */
    { .exec = &JEMU_SYM(j65c02_inst_BEQ), .max_cycles = 3 },
    /* Opcode 0xF1 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xF2 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xF3 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xF4 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xF5 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xF6 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xF7 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xF8 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xF9 - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xFA - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xFB - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xFC - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xFD - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xFE - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
    /* Opcode 0xFF - TODO implement. */
    { .exec = &JEMU_SYM(j65c02_inst_invalid_opcode), .max_cycles = 2 },
};
