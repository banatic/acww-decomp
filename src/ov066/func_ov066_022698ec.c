/* func_ov066_022698ec @ 0x022698ec, 0x48 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct UnkStruct_022698ec {
    unsigned char pad_00[0xb0];
    int (*unk_B0)(int a, int b, int c, int d);
} UnkStruct_022698ec;

extern UnkStruct_022698ec *data_ov066_0226bdf4;

int func_ov066_022698ec(int a, int b, int c, int d)
{
    UnkStruct_022698ec *p = data_ov066_0226bdf4;
    if (p && p->unk_B0) {
        return p->unk_B0(a, b, c, d);
    }
    return 0;
}
