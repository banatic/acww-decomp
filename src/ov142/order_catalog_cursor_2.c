/* order_catalog_cursor_2: 2 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_0229a298 @ 0x0229a298, 0x128 bytes, Thumb
 * func_ov142_0229a1fc @ 0x0229a1fc, 0x9c bytes, Thumb
 */

#include "types.h"

extern void func_ov142_0229b10c(void *self);
extern int func_ov142_02299668(void *self, int a);
extern void func_ov142_0229b138(void *self);
extern void func_ov002_0220a574(void *p);
extern void func_ov002_0220a4bc(void *receiver);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov142_0229b350(void *self);
extern void func_ov142_0229b2f8(void *self);
extern void func_ov142_02299928(void *self);
extern void func_ov142_02299918(void *self);
extern void func_0200467c(int a);
extern void func_ov142_0229ab68(void *self, u8 a);
extern int func_ov142_0229a0f8(void *self, u8 a, s16 b);
extern int func_ov002_0220a784(void *, int);
extern int func_ov142_0229a6d8(void *);

int func_ov142_0229a298(char *self, int param)
{
    switch (param) {
        case 0x13:
            func_ov142_0229b10c(self);
            return 1;

        case 0x12:
            if (func_ov142_02299668(self, 0x20) != 0) {
                func_ov142_0229b138(self);
                return 1;
            }
            return 0;

        case 0x14:
            func_ov002_0220a574(self + 0x14c);
            func_ov002_0220a4bc((void *) ((char *) self + 0x14c));
            func_ov002_02208098((void *) (self), 5);
            return 1;

        case 0x17:
            func_ov142_0229b350(self);
            return 1;

        case 0x18:
            func_ov142_0229b2f8(self);
            return 1;

        case 0x15:
            if (func_ov142_02299668(self, 0x400) != 0) {
                return 0;
            }
            func_ov142_02299928(self);
            func_ov002_02208098((void *) (self), 7);
            return 1;

        case 0x16:
            if (func_ov142_02299668(self, 0x800) != 0) {
                return 0;
            }
            func_ov142_02299918(self);
            func_ov002_02208098((void *) (self), 7);
            return 1;

        default:
            if ((u32) param <= 8) {
                if (*(u8 *) (self + 0xbd) != param) {
                    func_0200467c(0xc);
                    func_ov142_0229ab68(self, (u8) param);
                }
                return 0;
            }
            if ((u32) param >= 9 && (u32) param <= 0x11) {
                if (*(u8 *) (self + 0xc2) != 0) {
                    return 0;
                }
                if (func_ov142_0229a0f8(self, *(u8 *) (self + 0xbc), (s16) (*(s16 *) (self + 0xb4) + (param - 9))) != 0) {
                    func_0200467c(0x29);
                }
            }
            return 0;
    }
}

int func_ov142_0229a1fc(u8 *self, int arg1, int arg2)
{
    if (func_ov002_0220a784(self + 0x194, 6)) {
        return 0x13;
    }

    if (func_ov142_02299668(self, 0x20)) {
        if (arg1 >= 0xc4 && arg1 < 0xe8 && arg2 >= 0x4d && arg2 < 0x71) {
            return 0x12;
        }
    }

    if (arg1 <= 0x1b) {
        if (arg2 >= 0x18 && arg2 < 0xa8) {
            return (u8) ((arg2 - 0x18) >> 4);
        }
        return 0x19;
    } else {
        if (arg1 >= 0x38 && arg1 <= 0x9c) {
            if (arg2 >= 0x20 && arg2 < 0xa0) {
                int field = (*(u32 *) (self + 0xa0)) & 0xf;
                int v = (arg2 - (0x20 - field)) >> 4;
                if (v >= func_ov142_0229a6d8(self)) {
                    return 0x19;
                } else {
                    return (u8) (v + 9);
                }
            } else {
                return 0x19;
            }
        } else {
            return 0x19;
        }
    }
}
