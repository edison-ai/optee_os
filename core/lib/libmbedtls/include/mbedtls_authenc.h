/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2018, ARM Limited
 */

#ifndef __MBEDTLS_AUTHENC_H__
#define __MBEDTLS_AUTHENC_H__
#include <stddef.h>

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(CFG_CRYPTO_CCM)
#include "mbedtls/ccm.h"
#endif

#endif /* __MBEDTLS_AUTHENC_H__ */
