#include "blockchain.h"
#include <time.h>
/**
 * block_create - creates a new block in the blockchain
 * @prev: pointer to the previous block
 * @data: data to be stored in the new block
 * @data_len: length of data
 * Return: pointer to the new_block
*/
block_t *block_create(block_t const *prev, int8_t const *data,
												uint32_t data_len)
{
	time_t current;
	block_t *new_block = calloc(1, sizeof(block_t));

	current = time(NULL);
	memcpy(new_block->data.buffer, data, data_len);
	new_block->data.len = data_len;
	new_block->info.index = prev->info.index + 1;
	new_block->info.timestamp = current;
	memcpy(new_block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);

	return (new_block);
}
