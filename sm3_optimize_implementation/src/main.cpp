#include <openssl/evp.h>
#include "sm3.h"


#define Digest_length 32
#define Compare_byte 1		//bytes want to attack
#define ll long long
#define ull unsigned long long
using namespace std;

uint32_t IV[8]={
	0x7380166f,0x4914b2b9,
	0x172442d7,0xda8a0600,
	0xa96f30bc,0x163138aa,
	0xe38dee4d,0xb0fb0e4e,
};
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
void output(const void *out,int length){
	uint8_t *o=(uint8_t*)out;
	for(int i=0;i<length;i++){
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

/******************************
 * 函数名： msg_merge
 * 描述：		输入原始消息和拓展消息，按照要求返回拼接好的字符串
 * Input：	
******************************/
unsigned char* msg_merge(unsigned char* msg1,unsigned char* msg2,ull length1,ull length2,ull &new_length){
	ull tmp=64*ceil(length1/64.0);
	if((length1&63)>55)	tmp+=64;
	new_length=tmp+length2;
	unsigned char* msg=new unsigned char[new_length];
	memset(msg,0,new_length);
	memcpy(msg,msg1,length1);
	memcpy(msg+tmp,msg2,length2);
	msg[length1]=0x80;
	// for(int i=0;i<8;i++){
	// 	msg[tmp-8+i]=(length1>>(i*8))&0xff;
	// }
	PUTU32(msg+tmp-8,length1>>29);
	PUTU32(msg+tmp-4,(length1&0xffffffff)<<3);
	return msg;
} 


//将1byte转换为4byte，注意大小端问题！
void u8_to_u32(const void *from,uint32_t *to){
	uint8_t *f=(uint8_t*)from;
	for(int i=0;i<Digest_length/4;i++){
		*(to+i)=GETU32((f+i*4));
	}
}

/******************************
 * 函数名：	extension_attack
 * 描述：		输入初始消息和拓展消息，输出拓展之后的hash值
******************************/
void extension_attack(const void *hash_value,ull length1,ull length2,unsigned char* exten_msg,const void *digest){
	unsigned char* dgst=(unsigned char*)digest;
	ull tmp=64*ceil(length1/64.0);
	if((length1&63)>55)	tmp+=64;
	SM3_CTX ctx;
	uint32_t new_iv[8];
	u8_to_u32(hash_value,new_iv);
	//将原本消息作为iv值
	sm3_init(&ctx,new_iv);
	//设置剩余消息长度为拓展消息长度
	size_t blocks=tmp/SM3_BLOCK_SIZE;
	ctx.nblocks=blocks;
	if(length2<56){
		memcpy(ctx.block,exten_msg,length2);
			ctx.num=length2;
	}
	else{
		sm3_update(&ctx,exten_msg,length2);
	}
	sm3_final(&ctx,dgst);

	memset(&ctx,0,sizeof(SM3_CTX));
}

int main(){
	srand((unsigned int)time(NULL));
	ull length=1024;
	unsigned char *from=new unsigned char[length+1];
	ull int new_length=0;
	uint8_t *msg=new uint8_t[length+1];
	randstr(from,length);
	// from=(unsigned char*)"abc";
	// length=3;
	msg_init(from,msg);
	uint8_t dgst1[Digest_length],dgst2[Digest_length],dgst3[Digest_length];

#ifdef TIMING
	clock_t start,end;
	start=clock();
#endif

	for(int i=0;i<0xfffffe;i++){
		sm3(from,length,dgst2,IV);
	}
#ifdef TIMING
	end=clock();
	output(dgst2,Digest_length);
	cout << "cost time is "<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
#endif
}
