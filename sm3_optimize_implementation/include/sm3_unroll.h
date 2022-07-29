/******************************
 * 通过宏定义将迭代压缩的循环过程进行展开
******************************/
#include <string.h>
#include "stdint.h"

typedef unsigned int u32;
typedef unsigned char u8;

#define SM3_DIGEST_LENGTH 32  //摘要长度
#define SM3_BLOCK_SIZE    64  //数据分块长度
#define GETU32(p)         ((u32)(p)[0]<<24|(u32)(p)[1]<<16|(u32)(p)[2]<<8|(u32)(p)[3])  //将u8转换为u32
#define PUTU32(p,v)       ((p)[0]=(u8)((v)>>24),(p)[1]=(u8)((v)>>16),(p)[2]=(u8)((v)>>8),(p)[3]=(u8)(v))  //将u32放到u8数组中

#define ROTL(x,n)         (((x)<<(n))|((x)>>(32-n)))  //循环左移 n bit
#define P0(x)             ((x)^(ROTL((x),9))^(ROTL((x),17)))    //P0(x)=x^(x<<9)^(x<<17)
#define P1(x)             ((x)^(ROTL((x),15))^(ROTL((x),23)))   //P1(x)=x^(x<<15)^(x<<23)

#define FF00(x,y,z)       ((x)^(y)^(z))
#define FF16(x,y,z)       (((x)&(y))|((x)&(z))|((y)&(z)))
#define GG00(x,y,z)       ((x)^(y)^(z))
// #define GG16(x,y,z)       ((((y)^(z))&(x))^(z))              //GmSSL中的GG16，并没读懂
#define GG16(x,y,z)       (((x)&(y))|((~(x))&(z)))              //官方文档中的GG16

#define K0	0x79cc4519U
#define K1	0xf3988a32U
#define K2	0xe7311465U
#define K3	0xce6228cbU
#define K4	0x9cc45197U
#define K5	0x3988a32fU
#define K6	0x7311465eU
#define K7	0xe6228cbcU
#define K8	0xcc451979U
#define K9	0x988a32f3U
#define K10	0x311465e7U
#define K11	0x6228cbceU
#define K12	0xc451979cU
#define K13	0x88a32f39U
#define K14	0x11465e73U
#define K15	0x228cbce6U
#define K16	0x9d8a7a87U
#define K17	0x3b14f50fU
#define K18	0x7629ea1eU
#define K19	0xec53d43cU
#define K20	0xd8a7a879U
#define K21	0xb14f50f3U
#define K22	0x629ea1e7U
#define K23	0xc53d43ceU
#define K24	0x8a7a879dU
#define K25	0x14f50f3bU
#define K26	0x29ea1e76U
#define K27	0x53d43cecU
#define K28	0xa7a879d8U
#define K29	0x4f50f3b1U
#define K30	0x9ea1e762U
#define K31	0x3d43cec5U
#define K32	0x7a879d8aU
#define K33	0xf50f3b14U
#define K34	0xea1e7629U
#define K35	0xd43cec53U
#define K36	0xa879d8a7U
#define K37	0x50f3b14fU
#define K38	0xa1e7629eU
#define K39	0x43cec53dU
#define K40	0x879d8a7aU
#define K41	0x0f3b14f5U
#define K42	0x1e7629eaU
#define K43	0x3cec53d4U
#define K44	0x79d8a7a8U
#define K45	0xf3b14f50U
#define K46	0xe7629ea1U
#define K47	0xcec53d43U
#define K48	0x9d8a7a87U
#define K49	0x3b14f50fU
#define K50	0x7629ea1eU
#define K51	0xec53d43cU
#define K52	0xd8a7a879U
#define K53	0xb14f50f3U
#define K54	0x629ea1e7U
#define K55	0xc53d43ceU
#define K56	0x8a7a879dU
#define K57	0x14f50f3bU
#define K58	0x29ea1e76U
#define K59	0x53d43cecU
#define K60	0xa7a879d8U
#define K61	0x4f50f3b1U
#define K62	0x9ea1e762U
#define K63	0x3d43cec5U

