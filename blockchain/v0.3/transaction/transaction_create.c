#include "transaction.h"

transaction_t *transaction_create(EC_KEY const *sender,
    EC_KEY const *receiver, uint32_t amount, llist_t *all_unspent)
{
    transaction_t *transaction = calloc(1, sizeof(transaction_t));
    unspent_tx_out_t *unspent_node;
    uint32_t unspent_size = 0, i;
    uint32_t total_amount = 0;
    uint8_t sender_pub_buffer[65], reciever_pub_buffer[65], hash_buff[32], *hash_buff_p;
    tx_out_t *transaction_out, *transaction_return;
    tx_in_t *unspent_input;
    llist_t *unspent_out, *in;

    ec_to_pub(sender, sender_pub_buffer);
    ec_to_pub(receiver, reciever_pub_buffer);
    unspent_size = llist_size(all_unspent);
    in = llist_create(MT_SUPPORT_FALSE);
    for (i = 0; i < unspent_size; i++)
    {
        unspent_node = llist_get_node_at(all_unspent, i);
        if (memcmp(sender_pub_buffer, unspent_node->out.pub, 64) == 0)
        {
            unspent_input = tx_in_create(unspent_node);
            llist_add_node(in, unspent_input, ADD_NODE_REAR);
            total_amount += unspent_node->out.amount;
        }
    }
    if (total_amount < amount)
        return (NULL);
    unspent_out = llist_create(MT_SUPPORT_FALSE);
    transaction_out = tx_out_create(amount, reciever_pub_buffer);
    llist_add_node(unspent_out, transaction_out, ADD_NODE_REAR);
    if (total_amount > amount)
    {
        transaction_return = tx_out_create(total_amount - amount, sender_pub_buffer);
        llist_add_node(unspent_out, transaction_return, ADD_NODE_REAR);
    }
    transaction->outputs = unspent_out;
    transaction->inputs = in;
    hash_buff_p = transaction_hash(transaction, hash_buff);
    memcpy(transaction->id, hash_buff_p, 32);
    for (i = 0; (int)i < llist_size(in); i++)
    {
        unspent_input = llist_get_node_at(in, i);
        tx_in_sign(unspent_input, hash_buff_p, sender, (llist_t *)in);
    }

    return (transaction);
    
}