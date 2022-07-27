#include <string.h>

#define SM3_WORD unsigned int
#define SM3_CBLOCK 64
#define SM3_LBLOCK (SM3_CBLOCK/4)

typedef struct SM3state_st{
  uint32_t digest[8];
  uint64_t nblocks;
  unsigned char block[64];
  int num;
}SM3_CTX;

void sm3_init(SM3_CTX *ctx,const void *IV){
  memset(ctx,0,sizeof(*ctx));
  for(int i=0;i<8;i++){
    memcpy(&(ctx->digest[i]),(IV+i),4);
  }
}