/******************************
 * 说明：  预计算出Tj经过循环移位的值，提高速度
******************************/
uint32_t K[64] = {
	K0,  K1,  K2,  K3,  K4,  K5,  K6,  K7,
	K8,  K9,  K10, K11, K12, K13, K14, K15,
	K16, K17, K18, K19, K20, K21, K22, K23,
	K24, K25, K26, K27, K28, K29, K30, K31,
	K32, K33, K34, K35, K36, K37, K38, K39,
	K40, K41, K42, K43, K44, K45, K46, K47,
	K48, K49, K50, K51, K52, K53, K54, K55,
	K56, K57, K58, K59, K60, K61, K62, K63,
	/*
	0x79cc4519U, 0xf3988a32U, 0xe7311465U, 0xce6228cbU,
	0x9cc45197U, 0x3988a32fU, 0x7311465eU, 0xe6228cbcU,
	0xcc451979U, 0x988a32f3U, 0x311465e7U, 0x6228cbceU,
	0xc451979cU, 0x88a32f39U, 0x11465e73U, 0x228cbce6U,
	0x9d8a7a87U, 0x3b14f50fU, 0x7629ea1eU, 0xec53d43cU,
	0xd8a7a879U, 0xb14f50f3U, 0x629ea1e7U, 0xc53d43ceU,
	0x8a7a879dU, 0x14f50f3bU, 0x29ea1e76U, 0x53d43cecU,
	0xa7a879d8U, 0x4f50f3b1U, 0x9ea1e762U, 0x3d43cec5U,
	0x7a879d8aU, 0xf50f3b14U, 0xea1e7629U, 0xd43cec53U,
	0xa879d8a7U, 0x50f3b14fU, 0xa1e7629eU, 0x43cec53dU,
	0x879d8a7aU, 0x0f3b14f5U, 0x1e7629eaU, 0x3cec53d4U,
	0x79d8a7a8U, 0xf3b14f50U, 0xe7629ea1U, 0xcec53d43U,
	0x9d8a7a87U, 0x3b14f50fU, 0x7629ea1eU, 0xec53d43cU,
	0xd8a7a879U, 0xb14f50f3U, 0x629ea1e7U, 0xc53d43ceU,
	0x8a7a879dU, 0x14f50f3bU, 0x29ea1e76U, 0x53d43cecU,
	0xa7a879d8U, 0x4f50f3b1U, 0x9ea1e762U, 0x3d43cec5U,
	*/
};

static void sm3_compress_blocks(uint32_t digest[8],const void *data,size_t blocks);

typedef struct SM3state_st{
  uint32_t digest[8];       //存放摘要值
  uint64_t nblocks;         //存放已经处理的块数
  unsigned char block[64];  //存放剩余消息
  int num;                  //存放剩余消息的长度
}SM3_CTX;

void sm3_init(SM3_CTX *ctx,uint32_t *IV){
  memset(ctx,0,sizeof(*ctx));
  for(int i=0;i<8;i++){
    memcpy(&(ctx->digest[i]),IV+i,4);
  }
}

void sm3_update(SM3_CTX *ctx,const void* data_from,size_t data_len){
  const unsigned char* data=(unsigned char*)data_from;
  size_t blocks;
  if(ctx->num){
    unsigned int left=SM3_BLOCK_SIZE-ctx->num;  //获取该块剩余长度
    if(data_len<left){
      memcpy(ctx->block+ctx->num,data,data_len);  //将数据复制到对应位置
      ctx->num+=data_len; //增加剩余数据长度
      return;
    }
    else{
      //数据过长，压缩一轮
      memcpy(ctx->block+ctx->num,data,left);  
      sm3_compress_blocks(ctx->digest,ctx->block,1);  //将数据进行压缩一轮
      ctx->nblocks++; //块数+1
      data+=left;     //将指针进行偏移
      data_len-=left;
    }
  }
  blocks=data_len/SM3_BLOCK_SIZE;
  sm3_compress_blocks(ctx->digest,data,blocks);     //对blocks块数据压缩block次
  ctx->nblocks+=blocks;
  data+=SM3_BLOCK_SIZE*blocks;
  data_len-=SM3_BLOCK_SIZE*blocks;

  ctx->num=data_len;
  if(data_len){
    memcpy(ctx->block,data,data_len);
  }
}

