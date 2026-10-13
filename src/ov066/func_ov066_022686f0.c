/* func_ov066_022686f0 @ 0x022686f0, 0xa8 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

struct UnkStruct_022686f0 {
    unsigned char pad_00[0xc];
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned char pad2[6];
    unsigned short unk_1A;
    unsigned short unk_1C;
};
struct UnkStruct_022686f0_2 {
    unsigned char pad_00[0x17];
    unsigned char unk_17;
    unsigned char pad2[0x24];
    int b0 : 1;
    int b1 : 1;
    int b2 : 1;
};

extern struct UnkStruct_022686f0 *data_ov066_0226bdf4;
extern struct UnkStruct_022686f0_2 *data_ov066_0226bdec;
extern void func_ov066_02268570(void);
extern void func_ov066_0226686c(void);
extern int WM_StartMPEx(void (*cb)(void), unsigned int a1, unsigned short a2, unsigned int a3, unsigned short a4,
                        unsigned char a5, int a6, int a7, int a8, int a9, int a10);

void func_ov066_022686f0(void)
{
    if (WM_StartMPEx(func_ov066_02268570, data_ov066_0226bdf4->unk_0C, data_ov066_0226bdf4->unk_1A,
                     data_ov066_0226bdf4->unk_10, data_ov066_0226bdf4->unk_1C, data_ov066_0226bdec->unk_17, 4,
                     data_ov066_0226bdec->b0, data_ov066_0226bdec->b1, 1, data_ov066_0226bdec->b2) == 2) {
        return;
    }
    func_ov066_0226686c();
    return;
}
