/* func_02013304 @ 0x02013304, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02013384(unsigned char *, unsigned int *);
extern void MI_CpuFill8(void *dst, int val, int len);
extern void MI_CpuCopy8(void *dst, void *src, int len);

struct UnkStruct_02013304 {
    unsigned char unk_00, unk_01, unk_02;
};

struct UnkStruct_02013304 func_02013304(unsigned char *self, unsigned int *argument1)
{
    unsigned char local[3];
    int idx;
    unsigned char *base;
    unsigned char *dst;
    int i;

    idx = func_02013384((unsigned char *) self, (unsigned int *) argument1);
    MI_CpuFill8(local, 0, 3);
    if (idx != -1) {
        base = self + 0x2c;
        dst = base + idx * 3;
        MI_CpuCopy8(dst, local, 3);
        dst = dst + 3;
        for (i = idx; i < 0x1d; i++) {
            MI_CpuCopy8(dst, base, 3);
            dst = dst + 3;
            base = base + 3;
        }
        MI_CpuFill8(self + 0x2c + (0x1d - idx) * 3, 0, (idx + 1) * 3);
    }
    return *(struct UnkStruct_02013304 *) local;
}
