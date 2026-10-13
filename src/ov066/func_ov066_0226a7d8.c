/* func_ov066_0226a7d8 @ 0x0226a7d8, 0x38 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov066_022668c4(int);
extern void OS_CancelAlarms(int);

struct func_ov066_0226a7d8_arg {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    int unk_04;
    int unk_08;
};

void func_ov066_0226a7d8(struct func_ov066_0226a7d8_arg *p)
{
    p->unk_01 = 0;
    p->unk_02 = 0;
    OS_CancelAlarms(p->unk_00 + 0x80);
    func_ov066_022668c4(p->unk_08);
    func_ov066_022668c4(p->unk_04);
}
