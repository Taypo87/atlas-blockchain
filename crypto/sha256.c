#include "hblk_crypto.h"

/**
 * sha256 - creates a sha hash from given input
*/
uint8_t *sha256(int8_t const *s, size_t len,
            uint8_t digest[SHA256_DIGEST_LENGTH])
{
    SHA256_CTX ctx;

    SHA256_Init(&ctx);
    SHA256_Update(&ctx, (void *)s, len);
    SHA256_Final(digest, &ctx);
    return (digest);
}
