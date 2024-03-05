#include "transaction.h"

/**
 * transaction_destroy - frees a stransaction struct
 * @transaction: the struct to free
*/
void transaction_destroy(transaction_t *transaction)
{
	int in_size, out_size;

	in_size = llist_size(transaction->inputs);
	out_size = llist_size(transaction->outputs);
	
	llist_destroy(transaction->inputs, in_size, free);
	llist_destroy(transaction->outputs, out_size, free);
	free(transaction);
}
