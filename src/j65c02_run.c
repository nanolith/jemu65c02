/**
 * \file j65c02_step.c
 *
 * \brief Run an instance for a number of cycles.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

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
JEMU_SYM(j65c02_run)(JEMU_SYM(j65c02)* inst, int cycles)
{
    status retval;
    uint8_t ins;
    int ins_cycles = 0;

    /* increment cycles with the cycle delta from the last run. */
    cycles += inst->cycle_delta;
    inst->cycle_delta = 0;

    /* loop until cycles are consumed. */
    for (;;)
    {
        /* if the processor is in a bad state, return an error. */
        if (inst->crash)
        {
            retval = JEMU_ERROR_INVALID_PROCESSOR_STATE;
            goto done;
        }

        /* if the processor is stopped or waiting, consume all cycles and
         * return. */
        if (inst->stopped || inst->wait)
        {
            retval = STATUS_SUCCESS;
            goto done;
        }

        /* fetch an instruction. */
        retval = j65c02_fetch(&ins, inst);
        if (STATUS_SUCCESS != retval)
        {
            goto done;
        }

        /* decode the instruction. */
        const j65c02_instruction* ins_fn =
            JEMU_SYM(global_j65c02_instructions) + ins;

        /* do we have the budget to run this instruction? */
        if (cycles > ins_fn->max_cycles)
        {
            /* execute the instruction. */
            retval = ins_fn->exec(inst, &ins_cycles);
            if (STATUS_SUCCESS != retval)
            {
                goto done;
            }

            /* decrement cycles. */
            cycles -= ins_cycles;
        }
        else
        {
            inst->cycle_delta = cycles > 0 ? cycles : 0;
            retval = STATUS_SUCCESS;
            goto done;
        }
    }

done:
    return retval;

}
