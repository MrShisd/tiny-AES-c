#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Enable ECB, CTR and CBC mode. Note this can be done before including aes.h or at compile-time.
// E.g. with GCC by using the -D flag: gcc -c aes.c -DCBC=0 -DCTR=1 -DECB=1
#define CBC 1
#define CTR 0
#define ECB 0

#include "aes.h"

int encrypt_file_cbc128(char *fileName, uint8_t *key ,uint8_t *iv);
int decrypt_file_cbc128(char *fileName, uint8_t *key ,uint8_t *iv);

char * encrypt_string_cbc128(const char *In, int num, uint8_t *key ,uint8_t *iv);
char * decrypt_string_cbc128(const char *In, int num, uint8_t *key ,uint8_t *iv);

int get16ABoutInput(int input);

// int main(void)
// {
    // char *fileName = "1.txt";
    // uint8_t key[] = { 0x62, 0xff, 0x7d, 0x05, 0x37, 0xa5, 0x58, 0x91, 0xa5, 0x7f, 0xd5, 0x38, 0x99, 0x5d, 0x1f, 0x59 };
    // uint8_t iv[]  = { 0x2f, 0xf1, 0x3e, 0xe8, 0x19, 0xc3, 0xa6, 0x18, 0x04, 0x7b, 0x49, 0x1f, 0x57, 0xf7, 0xaa, 0x1c };
    // // encrypt_file_cbc128(fileName,key,iv);
//     decrypt_file_cbc128(fileName,key,iv);

//     return 0;
// }

int get16ABoutInput(int input)
{
    if((input % 16)!=0)
    {
        return input + 16 -(input % 16);
    }
    return input;
}

char * encrypt_string_cbc128(const char *In, int lSIze, uint8_t *key ,uint8_t *iv)
{
    int num = get16ABoutInput(lSIze/sizeof(uint8_t));
    uint8_t *InTmp = (uint8_t *)malloc(sizeof(uint8_t)*num);
    memset(InTmp,' ',sizeof(uint8_t)*num);
    memcpy(InTmp,In,lSIze);
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, InTmp, num);

    return (char *)InTmp;   //may be problem not free

}

char * decrypt_string_cbc128(const char *In, int lSIze, uint8_t *key ,uint8_t *iv)
{
    int num = get16ABoutInput(lSIze/sizeof(uint8_t));
    uint8_t *InTmp = (uint8_t *)malloc(sizeof(uint8_t)*num);
    memset(InTmp,' ',sizeof(uint8_t)*num);
    memcpy(InTmp,In,lSIze);
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, InTmp, num);

    return (char *)InTmp;   //may be problem not free

}
int encrypt_file_cbc128(char *fileName, uint8_t* key ,uint8_t* iv)
{
    FILE *fp;
    if((fp = fopen(fileName,"rb")) == NULL)
    {
        printf("error open input file\n");
        return -1;
    }
    fseek(fp,0,SEEK_END);
    long lSIze = ftell(fp);
    rewind (fp);
    int num = get16ABoutInput(lSIze/sizeof(uint8_t));

    uint8_t *In = (uint8_t *)malloc(sizeof(uint8_t)*num);
    memset(In,' ',sizeof(uint8_t)*num);
    fread(In,sizeof(uint8_t),lSIze,fp);
    fclose(fp);
    
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, In, num);

    FILE *fp1;
    if((fp1 = fopen(fileName,"wb")) == NULL)
    {
        printf("error open input file\n");
        return -1;
    }
    int fNum = fwrite(In,sizeof(uint8_t),num,fp1);
    fclose(fp1);

    free(In);
}   
int decrypt_file_cbc128(char *fileName, uint8_t* key ,uint8_t* iv)
{
    FILE *fp;
    if((fp = fopen(fileName,"rb")) == NULL)
    {
        printf("error open input file\n");
        return -1;
    }
    fseek(fp,0,SEEK_END);
    long lSIze = ftell(fp);
    rewind(fp);

    int num = get16ABoutInput(lSIze/sizeof(uint8_t));
    printf("num:%d\n",num );
    uint8_t *In = (uint8_t *)malloc(sizeof(uint8_t)*num);
    fread(In,sizeof(uint8_t),lSIze,fp);
    fclose(fp);
    
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, In, num);
    FILE *fp1;
    if((fp1 = fopen(fileName,"wb")) == NULL)
    {
        printf("error open input file\n");
        return -1;
    }
    fwrite(In,sizeof(uint8_t),num,fp1);
    fclose(fp1);
    free(In);
}   
