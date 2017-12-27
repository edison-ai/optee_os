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

/**
 * \def MBEDTLS_CMAC_C
 *
 * Enable the CMAC (Cipher-based Message Authentication Code) mode for block
 * ciphers.
 *
 * Module:  library/cmac.c
 *
 * Requires: MBEDTLS_AES_C or MBEDTLS_DES_C
 *
 */
#ifndef MBEDTLS_CMAC_C
#define MBEDTLS_CMAC_C
#endif

#ifdef MBEDTLS_CIPHER_PADDING_PKCS7
#undef MBEDTLS_CIPHER_PADDING_PKCS7
#endif

#define MBEDTLS_PLATFORM_PRINTF_MACRO	(void)

#endif /* MBEDTLS_FEATURE_CONFIG_H */
