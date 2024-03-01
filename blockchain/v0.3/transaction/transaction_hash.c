#include "transaction.h"
/**
 * append_buffer - appends a buffer at 32 byte increments
 * @masterbuffer: the buffer to write to
 * @current: the current location to write to in the buffer
*/
static void append_buffer(u_int8_t *masterbuffer, size_t *current, uint8_t *hash)
{
	memcpy(masterbuffer + *current, hash, 32);
	*current += 32;
}
/**
 * transaction_hash -  computes the ID of a transaction
 * @transaction: struct containing lists of the in and out tx
 * @hash_buff: buffer to store the id
 * Return: pointer to hash_buf
*/
uint8_t *transaction_hash(transaction_t const *transaction,
					uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	tx_in_t *in_node;
	tx_out_t *out_node;
	uint8_t *masterbuff, *hash_buf_p;
	int input = 0, output = 0, i, size_buff;
	size_t current = 0;

	input = llist_size(transaction->inputs);
	output = llist_size(transaction->outputs);
	size_buff = (32 * 3 * input) + (32 * output);
	masterbuff = malloc(size_buff);
	for (i = 0; i < input; i++)
	{
		in_node = llist_get_node_at(transaction->inputs, i);
		append_buffer(masterbuff, &current, in_node->block_hash);
		append_buffer(masterbuff, &current, in_node->tx_id);
		append_buffer(masterbuff, &current, in_node->tx_out_hash);
	}
	for (i = 0; i < output; i++)
	{
		out_node = llist_get_node_at(transaction->outputs, i);
		append_buffer(masterbuff, &current, out_node->hash);
	}
	sha256((const int8_t *)masterbuff, (size_t)size_buff, hash_buf);
	free(masterbuff);
	hash_buf_p = hash_buf;
	return(hash_buf_p);
}
