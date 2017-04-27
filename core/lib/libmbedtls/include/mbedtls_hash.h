/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2017, ARM Limited
 */

#ifndef MBEDTLS_HASH_H
#define MBEDTLS_HASH_H
#include <stddef.h>

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(CFG_CRYPTO_MD5)
#include "mbedtls/md5.h"
#endif

#if defined(CFG_CRYPTO_SHA1)
#include "mbedtls/sha1.h"
#endif

#if defined(CFG_CRYPTO_SHA224) || defined(CFG_CRYPTO_SHA256)
#include "mbedtls/sha256.h"
#endif

#if defined(CFG_CRYPTO_SHA384) || defined(CFG_CRYPTO_SHA512)
#include "mbedtls/sha512.h"
#endif

#endif /* MBEDTLS_HASH_H */
