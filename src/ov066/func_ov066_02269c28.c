/* func_ov066_02269c28 @ 0x02269c28, 0x1a4 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

struct Dev {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned short unk_18;
    unsigned short unk_1A;
    unsigned short unk_1C;
    char pad_1E[0x22 - 0x1e];
    unsigned char unk_22;
    char pad_23[0x24 - 0x23];
    unsigned char unk_24;
    char pad_25[0xb8 - 0x25];
    unsigned int unk_B8;
};
extern struct Dev *data_ov066_0226bdf4;

struct Other {
    unsigned int unk_00;
    unsigned int unk_04;
    char pad_08[0xa - 8];
    unsigned char unk_0A;
    char pad_18[0x18 - 0xb];
    unsigned short unk_18;
    unsigned short unk_1A;
    unsigned short unk_1C;
    unsigned short unk_1E;
};
extern struct Other *data_ov066_0226bdec;

extern int data_ov066_0226bdf8;

extern int func_ov066_02266908(int a, int b);
extern void func_ov066_02267ef8(void);
extern void OS_GetMacAddress(void *p);
extern int func_ov066_022683ec(void *p);
extern void func_ov066_02269dcc(void);

void func_ov066_02269c28(void)
{
    unsigned int v0, v1;
    unsigned short a, b;

    data_ov066_0226bdf4->unk_00 = func_ov066_02266908(0x40, 0x20);
    data_ov066_0226bdf4->unk_08 = func_ov066_02266908(0x70, 0x20);
    data_ov066_0226bdf4->unk_18 = 8;

    v0 = (data_ov066_0226bdec->unk_18 + 0xe) * data_ov066_0226bdec->unk_0A + 0x29;
    v0 &= ~0x1fu;
    v1 = (data_ov066_0226bdec->unk_1C + 0x55) & ~0x1fu;
    a = (unsigned short) (v0 * 2);
    b = (unsigned short) (v1 * 2);
    if (a <= b) {
        a = b;
    }
    data_ov066_0226bdf4->unk_1A = a;
    data_ov066_0226bdf4->unk_0C = func_ov066_02266908(data_ov066_0226bdf4->unk_1A, 0x20);

    v0 = (data_ov066_0226bdec->unk_1A + 0x23) & ~0x1fu;
    v1 = (data_ov066_0226bdec->unk_1E + 0x21) & ~0x1fu;
    a = (unsigned short) v0;
    b = (unsigned short) v1;
    if (a <= b) {
        a = b;
    }
    data_ov066_0226bdf4->unk_1C = a;
    data_ov066_0226bdf4->unk_10 = func_ov066_02266908(data_ov066_0226bdf4->unk_1C, 0x20);

    data_ov066_0226bdf4->unk_14 = func_ov066_02266908(data_ov066_0226bdec->unk_1E << 1, 0x20);
    data_ov066_0226bdf4->unk_B8 = 0;

    func_ov066_02267ef8();
    OS_GetMacAddress(&data_ov066_0226bdf4->unk_22);
    data_ov066_0226bdf8 = func_ov066_022683ec(&data_ov066_0226bdf4->unk_24);
    data_ov066_0226bdec->unk_04 = 2;
    data_ov066_0226bdec->unk_00 = 0;

    func_ov066_02269dcc();
}
