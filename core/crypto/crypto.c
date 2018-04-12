// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2017, Linaro Limited
 */

#include <assert.h>
#include <compiler.h>
#include <crypto/aes-ccm.h>
#include <crypto/aes-gcm.h>
#include <crypto/crypto.h>
#include <crypto/crypto_lite.h>
#include <kernel/panic.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_CFG_CRYPTO_WITH_HASH)
TEE_Result crypto_hash_alloc_ctx(void **ctx __unused, uint32_t algo __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

void crypto_hash_free_ctx(void *ctx, uint32_t algo __unused)
{
	if (ctx)
		assert(0);
}

void crypto_hash_copy_state(void *dst_ctx __unused, void *src_ctx __unused,
			    uint32_t algo __unused)
{
	assert(0);
}

TEE_Result crypto_hash_init(void *ctx __unused, uint32_t algo __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}
TEE_Result crypto_hash_update(void *ctx __unused, uint32_t algo __unused,
			      const uint8_t *data __unused, size_t len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}
TEE_Result crypto_hash_final(void *ctx __unused, uint32_t algo __unused,
			     uint8_t *digest __unused, size_t len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}
#endif /*_CFG_CRYPTO_WITH_HASH*/

#if defined(_CFG_CRYPTO_WITH_CIPHER)
TEE_Result crypto_cipher_alloc_ctx(void **ctx, uint32_t algo)
{
	switch (algo) {
#if defined(CFG_CRYPTO_ECB) || defined(CFG_CRYPTO_CBC) || \
	defined(CFG_CRYPTO_CTS) || defined(CFG_CRYPTO_XTS)
	case TEE_ALG_AES_ECB_NOPAD:
	case TEE_ALG_AES_CBC_NOPAD:
	case TEE_ALG_AES_CTS:
	case TEE_ALG_AES_XTS:
		return crypto_cipher_lite_alloc_ctx(ctx, algo);
#endif
	default:
		return _crypto_cipher_alloc_ctx(ctx, algo);
	}
}

void crypto_cipher_free_ctx(void *ctx, uint32_t algo)
{
	switch (algo) {
#if defined(CFG_CRYPTO_ECB) || defined(CFG_CRYPTO_CBC) || \
	defined(CFG_CRYPTO_CTS) || defined(CFG_CRYPTO_XTS)
	case TEE_ALG_AES_ECB_NOPAD:
	case TEE_ALG_AES_CBC_NOPAD:
	case TEE_ALG_AES_CTS:
	case TEE_ALG_AES_XTS:
		crypto_cipher_lite_free_ctx(ctx, algo);
		return;
#endif
	default:
		_crypto_cipher_free_ctx(ctx, algo);
		return;
	}
}

void crypto_cipher_copy_state(void *dst_ctx, void *src_ctx,
			      uint32_t algo)
{
	switch (algo) {
#if defined(CFG_CRYPTO_ECB) || defined(CFG_CRYPTO_CBC) || \
	defined(CFG_CRYPTO_CTS) || defined(CFG_CRYPTO_XTS)
	case TEE_ALG_AES_ECB_NOPAD:
	case TEE_ALG_AES_CBC_NOPAD:
	case TEE_ALG_AES_CTS:
	case TEE_ALG_AES_XTS:
		crypto_cipher_lite_copy_state(dst_ctx, src_ctx, algo);
		return;
#endif
	default:
		_crypto_cipher_copy_state(dst_ctx, src_ctx, algo);
		return;
	}
}

TEE_Result crypto_cipher_init(void *ctx, uint32_t algo,
			      TEE_OperationMode mode,
			      const uint8_t *key1,
			      size_t key1_len,
			      const uint8_t *key2,
			      size_t key2_len,
			      const uint8_t *iv,
			      size_t iv_len)
{
	switch (algo) {
#if defined(CFG_CRYPTO_ECB) || defined(CFG_CRYPTO_CBC) || \
	defined(CFG_CRYPTO_CTS) || defined(CFG_CRYPTO_XTS)
	case TEE_ALG_AES_ECB_NOPAD:
	case TEE_ALG_AES_CBC_NOPAD:
	case TEE_ALG_AES_CTS:
	case TEE_ALG_AES_XTS:
		return crypto_cipher_lite_init(ctx, algo, mode, key1, key1_len,
					      key2, key2_len, iv, iv_len);
#endif
	default:
		return _crypto_cipher_init(ctx, algo, mode, key1, key1_len,
				      key2, key2_len, iv, iv_len);
	}
}

TEE_Result crypto_cipher_update(void *ctx, uint32_t algo,
				TEE_OperationMode mode,
				bool last_block,
				const uint8_t *data,
				size_t len, uint8_t *dst)
{
	switch (algo) {
#if defined(CFG_CRYPTO_ECB) || defined(CFG_CRYPTO_CBC) || \
	defined(CFG_CRYPTO_CTS) || defined(CFG_CRYPTO_XTS)
	case TEE_ALG_AES_ECB_NOPAD:
	case TEE_ALG_AES_CBC_NOPAD:
	case TEE_ALG_AES_CTS:
	case TEE_ALG_AES_XTS:
		return crypto_cipher_lite_update(ctx, algo, mode, last_block,
						data, len, dst);
#endif
	default:
		return _crypto_cipher_update(ctx, algo, mode, last_block,
				     data, len, dst);
	}
}

void crypto_cipher_final(void *ctx, uint32_t algo)
{
	switch (algo) {
#if defined(CFG_CRYPTO_ECB) || defined(CFG_CRYPTO_CBC) || \
	defined(CFG_CRYPTO_CTS) || defined(CFG_CRYPTO_XTS)
	case TEE_ALG_AES_ECB_NOPAD:
	case TEE_ALG_AES_CBC_NOPAD:
	case TEE_ALG_AES_CTS:
	case TEE_ALG_AES_XTS:
		crypto_cipher_lite_final(ctx, algo);
		return;
#endif
	default:
		_crypto_cipher_final(ctx, algo);
		return;
	}
}

TEE_Result crypto_cipher_get_block_size(uint32_t algo __unused,
					size_t *size __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}
#endif /*_CFG_CRYPTO_WITH_CIPHER*/

#if defined(_CFG_CRYPTO_WITH_MAC)
TEE_Result crypto_mac_alloc_ctx(void **ctx, uint32_t algo)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CBC_MAC)
	case TEE_ALG_AES_CBC_MAC_NOPAD:
	case TEE_ALG_AES_CBC_MAC_PKCS5:
	case TEE_ALG_DES_CBC_MAC_NOPAD:
	case TEE_ALG_DES_CBC_MAC_PKCS5:
	case TEE_ALG_DES3_CBC_MAC_NOPAD:
	case TEE_ALG_DES3_CBC_MAC_PKCS5:
		return crypto_cbc_mac_alloc_ctx(ctx, algo);
