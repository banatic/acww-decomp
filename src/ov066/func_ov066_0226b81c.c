/* func_ov066_0226b81c @ 0x0226b81c, 0xa0 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int OS_DisableInterrupts(void);
extern unsigned int OS_RestoreInterrupts(unsigned int mask);
extern int func_ov066_0226b8bc(void);

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char pad_05[0x1e - 0x05];
    unsigned short unk_1E;
    unsigned int unk_20;
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
} UnkStruct_0226b81c;

extern UnkStruct_0226b81c *data_ov066_0226be08;

int func_ov066_0226b81c(int a, int b, int c, int d)
{
    int flag = 0;
    unsigned int handle = OS_DisableInterrupts();
    if (func_ov066_0226b8bc() != 0) {
        int zero = flag;
        flag = 1;
        data_ov066_0226be08->unk_04 |= 8;
        data_ov066_0226be08->unk_04 &= ~0x10;
        data_ov066_0226be08->unk_20 = a;
        data_ov066_0226be08->unk_24 = b;
        data_ov066_0226be08->unk_28 = zero;
        data_ov066_0226be08->unk_1E = (unsigned short) c;
        data_ov066_0226be08->unk_2C = d;
    }
    OS_RestoreInterrupts(handle);
    return flag;
}
