#include "transaction.h"

/**
 * tx_in_create - creates a new tx_in struct
 * @unspent: the unsepnt tx out struct being converted
 * Return: pointer to the newly allocated struct
*/
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *new = calloc(1, sizeof(tx_in_t));

	memcpy(new->block_hash, unspent->block_hash, SHA256_DIGEST_LENGTH);
	memcpy(new->tx_id, unspent->tx_id, SHA256_DIGEST_LENGTH);
	memcpy(new->tx_out_hash, unspent->out.hash, SHA256_DIGEST_LENGTH);

	return (new);
}