#endif
#if defined(CFG_CRYPTO_HMAC) || defined(CFG_CRYPTO_CMAC)
	case TEE_ALG_HMAC_MD5:
	case TEE_ALG_HMAC_SHA224:
	case TEE_ALG_HMAC_SHA1:
	case TEE_ALG_HMAC_SHA256:
	case TEE_ALG_HMAC_SHA384:
	case TEE_ALG_HMAC_SHA512:
	case TEE_ALG_AES_CMAC:
		return _crypto_mac_alloc_ctx(ctx, algo);
#endif
	default:
		return TEE_ERROR_NOT_SUPPORTED;
	}
}

void crypto_mac_free_ctx(void *ctx, uint32_t algo)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CBC_MAC)
	case TEE_ALG_AES_CBC_MAC_NOPAD:
	case TEE_ALG_AES_CBC_MAC_PKCS5:
	case TEE_ALG_DES_CBC_MAC_NOPAD:
	case TEE_ALG_DES_CBC_MAC_PKCS5:
	case TEE_ALG_DES3_CBC_MAC_NOPAD:
	case TEE_ALG_DES3_CBC_MAC_PKCS5:
		crypto_cbc_mac_free_ctx(ctx, algo);
		break;
#endif
#if defined(CFG_CRYPTO_HMAC) || defined(CFG_CRYPTO_CMAC)
	case TEE_ALG_HMAC_MD5:
	case TEE_ALG_HMAC_SHA224:
	case TEE_ALG_HMAC_SHA1:
	case TEE_ALG_HMAC_SHA256:
	case TEE_ALG_HMAC_SHA384:
	case TEE_ALG_HMAC_SHA512:
	case TEE_ALG_AES_CMAC:
		_crypto_mac_free_ctx(ctx, algo);
		break;
