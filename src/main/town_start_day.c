/* town_start_day: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209fae8 @ 0x0209fae8, 0x2 bytes, Thumb
 * func_0209fae4 @ 0x0209fae4, 0x2 bytes, Thumb
 * func_0209fad4 @ 0x0209fad4, 0xe bytes, Thumb
 * func_0209faac @ 0x0209faac, 0x28 bytes, Thumb
 * func_0209fa40 @ 0x0209fa40, 0x6c bytes, Thumb
 * func_0209fa30 @ 0x0209fa30, 0xe bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
} UnkStruct_0209fa30;

extern void func_0209df64(void *);
extern void MI_CpuCopy8(const void *, void *, unsigned int);
extern void func_0209e474(void *p);
extern void func_0209e29c(void *p, int n);
extern int func_0209e3ac(const void *a, const void *b, int mask);

int func_0209fa30(UnkStruct_0209fa30 *s);

void func_0209fae8(void *self) {}

void func_0209fae4(void *self) {}

void func_0209fad4(unsigned char *r0)
{
    r0[0] = 1;
    r0[1] = 1;
    r0[2] = 0;
    r0[3] = 0;
}

int func_0209faac(void *obj, const void *src)
{
    unsigned char local[4];
    if (src == 0) {
        func_0209df64(local);
        src = local;
    }
    MI_CpuCopy8(src, obj, 4);
    ((unsigned char *) obj)[3] = 1;
    return 1;
}

void func_0209fa40(u8 *arg)
{
    u64 t[2];

    if (func_0209fa30((UnkStruct_0209fa30 *) arg) == 0) {
        return;
    }
    t[0] = 0;
    t[1] = 0;
    func_0209e474(&t[0]);
    ((u8 *) t)[13] = arg[2];
    ((u8 *) t)[12] = arg[1];
    ((u8 *) t)[11] = arg[0];
    ((u8 *) t)[10] = 0;
    if (func_0209e3ac(&t[1], &t[0], 0x3c) == 1) {
        goto zero;
    }
    ((u8 *) t)[10] = 6;
    func_0209e29c(&t[1], 1);
    if (func_0209e3ac(&t[1], &t[0], 0x3c) == 1) {
        return;
    }
    arg[3] = 0;
    return;
zero:
    arg[3] = 0;
}

int func_0209fa30(UnkStruct_0209fa30 *s)
{
    if (s->unk_03 == 0) {
        return 0;
    }
    return 1;
}
