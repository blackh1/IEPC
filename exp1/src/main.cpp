#include "../../thirdparty/ssl/include/openssl/evp.h"
#include <iostream>
#include <string.h>
using namespace std;

int sm3_hash(const unsigned char *message, size_t len, unsigned char *hash, unsigned int *hash_len)
{
    EVP_MD_CTX *md_ctx;
    const EVP_MD *md;
    md = EVP_sm3();
    md_ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(md_ctx, md, NULL);
    EVP_DigestUpdate(md_ctx, message, len);
    EVP_DigestFinal_ex(md_ctx, hash, hash_len);
    EVP_MD_CTX_free(md_ctx);
    return 0;
}
int main(){
const unsigned char sample1[] = {'a', 'b', 'c', 0};
	unsigned int sample1_len = strlen((char *)sample1);
	const unsigned char sample2[] = {0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
                                         0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
                                         0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
                                         0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
                                         0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
                                         0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
                                         0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
                                         0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64};
	unsigned int sample2_len = sizeof(sample2);
	unsigned char hash_value[64];
	unsigned int i, hash_len;

	sm3_hash(sample1, sample1_len, hash_value, &hash_len);
	printf("raw data: %s\n", sample1);
	printf("hash length: %d bytes.\n", hash_len);
	printf("hash value:\n");
	for (i = 0; i < hash_len; i++)
	{
	    printf("0x%x  ", hash_value[i]);
	}
	printf("\n\n");

	sm3_hash(sample2, sample2_len, hash_value, &hash_len);
	printf("raw data:\n");
	for (i = 0; i < sample2_len; i++)
	{
	    printf("0x%x  ", sample2[i]);
	}
	printf("\n");
	printf("hash length: %d bytes.\n", hash_len);
	printf("hash value:\n");
	for (i = 0; i < hash_len; i++)
	{
	    printf("0x%x  ", hash_value[i]);
	}
	printf("\n");
	cout << "cmake so difficult";
  return 0;
}