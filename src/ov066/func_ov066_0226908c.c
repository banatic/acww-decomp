/* func_ov066_0226908c @ 0x0226908c, 0xc8 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

struct UnkStruct_0226908c {
    unsigned char pad_00[0x1e];
    short unk_1E;
    unsigned char pad1[0x8c - 0x20];
    unsigned char unk_8C;
    unsigned char pad_8D[0xc0 - 0x8d];
    int unk_C0;
};

struct UnkStruct_0226908c_2 {
    unsigned char pad_00[4];
    int unk_04;
    unsigned char pad1[0xb - 8];
    unsigned char unk_0B;
};

extern struct UnkStruct_0226908c *data_ov066_0226bdf4;
extern struct UnkStruct_0226908c_2 *data_ov066_0226bdec;

extern void func_ov066_0226929c(void);
extern void func_ov066_0226987c(int, int);
extern void func_ov066_022687f4(void);
extern void func_ov066_022695ac(int, void *);
extern void func_ov066_02266800(int, int);
extern void func_ov066_0226848c(int);

void func_ov066_0226908c(void *a0)
{
    unsigned char *self = (unsigned char *) a0;

    data_ov066_0226bdf4->unk_C0 |= 0x10;

    if (data_ov066_0226bdec->unk_04 == 6) {
        data_ov066_0226bdec->unk_04 = 9;
        data_ov066_0226bdf4->unk_1E = 0;
        func_ov066_0226929c();

        data_ov066_0226bdf4->unk_C0 |= 0x20;
        func_ov066_0226987c(0xbd8a, data_ov066_0226bdf4->unk_8C);
        func_ov066_022687f4();
    }

    func_ov066_022695ac(*(unsigned short *) (self + 0x10), self + 0xa);
    func_ov066_02266800(0, *(unsigned short *) (self + 0x10));

    if (data_ov066_0226bdf4->unk_8C >= data_ov066_0226bdec->unk_0B) {
        func_ov066_0226848c(0);
    }
}
