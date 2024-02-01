#include "blockchain.h"
#include <time.h>

block_t *block_create(block_t const *prev, int8_t const *data, uint32_t data_len)
{
    block_t *new_block = calloc(1, sizeof(block_t));

    memcpy(new_block->data.buffer, data, BLOCKCHAIN_DATA_MAX);
    new_block->data.len = data_len;

/*
    might not need this line since we used calloc
    memset(new_block->hash, 0, SHA256_DIGEST_LENGTH);
*/
    new_block->info.index = prev->info.index + 1;
    new_block->info.timestamp = time(NULL);
    memcpy(new_block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);

    return (new_block);
}