#endif
	default:
		return;
	}
}

void crypto_mac_copy_state(void *dst_ctx, void *src_ctx,
			   uint32_t algo)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CBC_MAC)
	case TEE_ALG_AES_CBC_MAC_NOPAD:
	case TEE_ALG_AES_CBC_MAC_PKCS5:
	case TEE_ALG_DES_CBC_MAC_NOPAD:
	case TEE_ALG_DES_CBC_MAC_PKCS5:
	case TEE_ALG_DES3_CBC_MAC_NOPAD:
	case TEE_ALG_DES3_CBC_MAC_PKCS5:
		crypto_cbc_mac_copy_state(dst_ctx, src_ctx, algo);
		break;
#endif
#if defined(CFG_CRYPTO_HMAC) || defined(CFG_CRYPTO_CMAC)
	case TEE_ALG_HMAC_MD5:
	case TEE_ALG_HMAC_SHA224:
	case TEE_ALG_HMAC_SHA1:
	case TEE_ALG_HMAC_SHA256:
	case TEE_ALG_HMAC_SHA384:
	case TEE_ALG_HMAC_SHA512:
	case TEE_ALG_AES_CMAC:
		_crypto_mac_copy_state(dst_ctx, src_ctx, algo);
		break;
#endif
	default:
		break;
	}
}

TEE_Result crypto_mac_init(void *ctx, uint32_t algo,
			   const uint8_t *key, size_t len)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CBC_MAC)
	case TEE_ALG_AES_CBC_MAC_NOPAD:
	case TEE_ALG_AES_CBC_MAC_PKCS5:
	case TEE_ALG_DES_CBC_MAC_NOPAD:
	case TEE_ALG_DES_CBC_MAC_PKCS5:
	case TEE_ALG_DES3_CBC_MAC_NOPAD:
	case TEE_ALG_DES3_CBC_MAC_PKCS5:
		return crypto_cbc_mac_init(ctx, algo, key, len);
#endif
#if defined(CFG_CRYPTO_HMAC) || defined(CFG_CRYPTO_CMAC)
	case TEE_ALG_HMAC_MD5:
	case TEE_ALG_HMAC_SHA224:
	case TEE_ALG_HMAC_SHA1:
	case TEE_ALG_HMAC_SHA256:
	case TEE_ALG_HMAC_SHA384:
	case TEE_ALG_HMAC_SHA512:
	case TEE_ALG_AES_CMAC:
		return _crypto_mac_init(ctx, algo, key, len);
#endif
	default:
		return TEE_ERROR_NOT_SUPPORTED;
	}
}

TEE_Result crypto_mac_update(void *ctx, uint32_t algo,
			     const uint8_t *data, size_t len)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CBC_MAC)
	case TEE_ALG_AES_CBC_MAC_NOPAD:
	case TEE_ALG_AES_CBC_MAC_PKCS5:
	case TEE_ALG_DES_CBC_MAC_NOPAD:
	case TEE_ALG_DES_CBC_MAC_PKCS5:
	case TEE_ALG_DES3_CBC_MAC_NOPAD:
	case TEE_ALG_DES3_CBC_MAC_PKCS5:
		return crypto_cbc_mac_update(ctx, algo, data, len);
