#include "hblk_crypto.h"
/**
 * ec_create - creates an EC private and public key pair
 * Return: EC_KEY struct containing the key pair
*/
EC_KEY *ec_create(void)
{
	EC_KEY *key;

	key = EC_KEY_new_by_curve_name(EC_CURVE);
	EC_KEY_generate_key(key);
	return (key);
}