void sm3_final(SM3_CTX *ctx,unsigned char *digest){
  int i;
  ctx->block[ctx->num]=0x80;
  if(ctx->num+9<=SM3_BLOCK_SIZE){   //分块剩余大于8byte
    memset(ctx->block+ctx->num+1,0,SM3_BLOCK_SIZE-ctx->num-9);
  }
  else{                             //分块剩余小于8byte
    memset(ctx->block+ctx->num+1,0,SM3_BLOCK_SIZE-ctx->num-1);
    sm3_compress_blocks(ctx->digest,ctx->block,1);      //拓展一块再写入长度
    memset(ctx->block,0,SM3_BLOCK_SIZE-8);
  }
  //放8byte长度数据，以bit为单位
  PUTU32(ctx->block+56,ctx->nblocks>>23);                 //每块64byte，即512bit，所以是>>32<<9等于>>23
  PUTU32(ctx->block+60,(ctx->nblocks<<9)+(ctx->num<<3));

  sm3_compress_blocks(ctx->digest,ctx->block,1);
  for(i=0;i<8;i++){
    PUTU32(digest+i*4,ctx->digest[i]);        //将生成的摘要放入外部传入的变量中
  }
}

void sm3_compress_blocks(uint32_t digest[8],const void *data_from,size_t blocks){
  const unsigned char *data=(unsigned char*)data_from;
  //创建中间需要的临时变量
  uint32_t A,B,C,D,E,F,G,H;
  uint32_t W[68];
  uint32_t SS1,SS2,TT1,TT2;
  int j;

  //开始进行迭代压缩
  while(blocks--){
    A=digest[0],B=digest[1],C=digest[2],D=digest[3];
    E=digest[4],F=digest[5],G=digest[6],H=digest[7];

    //消息初始化
    for(j=0;j<16;j++) W[j]=GETU32(data+j*4);    
    for(;j<68;j++)    W[j]=P1(W[j-16]^W[j-9]^ROTL(W[j-3],15))^ROTL(W[j-13],7)^W[j-6];

    j=0;

    for(;j<16;j++){
      SS1=ROTL((ROTL(A,12)+E+K[j]),7);
      SS2=SS1^ROTL(A,12);
			TT1 = FF00(A, B, C) + D + SS2 + (W[j] ^ W[j + 4]);
			TT2 = GG00(E, F, G) + H + SS1 + W[j];
			D = C;
			C = ROTL(B, 9);
			B = A;
			A = TT1;
			H = G;
			G = ROTL(F, 19);
			F = E;
			E = P0(TT2);
		}

		for (; j < 64; j++) {
			SS1 = ROTL((ROTL(A, 12) + E + K[j]), 7);
			SS2 = SS1 ^ ROTL(A, 12);
			TT1 = FF16(A, B, C) + D + SS2 + (W[j] ^ W[j + 4]);
			TT2 = GG16(E, F, G) + H + SS1 + W[j];
			D = C;
			C = ROTL(B, 9);
			B = A;
			A = TT1;
			H = G;
			G = ROTL(F, 19);
			F = E;
			E = P0(TT2);
		}
    digest[0] ^= A;
		digest[1] ^= B;
		digest[2] ^= C;
		digest[3] ^= D;
		digest[4] ^= E;
		digest[5] ^= F;
		digest[6] ^= G;
		digest[7] ^= H;

		data += 64;
  }
}

void sm3(const unsigned char *msg,size_t msglen,unsigned char dgst[SM3_DIGEST_LENGTH],uint32_t IV[8]){
  SM3_CTX ctx;
  sm3_init(&ctx,IV);
  sm3_update(&ctx,msg,msglen);
  sm3_final(&ctx,dgst);
  memset(&ctx,0,sizeof(SM3_CTX));
}

