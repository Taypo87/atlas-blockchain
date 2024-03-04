#include "transaction.h"
/**
 * transaction_is_valid - checks whether a transacttion is valid
 * @transaction: pointer the the transaction to verify
 * @all_unspent: pointer to the list of transactions
 * Return: 1 if valid else 0
*/
int transaction_is_valid(transaction_t const *transaction,
										llist_t *all_unspent)
{
	uint8_t buffer[SHA256_DIGEST_LENGTH], *flags;
	int i, input_size, j, unspent_size;
	tx_in_t *in_node;
	unspent_tx_out_t *unspent_node;
	EC_KEY *pub_key;

	unspent_size = llist_size(all_unspent);
	input_size = llist_size(transaction->inputs);
	flags = calloc(input_size, sizeof(uint8_t));
	transaction_hash(transaction, buffer);
	if (memcmp(&buffer, transaction->id, SHA256_DIGEST_LENGTH) != 0)
		return (0);
	for (i = 0; i < input_size; i++)
	{
		in_node = llist_get_node_at(transaction->inputs, i);
		for (j = 0; j < unspent_size; j++)
		{
			unspent_node = llist_get_node_at(all_unspent, j);
			pub_key = ec_from_pub(unspent_node->out.pub);
			if (!ec_verify(pub_key, transaction->id, SHA256_DIGEST_LENGTH, &in_node->sig))
				return (0);
			if (memcmp(unspent_node->out.hash, in_node->tx_out_hash,
				 SHA256_DIGEST_LENGTH) == 0
				&& memcmp(unspent_node->tx_id, in_node->tx_id,
				 SHA256_DIGEST_LENGTH) == 0 &&
				memcmp(unspent_node->block_hash,
				 in_node->block_hash, SHA256_DIGEST_LENGTH) == 0) 
			{
				flags[i] = 1;
				break;
			}
			
		}
		EC_KEY_free(pub_key);
		if (!flags[i])
		{
			free(flags);
			return (0);
		}
	}
	free(flags);
	return (1);
}
