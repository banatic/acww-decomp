/* func_020bceb4 @ 0x020bceb4, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef union {
    struct {
        int w0;
        int w1;
    } w;
    u8 b[8];
} DT;

struct UnkStruct_020bceb4 {
    u8 pad_00[0x2f29];
    u8 flag;
};

extern int func_020ba4e4(void);
extern void func_0209e474(DT *);
extern void MI_CpuCopy8(DT *, DT *, u32);
extern u32 func_0209e3ac(DT *, DT *, int);
extern void *func_020bdc50(struct UnkStruct_020bceb4 *, int, int, int, int);

void func_020bceb4(struct UnkStruct_020bceb4 *p)
{
    DT a, b, c;
    int t4, t6, t1;
    u32 r1v, r2v;

    if (p->flag) {
        p->flag = 0;
        t4 = func_020ba4e4() ? 0 : 1;
        a.w.w0 = 0;
        a.w.w1 = 0;
        b.w.w0 = 0;
        b.w.w1 = 0;
        c.w.w0 = 0;
        c.w.w1 = 0;
        func_0209e474(&c);
        MI_CpuCopy8(&c, &a, 8);
        MI_CpuCopy8(&c, &b, 8);
        a.b[4] = 3;
        a.b[3] = 0x10;
        b.b[4] = 9;
        b.b[3] = 0xf;
        r1v = func_0209e3ac(&a, &c, 0x18);
        r2v = func_0209e3ac(&c, &b, 0x18);
        t6 = 0;
        if ((r1v == 0xffffffff || r1v == 0) && (r2v == 0xffffffff || r2v == 0)) {
            t6 = 1;
        }
        a.b[2] = 6;
        b.b[2] = 9;
        r1v = func_0209e3ac(&a, &c, 4);
        r2v = func_0209e3ac(&c, &b, 4);
        t1 = 0;
        if ((r1v == 0xffffffff || r1v == 0) && r2v == 0xffffffff) {
            t1 = 1;
        }
        if (t4 && t6 && t1) {
            func_020bdc50(p, 0xc, 0x3c, 0, 0);
            func_020bdc50(p, 0xc, 0x3c, 0, 1);
            func_020bdc50(p, 0xc, 0x3c, 0, 2);
        }
    }
}
