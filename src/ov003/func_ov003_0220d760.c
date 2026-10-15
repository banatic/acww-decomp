/* func_ov003_0220d760 @ 0x0220d760, 0xc0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02010f5c(void *p);
extern int func_0203f7d0(void *a, void *b);
extern u32 func_020912d4(u32 a, void *b, void *c, int _x);
extern void func_02091278(void *, void *, void *, void *);
extern u32 func_02056f28(void *a, u32 b);
extern u32 func_020984fc(u32 a);
extern void func_0209971c(u32 a, void *b);
extern void func_0205eb8c(void *a, void *b, u32 c);

void func_ov003_0220d760(char *self)
{
    u16 shorts[2];
    u32 a, b, c, v;
    int x;

    func_02010f5c(self);
    v = *(u32 *) (self + 0x2d8);
    x = (int) ((v << 4) >> 16);
    if ((signed int) x >= 14 && (signed int) x <= 24) {
        u32 *p = (u32 *) (self + 0x7d4);
        u32 arr[3];

        c = *(u32 *) (self + 0x694);
        b = *(u32 *) (self + 0x690);
        a = *(u32 *) (self + 0x68c);
        arr[0] = a;
        arr[1] = b;
        arr[2] = c;
        func_0203f7d0(arr, arr);
        if (*p == -1) {
            *p = func_020912d4(0x31, arr, self + 0x8e, 0);
        } else {
            func_02091278((void *) (*p), (void *) (arr), (void *) (self + 0x8e), 0);
        }
    }
    if (func_02056f28(self + 0x2d0, 0x18) != 0) {
        u32 r = func_020984fc(*(u32 *) (self + 0x800));

        shorts[0] = 0xfff1;
        func_0209971c(r, shorts);
        shorts[1] = 0xfff1;
        func_0205eb8c(self + 0x5a0, &shorts[1], 0);
    }
}