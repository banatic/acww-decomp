/* func_ov003_02235fb8 @ 0x02235fb8, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022360d8(unsigned short *p, int i, int j);

void func_ov003_02235fb8(char *base, int x, int z)
{
    char *e;
    e = base + (((z - 0x10) >> 4) & 3) * 0x88;
    e = e + (((x - 0x10) >> 4) & 3) * 0x22;
    func_ov003_022360d8((unsigned short *) e, x & 0xf, z & 0xf);
}
