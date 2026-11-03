/* local_host_2: 2 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_022687f4 @ 0x022687f4, 0x84 bytes, ARM
 * func_ov066_02268798 @ 0x02268798, 0x5c bytes, ARM
 */

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

extern struct Type1 *data_ov066_0226bdec;
extern struct Type2 *data_ov066_0226bdf4;
extern int WM_SetGameInfo(void (*callback)(void *), unsigned int a, unsigned short b, unsigned int c, unsigned short d,
                          unsigned int e);
extern void func_ov066_0226686c(int status);
extern int func_ov066_02266e08(void);
extern void func_ov066_022686f0(void);

void func_ov066_02268798(unsigned short *param);

void func_ov066_022687f4(void)
{
    unsigned char cond;
    int status;

    cond = ((unsigned int) data_ov066_0226bdf4->unk_8C < (unsigned int) data_ov066_0226bdec->unk_0B) ? 1 : 0;
    status = WM_SetGameInfo((void (*)(void *)) func_ov066_02268798, data_ov066_0226bdf4->unk_08, data_ov066_0226bdf4->unk_18,
                            data_ov066_0226bdec->unk_28, data_ov066_0226bdf4->unk_20, cond);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}

void func_ov066_02268798(unsigned short *param)
{
    unsigned int *p;
    int v;

    if (func_ov066_02266e08() == 0) {
        if (param[1] == 0) {
            p = (unsigned int *) (*(unsigned int *) &data_ov066_0226bdf4);
            v = *(unsigned int *) ((char *) p + 0xc0);
            v = (v << 0x1a) >> 0x1f;
            if (v != 0) {
                func_ov066_022686f0();
            }
        } else {
            func_ov066_0226686c(param[1]);
        }
    }
}