#endif
#if defined(CFG_CRYPTO_HMAC) || defined(CFG_CRYPTO_CMAC)
	case TEE_ALG_HMAC_MD5:
	case TEE_ALG_HMAC_SHA224:
	case TEE_ALG_HMAC_SHA1:
	case TEE_ALG_HMAC_SHA256:
	case TEE_ALG_HMAC_SHA384:
	case TEE_ALG_HMAC_SHA512:
	case TEE_ALG_AES_CMAC:
		return _crypto_mac_update(ctx, algo, data, len);
#endif
	default:
		return TEE_ERROR_NOT_SUPPORTED;
	}
}

TEE_Result crypto_mac_final(void *ctx, uint32_t algo,
			    uint8_t *digest,
			    size_t digest_len)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CBC_MAC)
	case TEE_ALG_AES_CBC_MAC_NOPAD:
	case TEE_ALG_AES_CBC_MAC_PKCS5:
	case TEE_ALG_DES_CBC_MAC_NOPAD:
	case TEE_ALG_DES_CBC_MAC_PKCS5:
	case TEE_ALG_DES3_CBC_MAC_NOPAD:
	case TEE_ALG_DES3_CBC_MAC_PKCS5:
		return crypto_cbc_mac_final(ctx, algo, digest, digest_len);
#endif
#if defined(CFG_CRYPTO_HMAC) || defined(CFG_CRYPTO_CMAC)
	case TEE_ALG_HMAC_MD5:
	case TEE_ALG_HMAC_SHA224:
	case TEE_ALG_HMAC_SHA1:
	case TEE_ALG_HMAC_SHA256:
	case TEE_ALG_HMAC_SHA384:
	case TEE_ALG_HMAC_SHA512:
	case TEE_ALG_AES_CMAC:
		return _crypto_mac_final(ctx, algo, digest, digest_len);
#endif
	default:
		return TEE_ERROR_NOT_SUPPORTED;
	}
}
#endif /*_CFG_CRYPTO_WITH_MAC*/

TEE_Result crypto_authenc_alloc_ctx(void **ctx, uint32_t algo)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CCM)
	case TEE_ALG_AES_CCM:
		return crypto_aes_ccm_alloc_ctx(ctx);
#endif
#if defined(CFG_CRYPTO_GCM)
	case TEE_ALG_AES_GCM:
		return crypto_aes_gcm_alloc_ctx(ctx);
#endif
	default:
		return TEE_ERROR_NOT_IMPLEMENTED;
	}
}

void crypto_authenc_free_ctx(void *ctx, uint32_t algo)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CCM)
	case TEE_ALG_AES_CCM:
		crypto_aes_ccm_free_ctx(ctx);
		break;
#endif
#if defined(CFG_CRYPTO_GCM)
	case TEE_ALG_AES_GCM:
		crypto_aes_gcm_free_ctx(ctx);
		break;
#endif
	default:
		if (ctx)
			assert(0);
	}
}

void crypto_authenc_copy_state(void *dst_ctx, void *src_ctx, uint32_t algo)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CCM)
	case TEE_ALG_AES_CCM:
		crypto_aes_ccm_copy_state(dst_ctx, src_ctx);
		break;
#endif
#if defined(CFG_CRYPTO_GCM)
	case TEE_ALG_AES_GCM:
		crypto_aes_gcm_copy_state(dst_ctx, src_ctx);
		break;
#endif
	default:
		assert(0);
	}
}

TEE_Result crypto_authenc_init(void *ctx __maybe_unused,
			       uint32_t algo __maybe_unused,
			       TEE_OperationMode mode __maybe_unused,
			       const uint8_t *key __maybe_unused,
			       size_t key_len __maybe_unused,
			       const uint8_t *nonce __maybe_unused,
			       size_t nonce_len __maybe_unused,
			       size_t tag_len __maybe_unused,
			       size_t aad_len __maybe_unused,
			       size_t payload_len __maybe_unused)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CCM)
	case TEE_ALG_AES_CCM:
		return crypto_aes_ccm_init(ctx, mode, key, key_len, nonce,
					   nonce_len, tag_len, aad_len,
					   payload_len);
