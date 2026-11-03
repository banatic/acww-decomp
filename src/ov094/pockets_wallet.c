/* pockets_wallet: 3 functions, module ov094
 * mwccarm 1.2/base -O4,s
 * func_ov094_022999b0 @ 0x022999b0, 0x10 bytes, Thumb
 * func_ov094_022999a8 @ 0x022999a8, 0x8 bytes, Thumb
 * func_ov094_022999a0 @ 0x022999a0, 0x8 bytes, Thumb
 */

struct UnkStruct_022999b0 {
    unsigned char pad_00[8];
    unsigned short value;
};

int func_ov094_022999b0(struct UnkStruct_022999b0 *s, int mask)
{
    if ((s->value & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov094_022999a8(unsigned short *p0, int p1)
{
    p0[4] = (p0[4] | p1);
}

void func_ov094_022999a0(short *p, int v)
{
    *(unsigned short *) ((char *) p + 8) &= ~v;
}
