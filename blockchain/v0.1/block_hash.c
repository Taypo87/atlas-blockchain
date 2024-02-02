#include "blockchain.h"
/**
 * block_hash - hashes a block using sha256
 * @block: the block to be hashed
 * @hash_buf; the buffer to store the hash
 * Return: pointer to the hash_buf
*/
uint8_t *block_hash(block_t const *block, uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
    SHA256_CTX c;

    SHA256_Init(&c);
    SHA256_Update(&c, (void *)block, SHA256_DIGEST_LENGTH);
    SHA256_Final(hash_buf, &c);
    return (hash_buf);
}
