#include "transaction.h"

/**
 * tx_out_create - creates and initializes a tx_out_t struct
 * @amount: the amount of the transaction
 * @pub: the public key of transaction receiver
 * Return: pointer to the newly created struct
*/

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *new = calloc(1, sizeof(tx_out_t));

	if (new == NULL)
		return (NULL);

	new->amount = amount;
	memcpy(new->pub, pub, EC_PUB_LEN);
	sha256((int8_t *)new, sizeof(new->amount) + sizeof(new->pub), new->hash);
	return (new);

}
