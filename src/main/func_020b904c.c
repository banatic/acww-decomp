/* func_020b904c @ 0x020b904c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b904c {
    unsigned char pad_00[0xe0];
    unsigned int unk_E0;
    unsigned char pad_E4[0x4];
    unsigned char unk_E8;
};

int func_020b904c(struct UnkStruct_020b904c *p)
{
    if (p->unk_E8 && p->unk_E0 == 0x1D) {
        return 1;
    }
    return 0;
}
