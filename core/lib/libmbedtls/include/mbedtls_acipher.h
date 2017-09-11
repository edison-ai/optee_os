/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2017, ARM Limited
 */

#ifndef MBEDTLS_ACIPHER_H
#define MBEDTLS_ACIPHER_H
#include <stddef.h>

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/bignum.h"

#include "mbedtls/ctr_drbg.h"

#include "mbedtls/entropy.h"

#if defined(MBEDTLS_PK_C)
#include "mbedtls/pk.h"
#include "mbedtls/pk_internal.h"
#endif

#if defined(CFG_CRYPTO_DH)
#include "mbedtls/dhm.h"
#endif

#if defined(CFG_CRYPTO_ECC)
#include "mbedtls/ecdsa.h"
#include "mbedtls/ecp.h"
#include "mbedtls/ecdh.h"
#endif

#endif /* MBEDTLS_ACIPHER_H */
