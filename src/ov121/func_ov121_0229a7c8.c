/* func_ov121_0229a7c8 @ 0x0229a7c8, 0x178 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov121_02299bd4(void *obj, u8 mode);
extern int func_02099fe8(void);
extern void func_ov121_0229af7c(void *obj, int a, int b);
extern void func_0209a000(volatile u16 *p, int a);
extern void func_ov121_0229a524(void *obj);
extern unsigned int func_ov121_0229abac(void *obj, u8 a);
extern void func_ov121_02299b20(void *obj, u8 mode, u16 w);
extern void func_ov002_02208098(void *obj, int a);
extern void func_ov121_02299c88(void *obj, u8 a);

void func_ov121_0229a7c8(void *obj, u8 mode)
{
    volatile u16 h;
    volatile u16 h2;
    u16 v0, v1;
    unsigned int hit;
    int v;
    unsigned int t;
    u16 w;

    *(u8 *) ((char *) obj + 0xb7) = mode;
    v = func_ov121_02299bd4(obj, *(u8 *) ((char *) obj + 0xb7));
    h = v;
    switch (*(u8 *) ((char *) obj + 0xb7)) {
        case 0:
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x12a8 && v0 <= 0x12af) {
                hit = 1;
            }
            if (hit != 0) {
                v = 0xfff1;
            }
            break;
        case 1:
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x1429 && v0 <= 0x1430) {
                hit = 1;
            }
            if (hit != 0) {
                v = 0xfff1;
            }
            break;
        case 2:
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x13a0 && v0 <= 0x13a7) {
                hit = 1;
            }
            if (hit != 0) {
                v = 0xfff1;
            }
            break;
    }
    if (v != 0xfff1) {
        if (func_02099fe8() == -1) {
            func_ov121_0229af7c(obj, 4, 1);
            return;
        }
        h2 = v;
        func_0209a000(&h2, 0);
    }
    func_ov121_0229a524(obj);
    switch (*(u8 *) ((char *) obj + 0xb7)) {
        case 0:
            t = func_ov121_0229abac(obj, *(u8 *) ((char *) obj + 0xae));
            if (t < 8) {
                w = (u16) (t + 0x12a8);
            } else {
                w = 0x12a8;
            }
            *(u16 *) ((char *) obj + 0xa0) = w;
            break;
        case 1:
            t = func_ov121_0229abac(obj, *(u8 *) ((char *) obj + 0xae));
            if (t < 8) {
                w = (u16) (t + 0x1429);
            } else {
                w = 0x1429;
            }
            *(u16 *) ((char *) obj + 0xa0) = w;
            break;
        case 2:
            t = func_ov121_0229abac(obj, *(u8 *) ((char *) obj + 0xae));
            if (t < 8) {
                w = (u16) (t + 0x13a0);
            } else {
                w = 0x13a0;
            }
            *(u16 *) ((char *) obj + 0xa0) = w;
            break;
    }
    func_ov121_02299b20(obj, *(u8 *) ((char *) obj + 0xb7), *(u16 *) ((char *) obj + 0xa0));
    func_ov002_02208098(obj, 0x11);
    func_ov121_02299c88(obj, *(u8 *) ((char *) obj + 0xaf));
}