#endif
#if defined(CFG_CRYPTO_GCM)
	case TEE_ALG_AES_GCM:
		return crypto_aes_gcm_init(ctx, mode, key, key_len, nonce,
					   nonce_len, tag_len);
#endif
	default:
		return TEE_ERROR_NOT_IMPLEMENTED;
	}
}

TEE_Result crypto_authenc_update_aad(void *ctx __maybe_unused,
				     uint32_t algo __maybe_unused,
				     TEE_OperationMode mode __unused,
				     const uint8_t *data __maybe_unused,
				     size_t len __maybe_unused)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CCM)
	case TEE_ALG_AES_CCM:
		return crypto_aes_ccm_update_aad(ctx, data, len);
#endif
#if defined(CFG_CRYPTO_GCM)
	case TEE_ALG_AES_GCM:
		return crypto_aes_gcm_update_aad(ctx, data, len);
#endif
	default:
		return TEE_ERROR_NOT_IMPLEMENTED;
	}
}

TEE_Result crypto_authenc_update_payload(void *ctx __maybe_unused,
					 uint32_t algo __maybe_unused,
					 TEE_OperationMode mode __maybe_unused,
					 const uint8_t *src_data __maybe_unused,
					 size_t src_len __maybe_unused,
					 uint8_t *dst_data __maybe_unused,
					 size_t *dst_len __maybe_unused)
{
	size_t dl = *dst_len;

	*dst_len = src_len;
	if (dl < src_len)
		return TEE_ERROR_SHORT_BUFFER;

	switch (algo) {
#if defined(CFG_CRYPTO_CCM)
	case TEE_ALG_AES_CCM:
		return crypto_aes_ccm_update_payload(ctx, mode, src_data,
						     src_len, dst_data);
#endif
#if defined(CFG_CRYPTO_GCM)
	case TEE_ALG_AES_GCM:
		return crypto_aes_gcm_update_payload(ctx, mode, src_data,
						     src_len, dst_data);
#endif
	default:
		return TEE_ERROR_NOT_IMPLEMENTED;
	}
}

TEE_Result crypto_authenc_enc_final(void *ctx __maybe_unused,
				    uint32_t algo __maybe_unused,
				    const uint8_t *src_data __maybe_unused,
				    size_t src_len __maybe_unused,
				    uint8_t *dst_data __maybe_unused,
				    size_t *dst_len __maybe_unused,
				    uint8_t *dst_tag __maybe_unused,
				    size_t *dst_tag_len __maybe_unused)
{
	size_t dl = *dst_len;

	*dst_len = src_len;
	if (dl < src_len)
		return TEE_ERROR_SHORT_BUFFER;

	switch (algo) {
#if defined(CFG_CRYPTO_CCM)
	case TEE_ALG_AES_CCM:
		return crypto_aes_ccm_enc_final(ctx, src_data, src_len,
						dst_data, dst_tag, dst_tag_len);
#endif
#if defined(CFG_CRYPTO_GCM)
	case TEE_ALG_AES_GCM:
		return crypto_aes_gcm_enc_final(ctx, src_data, src_len,
						dst_data, dst_tag, dst_tag_len);
#endif
	default:
		return TEE_ERROR_NOT_IMPLEMENTED;
	}
}

