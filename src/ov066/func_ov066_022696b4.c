/* func_ov066_022696b4 @ 0x022696b4, 0x74 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_02268a1c(int);

typedef struct {
    int unk_00;
    int unk_04;
    unsigned char pad_08[0xc0 - 8];
    unsigned int unk_C0;
} UnkStruct_022696b4;

extern UnkStruct_022696b4 *data_ov066_0226bdec;
extern UnkStruct_022696b4 *data_ov066_0226bdf4;

void func_ov066_022696b4(int a, int b)
{
    UnkStruct_022696b4 *ip;
    UnkStruct_022696b4 *q;

    ip = data_ov066_0226bdec;
    if (ip->unk_04 != 4) {
        return;
    }
    if (a == 0) {
        return;
    }
    ip->unk_04 = 8;
    q = data_ov066_0226bdf4;
    q->unk_C0 = (q->unk_C0 & ~0x40) | ((b & 1) << 6);
    func_ov066_02268a1c(a + 0x20);
}
