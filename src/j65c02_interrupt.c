/**
 * \file j65c02_interrupt.c
 *
 * \brief Trigger an interrupt in the emulator instance.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

/**
 * \brief Trigger an interrupt in the instance.
 *
 * \param inst              The instance to interrupt.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
JEMU_SYM(status) FN_DECL_MUST_CHECK
JEMU_SYM(j65c02_interrupt)(JEMU_SYM(j65c02)* inst)
{
    status retval;
    uint8_t addr_low, addr_high;

    /* disable the wait flag on interrupt. */
    inst->wait = false;

    /* checkt to see if interrupts are enabled. */
    if (! (inst->reg_status & JEMU_65c02_STATUS_INTERRUPT))
    {
        /* push the PC onto the stack. */
        retval = j65c02_push(inst, inst->reg_pc >> 8);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }
        retval = j65c02_push(inst, (uint8_t)inst->reg_pc);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        /* push the status register with the break flag clear. */
        retval = j65c02_push(inst, inst->reg_status & ~JEMU_65c02_STATUS_BREAK);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        /* disable interrupts. */
        inst->reg_status |= JEMU_65c02_STATUS_INTERRUPT;

        /* clear decimal mode. */
        inst->reg_status &= ~JEMU_65c02_STATUS_DECIMAL;

        /* fetch the low byte of the new address. */
        retval = inst->read(inst->user_context, 0xFFFE, &addr_low);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        /* fetch the high byte of the new address. */
        retval = inst->read(inst->user_context, 0xFFFF, &addr_high);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        /* set the new address. */
        inst->reg_pc = (addr_high << 8) | addr_low;

        /* success. */
        return STATUS_SUCCESS;
    }
    else
    {
        /* Do nothing if interrupts are disabled. */
        return STATUS_SUCCESS;
    }
}
