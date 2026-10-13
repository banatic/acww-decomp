/* func_ov120_0229b548 @ 0x0229b548, 0xbc bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void MIi_CpuCopy16(void *src, void *dst, int size);
extern void MIi_CpuClear16(unsigned short value, void *dst, int size);
extern void func_ov120_0229a438(void *self, int mode);

void func_ov120_0229b548(char *self)
{
    volatile unsigned short buf[4];
    int r4;
    int rows;
    int idx;

    MIi_CpuCopy16(self + 0x1720, self + 0xf20, 0x800);

    rows = (*(unsigned short *) (self + 0x98)) >> 4;
    self[0xa3] = (unsigned char) rows;

    r4 = 0x13;
    for (idx = 0; idx < rows; idx++) {
        buf[0] = 0x10;
        MIi_CpuClear16(buf[0], self + 0xf20 + (r4 << 1), 0x14);
        buf[1] = 0x10;
        MIi_CpuClear16(buf[1], self + 0xf20 + ((r4 + 0x20) << 1), 0x14);
        r4 += 0x40;
    }

    rows += 7;
    r4 = (rows << 6) + 0x13;
    for (idx = rows; idx < 0xd; idx++) {
        buf[2] = 0x10;
        MIi_CpuClear16(buf[2], self + 0xf20 + (r4 << 1), 0x14);
        buf[3] = 0x10;
        MIi_CpuClear16(buf[3], self + 0xf20 + ((r4 + 0x20) << 1), 0x14);
        r4 += 0x40;
    }

    func_ov120_0229a438(self, 2);
}
