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
    char hex_str[SHA256_DIGEST_LENGTH * 2 + 1];

    SHA256_Init(&c);
    SHA256_Update(&c, (void *)block, SHA256_DIGEST_LENGTH);
    SHA256_Final(hash_buf, &c);
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(&hex_str[i * 2], "%02x", hash_buf[i]);
    }
    hex_str[SHA256_DIGEST_LENGTH * 2] = '\0';
    return (hex_str);
}
