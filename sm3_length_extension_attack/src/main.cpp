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
void output(uint8_t *out){
	for(int i=0;i<Digest_length;i++){
		printf("%02x",out[i]);
	}
	printf("\n");
}

/******************************
 * 函数名：	msg_init
 * 描述：		输入char类型的字符串(from)，将其转变为uint8_t类型的数组(dst)
 * Input：	char *from,uint8_t *dst
******************************/
void msg_init(char *from,uint8_t *dst){
	int len=strlen(from);
	for(int i=0;i<len;i++){
		dst[i]=from[i];
	}
}


/******************************
 * 函数名：	randstr
 * 描述：		随机生成给定长度(len)的字符串(str)
 * Input：	char *str, const int len
******************************/
void randstr(char *str, const int len)
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

/******************************
 * 函数名：	extension_attack
 * 描述：		输入初始消息和拓展消息，输出拓展之后的hash值
******************************/
void extension_attack(){

}

int main(){
	clock_t start,end;
	srand((unsigned int)time(NULL));
	int length=rand()%512+64;
	char *from=new char[length+1];
	char *exten_msg=(char*)"this is length extension attack.";
	int exten_length=strlen(exten_msg);
	uint8_t *msg=new uint8_t[length+1];
	randstr(from,length);
	msg_init(from,msg);
	uint8_t dgst1[Digest_length],dgst2[Digest_length];
	start=clock();

	end=clock();
	cout << "cost time is "<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
}
