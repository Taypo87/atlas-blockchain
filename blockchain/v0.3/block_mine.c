#include "blockchain.h"
/**
 * block_mine - mines a block
 * @block: the block to be mined
*/
void block_mine(block_t *block)
{
	uint8_t buff[SHA256_DIGEST_LENGTH];

	block_hash(block, buff);

	while (1)
	{
		if (hash_matches_difficulty(buff, block->info.difficulty))
		{
			memcpy(block->hash, buff, SHA256_DIGEST_LENGTH);
			break;
		}
		block->info.nonce++;
		block_hash(block, buff);
	}
}
