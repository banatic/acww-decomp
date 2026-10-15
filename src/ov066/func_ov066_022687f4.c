/* func_ov066_022687f4 @ 0x022687f4, 0x84 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern struct Type1 *data_ov066_0226bdec;
extern struct Type2 *data_ov066_0226bdf4;
extern void func_ov066_02268798(void *argument0);
extern int WM_SetGameInfo(void (*callback)(void *), unsigned int a, unsigned short b, unsigned int c, unsigned short d,
                          unsigned int e);
extern void func_ov066_0226686c(int status);

struct Type1 {
    unsigned char pad_00[0xb];
    unsigned char unk_0B;
    unsigned char pad_0C[0x1c];
    unsigned int unk_28;
};

struct Type2 {
    unsigned char pad_00[0x8];
    unsigned int unk_08;
    unsigned char pad_0C[0xc];
    unsigned short unk_18;
    unsigned char pad_1A[0x6];
    unsigned short unk_20;
    unsigned char pad_22[0x6a];
    unsigned char unk_8C;
};

void func_ov066_022687f4(void)
{
    unsigned char cond;
    int status;

    cond = ((unsigned int) data_ov066_0226bdf4->unk_8C < (unsigned int) data_ov066_0226bdec->unk_0B) ? 1 : 0;
    status = WM_SetGameInfo(func_ov066_02268798, data_ov066_0226bdf4->unk_08, data_ov066_0226bdf4->unk_18,
                            data_ov066_0226bdec->unk_28, data_ov066_0226bdf4->unk_20, cond);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}