TEE_Result crypto_authenc_dec_final(void *ctx __maybe_unused,
				    uint32_t algo __maybe_unused,
				    const uint8_t *src_data __maybe_unused,
				    size_t src_len __maybe_unused,
				    uint8_t *dst_data __maybe_unused,
				    size_t *dst_len __maybe_unused,
				    const uint8_t *tag __maybe_unused,
				    size_t tag_len __maybe_unused)
{
	size_t dl = *dst_len;

	*dst_len = src_len;
	if (dl < src_len)
		return TEE_ERROR_SHORT_BUFFER;

	switch (algo) {
#if defined(CFG_CRYPTO_CCM)
	case TEE_ALG_AES_CCM:
		return crypto_aes_ccm_dec_final(ctx, src_data, src_len,
						dst_data, tag, tag_len);
#endif
#if defined(CFG_CRYPTO_GCM)
	case TEE_ALG_AES_GCM:
		return crypto_aes_gcm_dec_final(ctx, src_data, src_len,
						dst_data, tag, tag_len);
#endif
	default:
		return TEE_ERROR_NOT_IMPLEMENTED;
	}
}

void crypto_authenc_final(void *ctx __maybe_unused,
			  uint32_t algo __maybe_unused)
{
	switch (algo) {
#if defined(CFG_CRYPTO_CCM)
	case TEE_ALG_AES_CCM:
		crypto_aes_ccm_final(ctx);
		break;
#endif
#if defined(CFG_CRYPTO_GCM)
	case TEE_ALG_AES_GCM:
		crypto_aes_gcm_final(ctx);
		break;
#endif
	default:
		break;
	}
}

#if !defined(_CFG_CRYPTO_WITH_ACIPHER)
struct bignum *crypto_bignum_allocate(size_t size_bits __unused)
{
	return NULL;
}

