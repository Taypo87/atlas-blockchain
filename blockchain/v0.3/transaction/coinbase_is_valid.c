#include "transaction.h"

/**
 * coinbase_is_valid - checks if a coinbase transaction is valid
 * @coinbase: the transaction to check
 * @block_index: index of the block the transaction belongs to
 * Return: 1 if valid, else 0
*/
int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index)
{
	uint8_t id_buffer[32];
	tx_in_t *in_p;
	tx_out_t *out_p;
	uint8_t sig_zero[72] = {0};

	if (!coinbase || !block_index)
		return (0);
	transaction_hash(coinbase, id_buffer);
	if (memcmp(coinbase->id, id_buffer, 32) != 0)
		return (0);
	if (llist_size(coinbase->inputs) > 1 || llist_size(coinbase->outputs) > 1)
		return (0);
	in_p = llist_get_node_at(coinbase->inputs, 0);
	out_p = llist_get_node_at(coinbase->outputs, 0);
	if (memcmp(in_p->tx_out_hash, &block_index, 4) != 0)
		return (0);
	if (out_p->amount != COINBASE_AMOUNT)
		return (0);
	memset(id_buffer, 0, 32);
	if (memcmp(in_p->block_hash, id_buffer, 32) != 0)
		return (0);
	if (memcmp(in_p->tx_id, id_buffer, 32) != 0)
		return (0);
	if (memcmp(in_p->sig.sig, sig_zero, 72) != 0)
		return (0);
	return (1);
}
