#include "transaction.h"
/**
 * unspent_tx_create - allocates and initializes a unspent_tx_out struct
 * @blockhash: the has of the the newly created unspent_tx_out
 * @tx_id: the transaction id
 * @out: copy of the referenced transaction output
*/
unspent_tx_out_t *unspent_tx_out_create(uint8_t block_hash[SHA256_DIGEST_LENGTH],
                        uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *out)
{
    unspent_tx_out_t *unspent = calloc(1, sizeof(unspent_tx_out_t));

    unspent->out = *out;
    memcpy(unspent->tx_id, tx_id, SHA224_DIGEST_LENGTH);
    sha256((int8_t *)unspent, sizeof(unspent->out) + sizeof(unspent->tx_id), unspent->block_hash);
	return (unspent);
}
