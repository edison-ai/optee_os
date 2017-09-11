srcs-y += tee_lmd_provider.c

# For mbedtls
cflags-y += -Icore/lib/libmbedtls/src/mbedtls/include
cflags-y += -D'MBEDTLS_CONFIG_FILE="mbedtls_config.h"'
cflags-y += -D_FILE_OFFSET_BITS=64 -Wno-old-style-definition \
	-Wno-redundant-decls -Wno-switch-default -Wno-unused-parameter

# Hashes
srcs-$(CFG_CRYPTO_MD5) += mbedtls/library/md5.c
srcs-$(CFG_CRYPTO_SHA1) += mbedtls/library/sha1.c
ifneq ($(CFG_CRYPTO_SHA224)_$(CFG_CRYPTO_SHA256),n_n)
srcs-y += mbedtls/library/sha256.c
endif
ifneq ($(CFG_CRYPTO_SHA384)_$(CFG_CRYPTO_SHA512),n_n)
srcs-y += mbedtls/library/sha512.c
endif

# Cipher
srcs-$(CFG_CRYPTO_AES) += mbedtls/library/aes.c
srcs-$(CFG_CRYPTO_GCM) += mbedtls/library/aesni.c
srcs-$(CFG_CRYPTO_GCM) += mbedtls/library/arc4.c
srcs-$(CFG_CRYPTO_GCM) += mbedtls/library/blowfish.c
srcs-$(CFG_CRYPTO_CCM) += mbedtls/library/ccm.c
srcs-$(CFG_CRYPTO_GCM) += mbedtls/library/camellia.c
srcs-$(CFG_CRYPTO_DES) += mbedtls/library/des.c
srcs-$(CFG_CRYPTO_GCM) += mbedtls/library/gcm.c
srcs-$(_CFG_CRYPTO_WITH_CIPHER) += mbedtls/library/cipher.c \
			mbedtls/library/cipher_wrap.c

#MAC
srcs-$(CFG_CRYPTO_HMAC) += mbedtls/library/md.c \
                         mbedtls/library/md_wrap.c
srcs-$(CFG_CRYPTO_CMAC) += mbedtls/library/cmac.c

# DRBG
ifneq ($(CFG_CRYPTO_CTR_DRBG)_$(CFG_CRYPTO_HMAC_DRBG),n_n)
srcs-y += mbedtls/library/entropy.c
endif
srcs-$(CFG_CRYPTO_CTR_DRBG) += mbedtls/library/ctr_drbg.c
srcs-$(CFG_CRYPTO_HMAC_DRBG) += mbedtls/library/hmac_drbg.c
ifeq ($(CFG_CRYPTO_CTR_DRBG),y)
ifeq ($(CFG_CRYPTO_AES),n)
srcs-y += mbedtls/library/aes.c
endif
endif

# Asymmetric ciphers
srcs-$(_CFG_CRYPTO_WITH_ACIPHER) += mbedtls/library/bignum.c
srcs-$(_CFG_CRYPTO_WITH_ACIPHER) += mbedtls/library/ctr_drbg.c
srcs-$(_CFG_CRYPTO_WITH_ACIPHER) += mbedtls/library/oid.c
srcs-$(_CFG_CRYPTO_WITH_ASN1) += mbedtls/library/asn1parse.c
srcs-$(_CFG_CRYPTO_WITH_ASN1) += mbedtls/library/asn1write.c
srcs-$(_CFG_CRYPTO_WITH_ACIPHER) += mbedtls/library/pk_wrap.c
srcs-$(_CFG_CRYPTO_WITH_ACIPHER) += mbedtls/library/pk.c
# RSA
srcs-$(CFG_CRYPTO_RSA) += mbedtls/library/rsa.c
# ECDSA
srcs-$(CFG_CRYPTO_ECC) += mbedtls/library/ecp_curves.c
srcs-$(CFG_CRYPTO_ECC) += mbedtls/library/ecp.c
srcs-$(CFG_CRYPTO_ECC) += mbedtls/library/ecdsa.c
# DH
srcs-$(CFG_CRYPTO_DH) += mbedtls/library/dhm.c
