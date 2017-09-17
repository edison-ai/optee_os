/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2017, ARM Limited
 */

#ifndef MBEDTLS_FEATURE_CONFIG_H
#define MBEDTLS_FEATURE_CONFIG_H

#include "mbedtls/config.h"

/**
 * \def MBEDTLS_SELF_TEST
 *
 * Disable the checkup functions (*_self_test).
 */
#ifdef MBEDTLS_SELF_TEST
#undef MBEDTLS_SELF_TEST
#endif

/**
 * \def MBEDTLS_FS_IO
 *
 * Disable functions that use the filesystem.
 */
#ifdef MBEDTLS_FS_IO
#undef MBEDTLS_FS_IO
#endif

/**
 * \def MBEDTLS_RIPEMD160_C
 *
 * Disable the RIPEMD-160 hash algorithm.
 */
#ifdef MBEDTLS_RIPEMD160_C
#undef MBEDTLS_RIPEMD160_C
#endif

/**
 * \def MBEDTLS_HAVE_TIME
 *
 * Disable time functions
 */
#ifdef MBEDTLS_HAVE_TIME
#undef MBEDTLS_HAVE_TIME
#endif

/**
 * \def MBEDTLS_HAVE_TIME_DATE
 *
 * Disable time date
 */
#ifdef MBEDTLS_HAVE_TIME_DATE
#undef MBEDTLS_HAVE_TIME_DATE
#endif

/**
 * \def MBEDTLS_TIMING_C
 *
 * Disable the semi-portable timing interface.
 */
#ifdef MBEDTLS_TIMING_C
#undef MBEDTLS_TIMING_C
#endif

/**
 * \def MBEDTLS_NO_PLATFORM_ENTROPY
 *
 * Enable the built-in platform entropy functions.
 */
#ifndef MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_NO_PLATFORM_ENTROPY
#endif

#define MBEDTLS_PLATFORM_PRINTF_MACRO	(void)

#endif /* MBEDTLS_FEATURE_CONFIG_H */
