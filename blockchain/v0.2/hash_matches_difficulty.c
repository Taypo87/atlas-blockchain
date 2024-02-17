#include "blockchain.h"
/**
 * hash_matches_difficulty - checkes if a hash respects a given difficulty
 * @hash: the hash to check
 * @difficulty: the difficulty the has needs to respect
 * Return: 1 if the difficulty is respected, else 0
*/
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
													uint32_t difficulty)
{
	uint8_t mask;
	uint8_t j = difficulty / 8, remains = difficulty % 8, i = 0;

	mask = (((1 << remains) - 1) << (8 - remains));
	for (i = 0; i < j; i++)
	{
		if (hash[i] != 0)
			return (0);
	}
	if (remains && (hash[i] & mask) != 0)
		return (0);
	return (1);





	

}
