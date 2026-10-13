/* func_ov134_0229b168 @ 0x0229b168, 0xb8 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov134_0229ae78(void *self, int a2, int a3, int a4);
extern int func_ov134_0229af00(void *self, int a2, int a3);
extern int func_ov134_0229ae9c(void *self, int value, u16 field);
extern void func_ov134_0229a868(void *self, int value);
extern void MI_CpuCopy8(void *dst, const void *src, int size);
extern void func_ov134_022995a0(void *self, int value);

int func_ov134_0229b168(void *self, int a2, int a3)
{
    int flag;
    int v;
    int v1;
    int v2;

    if (func_ov134_0229ae78(self, a2, a3, 0x28) == 0) {
        return 0;
    }

    v = func_ov134_0229af00(self, a2, a3);
    v1 = func_ov134_0229ae9c(self, v, *(u16 *) ((char *) self + 0x92));

    flag = 0;
    if (v1 >= -0x800 && v1 < 0x800) {
        *((u8 *) self + 0x9e) = 0;
        flag = 1;
        *(u16 *) ((char *) self + 0x96) = *(u16 *) ((char *) self + 0x92);
    } else {
        v2 = func_ov134_0229ae9c(self, v, *(u16 *) ((char *) self + 0x94));
        if (v2 >= -0x800 && v2 < 0x800) {
            flag = 1;
            *((u8 *) self + 0x9e) = 1;
            *(u16 *) ((char *) self + 0x96) = *(u16 *) ((char *) self + 0x94);
        }
    }

    if (flag) {
        func_ov134_0229a868(self, 6);
        MI_CpuCopy8((char *) self + 0xb8, (char *) self + 0xc0, 8);
        func_ov134_022995a0(self, 0x30);
        return 1;
    }
    return 0;
}
