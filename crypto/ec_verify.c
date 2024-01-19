#include "hblk_crypto.h"
/**
 * ec_verify - verifies an ec signature
 * @key: the EC_KEY struct holding the key pair
 * @msg: the message
 * @msglen: message length
 * @sig: struct containing the signature and sig length
 * Return: 1 on success, else 0
*/
int ec_verify(EC_KEY const *key, uint8_t const *msg,
						size_t msglen, sig_t const *sig)
{
	if (!key || !msg || !sig || !sig->len)
		return (0);
	if (ECDSA_verify(0, msg, msglen, sig->sig, sig->len, (EC_KEY *)key))
		return (1);
	return (0);
}
