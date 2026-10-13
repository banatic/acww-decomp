/* func_ov120_0229b4b0 @ 0x0229b4b0, 0x98 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void MIi_CpuCopy16(void *dest, const void *src, unsigned int size);
extern void *func_ov120_0229b188(void *self);
extern int func_ov120_0229b45c(void *self, int c, int idx);
extern void func_ov120_0229a438(void *self, int n);

void func_ov120_0229b4b0(void *self)
{
    unsigned char *lookup;
    int i, v, srcIdx, dstIdx;

    MIi_CpuCopy16((char *) self + 0x1F20, (char *) self + 0x1720, 0x800);
    lookup = (unsigned char *) func_ov120_0229b188(self);

    for (i = 0; i < 13; i++) {
        v = func_ov120_0229b45c(self, lookup[i], i);
        srcIdx = v * 64 + 19;
        dstIdx = i * 64 + 19;

        *((unsigned short *) ((char *) self + (dstIdx * 2) + 0x1720)) =
            *((unsigned short *) ((char *) self + (srcIdx * 2) + 0x1F20));
        *((unsigned short *) ((char *) self + ((dstIdx + 1) * 2) + 0x1720)) =
            *((unsigned short *) ((char *) self + ((srcIdx + 1) * 2) + 0x1F20));
        *((unsigned short *) ((char *) self + ((dstIdx + 0x20) * 2) + 0x1720)) =
            *((unsigned short *) ((char *) self + ((srcIdx + 0x20) * 2) + 0x1F20));
        *((unsigned short *) ((char *) self + ((dstIdx + 0x21) * 2) + 0x1720)) =
            *((unsigned short *) ((char *) self + ((srcIdx + 0x21) * 2) + 0x1F20));
    }

    func_ov120_0229a438(self, 2);
}
