/**
 * \file jemu65c02/config.h
 *
 * \brief Generated configuration file data for jemu65c02.
 *
 * \copyright 2022 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#define MAKE_C_VERSION(X,Y) V ## X ## _ ## Y
#define JEMU_VERSION_SYM \
    MAKE_C_VERSION(@JEMU_VERSION_MAJOR@, @JEMU_VERSION_MINOR@)

#define JEMU_VERSION_STRING \
    "@JEMU_VERSION_MAJOR@.@JEMU_VERSION_MINOR@.@JEMU_VERSION_REL@"
