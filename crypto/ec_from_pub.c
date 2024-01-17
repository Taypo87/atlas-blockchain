#include "hblk_crypto.h"
/**
 * ec_from_pub - sets an EC_KEY object with a public key
 * @pub: the public key
 * Return: the EC_KEY
*/
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key;

	key = EC_KEY_new();
	EC_KEY_set_public_key(key, pub);
	return (key);
}
