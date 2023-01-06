/**
 * \file j65c02_inst_TSB_abs.c
 *
 * \brief Handle a TSB abs instruction.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Handle a TSB ABS instruction.
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
JEMU_SYM(status) JEMU_SYM(j65c02_inst_TSB_abs)(
    JEMU_SYM(j65c02)* inst, int* cycles)
{
    status retval;
    uint8_t rhs;
    uint16_t addr;
    uint8_t tsb_product, and_product;

    /* fetch the address. */
    retval = j65c02_addr_abs(inst, &addr);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* fetch the value at the address. */
    retval = inst->read(inst->user_context, addr, &rhs);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* compute the TSB product. */
    tsb_product = inst->reg_a | rhs;

    /* compute the AND product. */
    and_product = inst->reg_a & rhs;

    /* write the TSB product to the memory location. */
    retval = inst->write(inst->user_context, addr, tsb_product);
    if (STATUS_SUCCESS != retval)
    {
        return retval;
    }

    /* set the zero flag. */
    if (!and_product)
    {
        inst->reg_status |= JEMU_65c02_STATUS_ZERO;
    }
    else
    {
        inst->reg_status &= ~JEMU_65c02_STATUS_ZERO;
    }

    /* this instruction takes 6 cycles. */
    *cycles = 6;

    return STATUS_SUCCESS;
}
