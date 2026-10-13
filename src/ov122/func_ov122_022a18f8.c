/* func_ov122_022a18f8 @ 0x022a18f8, 0xa0 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_0206fcbc(void *self);
extern void func_ov095_0229c084(void *p, int v);
extern void func_0206e2ec(void *p, int v);
extern void func_0206e1d8(void *p, void *v);
extern void func_ov122_0229f468(void *self, int);
extern void func_ov122_0229f454(void *self, int);
extern void func_0208e95c(void *p, int v);
extern void func_ov002_02209984(void *p, int a, int b, int c);
extern void func_ov002_02208e38(void *p);
extern int func_02065f20(void *p);
extern void func_ov095_0229c050(void *p);
extern void func_ov122_0229efd8(void *self, int);

void func_ov122_022a18f8(char *self)
{
    *(void **) (self + 0xbc) = func_0206fcbc(self);
    func_ov095_0229c084(self + 0xc0, 1);
    func_0206e2ec(self + 0x3ce8, 3);
    func_0206e1d8(self + 0x3ce8, *(void **) (self + 0xbc));
    func_ov122_0229f468(self, 0x10);
    func_ov122_0229f454(self, 0x10);
    *(u16 *) (self + 0xa8) = 0;
    func_0208e95c(self + 0x4010, 1);
    func_ov002_02209984(self + 0x42b0, 6, 1, 0);
    func_ov002_02208e38(self + 0x42b0);
    *(u32 *) (self + 0xa4) = 0;
    if (func_02065f20(*(void **) (self + 0xbc)) != 0) {
        func_ov095_0229c050(self + 0xc0);
        func_ov122_0229efd8(self, 0x10);
    }
}