TEE_Result crypto_bignum_bin2bn(const uint8_t *from __unused,
				size_t fromsize __unused,
				struct bignum *to __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

size_t crypto_bignum_num_bytes(struct bignum *a __unused)
{
	return 0;
}

size_t crypto_bignum_num_bits(struct bignum *a __unused)
{
	return 0;
}

void crypto_bignum_bn2bin(const struct bignum *from __unused,
			  uint8_t *to __unused)
{
}

void crypto_bignum_copy(struct bignum *to __unused,
			const struct bignum *from __unused)
{
}

void crypto_bignum_free(struct bignum *a)
{
	if (a)
		panic();
}

void crypto_bignum_clear(struct bignum *a __unused)
{
}

/* return -1 if a<b, 0 if a==b, +1 if a>b */
int32_t crypto_bignum_compare(struct bignum *a __unused,
			      struct bignum *b __unused)
{
	return -1;
}
#endif /*!_CFG_CRYPTO_WITH_ACIPHER*/

#if !defined(CFG_CRYPTO_RSA) || !defined(_CFG_CRYPTO_WITH_ACIPHER)
TEE_Result crypto_acipher_alloc_rsa_keypair(struct rsa_keypair *s __unused,
					    size_t key_size_bits __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result
crypto_acipher_alloc_rsa_public_key(struct rsa_public_key *s __unused,
				    size_t key_size_bits __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

void crypto_acipher_free_rsa_public_key(struct rsa_public_key *s __unused)
{
}

TEE_Result crypto_acipher_gen_rsa_key(struct rsa_keypair *key __unused,
				      size_t key_size __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_rsanopad_decrypt(struct rsa_keypair *key __unused,
					   const uint8_t *src __unused,
					   size_t src_len __unused,
					   uint8_t *dst __unused,
					   size_t *dst_len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_rsanopad_encrypt(struct rsa_public_key *key __unused,
					   const uint8_t *src __unused,
					   size_t src_len __unused,
					   uint8_t *dst __unused,
					   size_t *dst_len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_rsaes_decrypt(uint32_t algo __unused,
					struct rsa_keypair *key __unused,
					const uint8_t *label __unused,
					size_t label_len __unused,
					const uint8_t *src __unused,
					size_t src_len __unused,
					uint8_t *dst __unused,
					size_t *dst_len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_rsaes_encrypt(uint32_t algo __unused,
					struct rsa_public_key *key __unused,
					const uint8_t *label __unused,
					size_t label_len __unused,
					const uint8_t *src __unused,
					size_t src_len __unused,
					uint8_t *dst __unused,
					size_t *dst_len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_rsassa_sign(uint32_t algo __unused,
				      struct rsa_keypair *key __unused,
				      int salt_len __unused,
				      const uint8_t *msg __unused,
				      size_t msg_len __unused,
				      uint8_t *sig __unused,
				      size_t *sig_len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_rsassa_verify(uint32_t algo __unused,
					struct rsa_public_key *key __unused,
					int salt_len __unused,
					const uint8_t *msg __unused,
					size_t msg_len __unused,
					const uint8_t *sig __unused,
					size_t sig_len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}
#endif /*!CFG_CRYPTO_RSA || !_CFG_CRYPTO_WITH_ACIPHER*/

#if !defined(CFG_CRYPTO_DSA) || !defined(_CFG_CRYPTO_WITH_ACIPHER)
TEE_Result crypto_acipher_alloc_dsa_keypair(struct dsa_keypair *s __unused,
					    size_t key_size_bits __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result
crypto_acipher_alloc_dsa_public_key(struct dsa_public_key *s __unused,
				    size_t key_size_bits __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_gen_dsa_key(struct dsa_keypair *key __unused,
				      size_t key_size __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_dsa_sign(uint32_t algo __unused,
				   struct dsa_keypair *key __unused,
				   const uint8_t *msg __unused,
				   size_t msg_len __unused,
				   uint8_t *sig __unused,
				   size_t *sig_len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_dsa_verify(uint32_t algo __unused,
				     struct dsa_public_key *key __unused,
				     const uint8_t *msg __unused,
				     size_t msg_len __unused,
				     const uint8_t *sig __unused,
				     size_t sig_len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}
#endif /*!CFG_CRYPTO_DSA || !_CFG_CRYPTO_WITH_ACIPHER*/

#if !defined(CFG_CRYPTO_DH) || !defined(_CFG_CRYPTO_WITH_ACIPHER)
TEE_Result crypto_acipher_alloc_dh_keypair(struct dh_keypair *s __unused,
					   size_t key_size_bits __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_gen_dh_key(struct dh_keypair *key __unused,
				     struct bignum *q __unused,
				     size_t xbits __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result
crypto_acipher_dh_shared_secret(struct dh_keypair *private_key __unused,
				struct bignum *public_key __unused,
				struct bignum *secret __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}
#endif /*!CFG_CRYPTO_DH || !_CFG_CRYPTO_WITH_ACIPHER*/

#if !defined(CFG_CRYPTO_ECC) || !defined(_CFG_CRYPTO_WITH_ACIPHER)
TEE_Result
crypto_acipher_alloc_ecc_public_key(struct ecc_public_key *s __unused,
				    size_t key_size_bits __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_alloc_ecc_keypair(struct ecc_keypair *s __unused,
					    size_t key_size_bits __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

void crypto_acipher_free_ecc_public_key(struct ecc_public_key *s __unused)
{
}

TEE_Result crypto_acipher_gen_ecc_key(struct ecc_keypair *key __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_ecc_sign(uint32_t algo __unused,
				   struct ecc_keypair *key __unused,
				   const uint8_t *msg __unused,
				   size_t msg_len __unused,
				   uint8_t *sig __unused,
				   size_t *sig_len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result crypto_acipher_ecc_verify(uint32_t algo __unused,
				     struct ecc_public_key *key __unused,
				     const uint8_t *msg __unused,
				     size_t msg_len __unused,
				     const uint8_t *sig __unused,
				     size_t sig_len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}

TEE_Result
crypto_acipher_ecc_shared_secret(struct ecc_keypair *private_key __unused,
				 struct ecc_public_key *public_key __unused,
				 void *secret __unused,
				 unsigned long *secret_len __unused)
{
	return TEE_ERROR_NOT_IMPLEMENTED;
}
#endif /*!CFG_CRYPTO_ECC || !_CFG_CRYPTO_WITH_ACIPHER*/
