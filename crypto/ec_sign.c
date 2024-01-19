#include "hblk_crypto.h"
/**
 * ec_sign - creates a signature from a given set of bytes
 * @key: the EC_KEY pair
 * @msg: thebytes to sign
 * @msglen: length of the byte array
 * @sig: sig struct that contains the signature and the sig length
 * Return: the signature
*/
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
								 size_t msglen, sig_t *sig)
{
	u_int32_t sig_len = 0;

	if (!key || !msg)
		return (NULL);
	if (ECDSA_sign(0, msg, msglen, sig->sig, &sig_len, (EC_KEY *)key))
	{
		sig->len = sig_len;
		return (sig->sig);
	}
	return (NULL);
}
