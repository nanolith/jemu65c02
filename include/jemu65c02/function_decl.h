/**
 * \file jemu65c02/function_decl.h
 *
 * \brief Function declaration macros for jemu65c02.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <jemu65c02/config.h>
#include <jemu65c02/macro_tricks.h>

/*
 * With GCC 3.4 and clang, we can force a warning / error if the return value
 * of a function isn't checked.
 */
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
# if (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || (__GNUC__ > 3)
#  define FN_DECL_MUST_CHECK __attribute__((warn_unused_result))
# endif
#endif

/*
 * For other compilers, skip this check.
 */
#ifndef FN_DECL_MUST_CHECK
# define FN_DECL_MUST_CHECK
#endif

/*
 * The JEMU_UNIQUE_NAME is a UUID-based symbol.
 */
#define JEMU_UNIQUE_NAME u0ec71e88_25af_40aa_8dd9_990d596b60de

/*
 * Simple concat macro.
 */
#define JEMU_CONCAT(x,y) x ## y

/*
 * Symbol expansion and combination macro.
 */
#define JEMU_SYM_COMBINE(x, y, z) jemu ## _ ## x ## _ ## y ## _ ## z
#define JEMU_SYM_COMBINE1(x, y, z) JEMU_SYM_COMBINE(x, y, z)

/*
 * The JEMU_SYM macro elevates a given symbol to the JEMU namespace.
 */
#define JEMU_SYM(sym) JEMU_SYM_COMBINE1(JEMU_UNIQUE_NAME, JEMU_VERSION_SYM, sym)

/**
 * Begin an export section.
 */
#define JEMU_BEGIN_EXPORT \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-function\"")

/**
 * End an export section.
 */
#define JEMU_END_EXPORT \
    _Pragma("GCC diagnostic pop")
