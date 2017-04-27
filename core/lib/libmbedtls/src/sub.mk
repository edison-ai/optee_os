srcs-y += tee_lmd_provider.c

# For mbedtls
cflags-y += -Icore/lib/libmbedtls/src/mbedtls/include
cflags-y += -D'MBEDTLS_CONFIG_FILE="mbedtls_config.h"'
cflags-y += -D_FILE_OFFSET_BITS=64 -Wno-old-style-definition -Wno-redundant-decls

# Hashes
srcs-$(CFG_CRYPTO_MD5) += mbedtls/library/md5.c
srcs-$(CFG_CRYPTO_SHA1) += mbedtls/library/sha1.c
ifneq ($(CFG_CRYPTO_SHA224)_$(CFG_CRYPTO_SHA256),n_n)
srcs-y += mbedtls/library/sha256.c
endif
ifneq ($(CFG_CRYPTO_SHA384)_$(CFG_CRYPTO_SHA512),n_n)
srcs-y += mbedtls/library/sha512.c
endif
