#include <openssl/sha.h>
#include <string.h>
#include "transaction.h"

/**
 * transaction_is_valid - checks whether a transaction is valid
 * @transaction: pointer to the transaction to verify
 * @all_unspent: list of all unspent transaction outputs to date
 * Return: 1 if the transaction is valid, 0 otherwise
 */
int transaction_is_valid(transaction_t const *transaction, llist_t *all_unspent)
{
    uint8_t hash_buf[SHA256_DIGEST_LENGTH];
    int input_total = 0, output_total = 0;
    tx_in_t *input;
    tx_out_t *output;
    unspent_tx_out_t *unspent;
    EC_KEY *pub_key;
    int i, j, valid;

    if (!transaction || !all_unspent)
        return (0);

    /* Check if the computed hash of the transaction matches the hash stored in it */
    transaction_hash(transaction, hash_buf);
    if (memcmp(hash_buf, transaction->id, SHA256_DIGEST_LENGTH) != 0)
        return (0);

    /* Check each input */
    for (i = 0; i < llist_size(transaction->inputs); i++)
    {
        input = llist_get_node_at(transaction->inputs, i);
        valid = 0;

        for (j = 0; j < llist_size(all_unspent); j++)
        {
            unspent = llist_get_node_at(all_unspent, j);
            if (memcmp(input->tx_id, unspent->out.hash, SHA256_DIGEST_LENGTH) == 0)
            {
                pub_key = ec_from_pub(unspent->out.pub);
                if (!pub_key || !ec_verify(pub_key, transaction->id, SHA256_DIGEST_LENGTH, &input->sig))
                {
                    EC_KEY_free(pub_key);
                    return (0);
                }

                EC_KEY_free(pub_key);
                input_total += unspent->out.amount;
                valid = 1;
                break;
            }
        }

        if (!valid)
            return (0);
    }

    /* Check the total amount of inputs and outputs */
    for (i = 0; i < llist_size(transaction->outputs); i++)
    {
        output = llist_get_node_at(transaction->outputs, i);
        output_total += output->amount;
    }

    if (input_total != output_total)
        return (0);

    return (1);
}
