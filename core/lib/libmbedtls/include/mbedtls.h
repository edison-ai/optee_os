/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2017, ARM Limited
 */

#ifndef LIBMBEDTLS_H
#define LIBMBEDTLS_H
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <stddef.h>

#if defined(_CFG_CRYPTO_WITH_HASH)
#include "mbedtls_hash.h"
#endif

#if defined(_CFG_CRYPTO_WITH_DRBG)
#include "mbedtls_drbg.h"
#endif

#if defined(_CFG_CRYPTO_WITH_CIPHER)
#include "mbedtls_cipher.h"
#endif

#if defined(_CFG_CRYPTO_WITH_MAC)
#include "mbedtls_mac.h"
#endif

#if defined(_CFG_CRYPTO_WITH_ACIPHER)
#include "mbedtls_acipher.h"
#endif

#if defined(_CFG_CRYPTO_WITH_AUTHENC)
#include "mbedtls_authenc.h"
#endif

#endif /* LIBMBEDTLS_H */
