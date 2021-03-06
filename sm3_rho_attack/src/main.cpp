#include "openssl/evp.h"
#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define Digest_length 32
#define Compare_byte 1		//bytes want to attack

using namespace std;

/******************************
 * 函数名：	sm3_hash_openssl
 * 描述：		传入原始消息(msg)和长度(len)，计算出对应hash值(dgst)
 * Input：	uint8_t *dgst,const void *msg,size_t len
******************************/
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

/******************************
 * 函数名：	output
 * 描述：		输入对应hash值，将结果以16进制输出
 * Input：	uint8_t *out
******************************/
void output(const void *out){
	uint8_t *o=(uint8_t*)out;
	for(int i=0;i<Digest_length;i++){
		printf("%02x",*(o+i));
	}
	printf("\n");
}

/******************************
 * 函数名：	msg_init
 * 描述：		输入char类型的字符串(from)，将其转变为uint8_t类型的数组(dst)
 * Input：	char *from,uint8_t *dst
******************************/
void msg_init(unsigned char *from,uint8_t *dst){
	int len=strlen((char*)from);
	for(int i=0;i<len;i++){
		dst[i]=from[i];
	}
}


/******************************
 * 函数名：	randstr
 * 描述：		随机生成给定长度(len)的字符串(str)
 * Input：	char *str, const int len
******************************/
void randstr(unsigned char *str, const int len)
{
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

#define TIMING

int main(){

	srand((unsigned int)time(NULL));
	uint8_t dgst1[32],dgst2[32];
	int len1=rand()%128+32;
	unsigned char *from1=new unsigned char[len1+1];
	uint8_t *msg1=new uint8_t[len1+1],*msg2=new uint8_t[len1+1];
	unsigned long long count=0;

#ifdef TIMING
	//设置计时变量
	clock_t start,end;
	start=clock();
#endif

	randstr(from1,len1);
	// from1="hello,here is guanjun.this is a sm3 rho attack exp.";
	msg_init(from1,msg1);
	//走一步
	sm3_hash_openssl(dgst1,msg1,len1);
	//走两步
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
			// output(from1);
			break;
		}
	}
#ifdef TIMING
	end=clock();
	cout << "cost time is "<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
#endif
	cout << "rho attack front :"<<Compare_byte*8<<"bit(s)"<<endl;
}
