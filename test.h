#ifndef _TEST_H_
#define _TEST_H_
int encrypt_file_cbc128(char *fileName, uint8_t *key ,uint8_t *iv);
int decrypt_file_cbc128(char *fileName, uint8_t *key ,uint8_t *iv);

char * encrypt_string_cbc128(const char *In, int num, uint8_t *key ,uint8_t *iv);
char * decrypt_string_cbc128(const char *In, int num, uint8_t *key ,uint8_t *iv);

int get16ABoutInput(int input);
#endif