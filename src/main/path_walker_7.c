/* path_walker_7: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02013384 @ 0x02013384, 0x2e bytes, Thumb
 * func_02013304 @ 0x02013304, 0x80 bytes, Thumb
 * func_02013300 @ 0x02013300, 0x4 bytes, Thumb
 */

struct UnkStruct_02013304 {
    unsigned char unk_00, unk_01, unk_02;
};

extern void MI_CpuFill8(void *dst, int val, int len);
extern void MI_CpuCopy8(void *dst, void *src, int len);

int func_02013384(unsigned char *r0, unsigned int *r1)
{
    unsigned char *p;
    int i;
    unsigned int a, b;

    p = r0 + 0x2c;
    i = 0;
    while (i < 0x1e) {
        a = *r1;
        b = *p;
        if (a == b) {
            a = *(r1 + 1);
            b = *(p + 1);
            if (a == b) {
                return i;
            }
        }
        p += 3;
        i++;
    }
    return -1;
}

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

int func_02013300(int *p0)
{
    return p0[2];
}
