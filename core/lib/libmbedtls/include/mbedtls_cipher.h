/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2017, ARM Limited
 */

#ifndef __MBEDTLS_CIPHERTWO_H
#define __MBEDTLS_CIPHERTWO_H
#include <stddef.h>

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(_CFG_CRYPTO_WITH_CIPHER)
#include "mbedtls/cipher.h"
#include "mbedtls/cipher_internal.h"
#endif

#if defined(CFG_CRYPTO_DES)
#include "mbedtls/des.h"
#endif

#if defined(CFG_CRYPTO_AES)
#include "mbedtls/aes.h"
#endif

#endif /* MBEDTLS_CIPHERTWO_H */
