/**
 * \file j65c02_step.c
 *
 * \brief Single step an instruction.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "jemu65c02_internal.h"

JEMU_IMPORT_jemu65c02;
JEMU_IMPORT_jemu65c02_internal;

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
JEMU_SYM(j65c02_step)(JEMU_SYM(j65c02)* inst)
{
    status retval;
    uint8_t ins;
    int unused_cycles = 0;

    /* if the processor is in a bad state, return an error. */
    if (inst->crash)
    {
        retval = JEMU_ERROR_INVALID_PROCESSOR_STATE;
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

    /* execute the instruction. */
    retval = ins_fn->exec(inst, &unused_cycles);
    goto done;

done:
    return retval;
}
