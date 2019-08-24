from ctypes import *

#load the shared object file
adder = CDLL('./SEncry.dll')
#define 16 uint8_t array type
Uint8tarray = c_ubyte*16 
#init:
key = Uint8tarray( 0x62, 0x3f, 0x7d, 0x05, 0x37, 0xa5, 0x58, 0x91, 0xa5, 0x7f, 0xd5, 0x38, 0x99, 0x5d, 0x1f, 0x59 );
iv = Uint8tarray( 0x2f, 0xa1, 0x3e, 0xe8, 0x19, 0xc3, 0xa6, 0x18, 0x04, 0x7b, 0x49, 0x1f, 0x57, 0xf7, 0xaa, 0x1c );
fileName = "D:/shixiangdong/PLC/Runtime/home/Administrator/OpenPLC_v3/webserver/POUS.h"
# res_int = adder.encrypt_file_cbc128(fileName,key,iv)
res_int = adder.decrypt_file_cbc128(fileName,key,iv)
# with open(fileName,"rb") as file:
#     content = file.read()
#     print adder.decrypt_string_cbc128(content,len(content),key,iv)
