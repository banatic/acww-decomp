/* func_0207db48 @ 0x0207db48, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_0208150c(void *self);
extern void *func_0207f1c8(void *self);
extern void *func_0209b5ec(void *x);
extern int func_02003704(void *p);
extern int func_0209c370(void *p);
extern void *func_020036e8(void *p);
extern void *func_0208222c(void *p);
extern void *func_0209bfec(void *p);
extern int func_0209dffc(void *p);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_0209e29c(void *tmp, int flag);
extern int func_0209e3ac(void *list, void *tmp, int size);

typedef struct {
    u32 unk_00;
    u32 w1;
} UnkStruct_0207db48;

int func_0207db48(void *self, void *list)
{
    void *b;
    void *a;
    UnkStruct_0207db48 tmp;
    int result;

    b = func_0208150c(self);
    a = func_0209b5ec(func_0207f1c8(self));

    if (func_02003704(b) == 0) {
        goto fail;
    }
    if (func_0209c370(a) == 0) {
        goto fail;
    }

    b = func_0208222c(func_020036e8(b));
    a = func_0209bfec(a);
    if (func_0209dffc(a) != 0) {
        goto fail;
    }

    tmp.unk_00 = 0;
    tmp.w1 = 0;
    MI_CpuCopy8(a, &tmp, 8);
    ((u8 *) &tmp)[2] = ((u8 *) b)[2];
    ((u8 *) &tmp)[1] = ((u8 *) b)[3];

    if (((u8 *) a)[2] > ((u8 *) b)[2] || (((u8 *) b)[2] == ((u8 *) a)[2] && ((u8 *) b)[3] == ((u8 *) a)[1])) {
        func_0209e29c(&tmp, 1);
    }

    result = func_0209e3ac(list, &tmp, 0x3e) == 1 ? 1 : 0;
    return result;

fail:
    return 0;
}
