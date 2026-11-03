/* shop_list_a: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ae92c @ 0x020ae92c, 0x3e bytes, Thumb
 * func_020ae900 @ 0x020ae900, 0x2a bytes, Thumb
 * func_020ae8e4 @ 0x020ae8e4, 0x1c bytes, Thumb
 * func_020ae8cc @ 0x020ae8cc, 0x18 bytes, Thumb
 * func_020ae8bc @ 0x020ae8bc, 0x10 bytes, Thumb
 * func_020ae850 @ 0x020ae850, 0x6c bytes, Thumb
 * func_020ae834 @ 0x020ae834, 0x1c bytes, Thumb
 * func_020ae814 @ 0x020ae814, 0x1e bytes, Thumb
 * func_020ae7b4 @ 0x020ae7b4, 0x60 bytes, Thumb
 * func_020ae798 @ 0x020ae798, 0x1c bytes, Thumb
 * func_020ae794 @ 0x020ae794, 0x2 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[12];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
} Func020ae92cCtx;

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern int func_020b0038(void *a, void *b, void *c, int d, int e);
extern int func_020aff84(void *a, void *b, void *c, int d);
extern int func_020b0074(int, int, int);
extern int func_0204bcdc(void *p);
extern unsigned int func_0204bc64(void *p);
extern void func_020b0164(int p0, int p1, int p2, int p3, int p4, int p5, int p6);
extern unsigned int func_02062124(void);
extern unsigned int func_02062118(void);
extern unsigned int func_02063cd4(unsigned int, unsigned int);
extern unsigned char data_021f4a80[];

int func_020ae92c(Func020ae92cCtx *self, const void *src)
{
    u8 buf[8];
    MI_CpuCopy8(src, buf, 8);
    if (self->unk_0E != buf[5] || self->unk_0D != buf[4] || self->unk_0C != buf[3] || self->unk_0F != 0) {
        return 1;
    }
    return 0;
}

void func_020ae900(unsigned char *dest, const unsigned char *src)
{
    unsigned char buf[8];

    MI_CpuCopy8((const void *) src, (void *) buf, 8);
    dest[14] = buf[5];
    dest[13] = buf[4];
    dest[12] = buf[3];
    dest[15] = 0;
}

int func_020ae8e4(void *a, void *b, int c)
{
    return func_020b0038(b, a, (char *) a + 0x10, 6, c);
}

int func_020ae8cc(unsigned char *first, unsigned char *second)
{
    return func_020aff84(second, first, first + 0x10, 6);
}

int func_020ae8bc(int a, int b)
{
    return func_020b0074(b, 6, a + 16);
}

static __inline int EqA(void *p, void *q)
{
    if (func_0204bc64(p) == func_0204bc64(q)) {
        return 1;
    }
    return 0;
}

static __inline int EqB(u16 x, u16 y)
{
    if (x == y) {
        return 1;
    }
    return 0;
}

int func_020ae850(void *a, u16 *b)
{
    unsigned int i;
    u16 *p;
    int result;

    for (i = 0; i < 6; i++) {
        p = (u16 *) func_020ae8e4(a, (void *) i, 0);
        if (func_0204bcdc(p)) {
            result = EqA(p, b);
        } else {
            result = EqB(p[0], b[0]);
        }
        if (result != 0) {
            return func_020ae8bc((int) a, i);
        }
    }
    return 0;
}

void func_020ae834(int a, int b)
{
    func_020b0164(a, b, 7, 29, 1, 6, 1);
}

void func_020ae814(int a, int b)
{
    func_020b0164(a, b, 2, 0, 3, 6, 1);
}

void func_020ae7b4(int p0, int p1)
{
    unsigned int v1, v2, v3, v4;

    v1 = func_02062124();
    v2 = func_02062118();
    v3 = func_02063cd4((unsigned int) data_021f4a80, v1 + v2);
    v4 = func_02062124();

    if (v3 < v4) {
        func_020b0164(p0, p1, 6, 0x1d, 1, 6, 1);
    } else {
        func_020b0164(p0, p1, 8, 0x1d, 1, 6, 1);
    }
}

void func_020ae798(int a, int b)
{
    func_020b0164(a, b, 5, 0x1d, 1, 6, 1);
}

void func_020ae794(void *object) {}
