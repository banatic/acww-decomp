/* func_ov066_022699cc @ 0x022699cc, 0x20 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_022699cc {
    char pad_00[0x1e];
    unsigned short unk_1E;
} *data_ov066_0226bdf4;

int func_ov066_022699cc(void)
{
    return data_ov066_0226bdf4 ? data_ov066_0226bdf4->unk_1E : 0xffff;
}
