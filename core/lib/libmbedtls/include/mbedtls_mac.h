/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2017, ARM Limited
 */

#ifndef __MBEDTLS_MAC_H
#define __MBEDTLS_MAC_H
#include <stddef.h>

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(CFG_CRYPTO_HMAC)
#include "mbedtls/md_internal.h"
#include "mbedtls/md.h"
#endif

#if defined(CFG_CRYPTO_CMAC)
#include "mbedtls/cmac.h"
#endif

#endif /* MBEDTLS_MAC_H */
