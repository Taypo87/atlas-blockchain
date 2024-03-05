#include "transaction.h"

transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index)
{
    transaction_t *transaction = calloc(1, sizeof(transaction_t));
    tx_out_t *out_P = calloc(1, sizeof(tx_out_t));
    tx_in_t *in_p = calloc(1, sizeof(tx_in_t));
    uint8_t pub_buf[EC_PUB_LEN];
    llist_t *in_list, *out_list;

    if(!receiver)
        return (NULL);

    memcpy(in_p->tx_out_hash, &block_index, 4);
    out_P->amount = COINBASE_AMOUNT;
    ec_to_pub(receiver, pub_buf);
    memcpy(out_P->pub, pub_buf, 32);
    sha256((int8_t *)out_P, sizeof(out_P->amount) + sizeof(out_P->pub), out_P->hash);
    in_list = llist_create(MT_SUPPORT_FALSE);
    out_list = llist_create(MT_SUPPORT_FALSE);
    llist_add_node(in_list, &in_p, ADD_NODE_FRONT);
    llist_add_node(out_list, &out_P, ADD_NODE_FRONT);
    transaction->inputs = in_list;
    transaction->outputs = out_list;
    transaction_hash(transaction, pub_buf);
    memcpy(transaction->id, pub_buf, 32);
    return(transaction);
}
