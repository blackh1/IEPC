#include "openssl/evp.h"
#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define Digest_length 32
#define Compare_byte 3		//bytes want to attack

using namespace std;

//simple sm3 using openssl
int sm3_hash_openssl(uint8_t *dgst,const void *msg,size_t len){
	int res=0;
	const EVP_MD *md=EVP_get_digestbyname("sm3");
	EVP_MD_CTX *mdctx=EVP_MD_CTX_new();
	if(!mdctx)	goto done;

	EVP_DigestInit_ex(mdctx,md,NULL);
	EVP_DigestUpdate(mdctx,msg,len);
	res=EVP_DigestFinal_ex(mdctx,dgst,NULL);

done:
	EVP_MD_CTX_free(mdctx);
	return res;
}

//simple output function
void output(uint8_t *out){
	for(int i=0;i<Digest_length;i++){
		printf("%02x",out[i]);
	}
	printf("\n");
}

//change message from char to uint8
void msg_init(char *from,uint8_t *dst){
	int len=strlen(from);
	for(int i=0;i<len;i++){
		dst[i]=from[i];
	}
}


//generate random string
void randstr(char *str, const int len)
{
	// srand(time(NULL));
	int i;
	for (i = 0; i < len; ++i)
	{
		switch ((rand() % 3))
		{
		case 1:
			str[i] = 'A' + rand() % 26;
			break;
		case 2:
			str[i] = 'a' + rand() % 26;
			break;
		default:
			str[i] = '0' + rand() % 10;
			break;
		}
	}
	str[++i] = '\0';
}

int main(){
	clock_t start,end;
	srand((unsigned int)time(NULL));
	uint8_t dgst1[32],dgst2[32];
	char *from1=new char[32];
	uint8_t *msg1=new uint8_t[32],*msg2=new uint8_t[32];
	unsigned long long count=0;
	start=clock();
	randstr(from1,31);
	int len1=strlen(from1);
	msg_init(from1,msg1);
	sm3_hash_openssl(dgst1,msg1,len1);
	sm3_hash_openssl(dgst2,msg1,len1);
	sm3_hash_openssl(dgst2,dgst2,Digest_length);
	//start attack
	while(true){
		//generate and hash
		sm3_hash_openssl(dgst1,dgst1,Digest_length);
		sm3_hash_openssl(dgst2,dgst2,Digest_length);
		sm3_hash_openssl(dgst2,dgst2,Digest_length);

		//print attempt times
		count++;
		if(count%5000000==0){
			cout << endl<<"count:"<<count<<endl;
		}
		//compare if equal
		if(!memcmp(dgst1,dgst2,Compare_byte)){
			printf("count is %lld\n",count);
			printf("Digest1 is:");
			output(dgst1);
			printf("Digest2 is:");
			output(dgst2);
			printf("Message is :");
			printf("%s\n",from1);
			break;
		}
	}
	end=clock();
	cout << "cost time is "<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
	cout << "rho attack front :"<<Compare_byte*8<<"bit(s)"<<endl;
}