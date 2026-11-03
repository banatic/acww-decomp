/* order_catalog_cursor_6: 8 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_0229b700 @ 0x0229b700, 0x104 bytes, Thumb
 * func_ov142_0229b6cc @ 0x0229b6cc, 0x34 bytes, Thumb
 * func_ov142_0229b698 @ 0x0229b698, 0x34 bytes, Thumb
 * func_ov142_0229b670 @ 0x0229b670, 0x28 bytes, Thumb
 * func_ov142_0229b5e8 @ 0x0229b5e8, 0x88 bytes, Thumb
 * func_ov142_0229b59c @ 0x0229b59c, 0x4c bytes, Thumb
 * func_ov142_0229b55c @ 0x0229b55c, 0x3e bytes, Thumb
 * func_ov142_0229b528 @ 0x0229b528, 0x34 bytes, Thumb
 */

#include "types.h"

extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern int func_ov002_02208054(void *self, int a);
extern void func_ov142_0229b23c(void *self);
extern int func_ov142_0229a1fc(void *self, int a, int b);
extern int func_ov142_0229a298(void *self, int a);
extern int func_ov142_02299668(void *self, int a);
extern int func_ov142_02299c1c(void *self, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov142_02299928(void *self);
extern void func_ov142_02299918(void *self);
extern void func_ov002_0220a574(void *p);
extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov142_02299ba4(int arg0, unsigned char arg1, int arg2);
extern void func_ov142_02299b94(int param);
extern void func_ov142_02299830(int a);
extern void func_ov142_02299908(int a);
extern int func_ov002_02208014(void *receiver);
extern void *func_ov002_02208008(void *p);
extern int func_ov142_02299c64(void *p, void *a);
extern void func_ov142_0229af4c(void *p);
extern void func_ov142_0229b278(void *p);
extern void func_ov142_0229aee8(void *p);
extern void func_ov142_0229af94(void *p);
extern void func_ov142_0229b10c(void *p);
extern void func_ov142_0229b138(void *p);
extern unsigned short data_021fbe40[2];
void func_ov142_02299b08(int);
int func_ov142_0229b04c(int);
int func_ov142_0229afb0(int);
void func_ov002_0220a0b4(int, int, int);
extern int func_ov142_02299ae0(void *);
extern void func_ov142_0229aec4(void *);

void func_ov142_0229b700(void *self)
{
    int cond;
    int r6;
    int r4;
    int r1;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov142_0229b23c(self);
        return;
    }

    cond = ((*(u8 *) &data_021fbdd8) != 0 && data_021fbddc != 0);
    if (cond == 0) {
        return;
    }

    r6 = data_021f6c58;
    r4 = (*(u8 *) &data_021f6c54);

    r1 = func_ov142_0229a1fc(self, r6, r4);
    if (r1 != 0x19) {
        func_ov142_0229a298(self, r1);
        return;
    }

    if (func_ov142_02299668(self, 0x100) != 0) {
        return;
    }

    if (func_ov142_02299c1c(self, r6, r4) != 0) {
        func_ov002_02208098((void *) (self), 1);
        return;
    }

    if (r6 < 0xb8 || r6 >= 0xc8) {
        return;
    }

    if (func_ov142_02299668(self, 0x400) == 0) {
        if (r4 >= 0x19 && r4 < 0x29) {
            func_ov142_02299928(self);
            func_ov002_02208098((void *) (self), 3);
            return;
        }
    }

    if (func_ov142_02299668(self, 0x800) == 0) {
        if (r4 >= 0x95 && r4 < 0xa5) {
            func_ov142_02299918(self);
            func_ov002_02208098((void *) (self), 3);
            return;
        }
    }

    if (r4 >= 0x2c && r4 <= 0x86) {
        func_ov002_0220a574((char *) self + 0x14c);
        func_ov002_02208098((void *) (self), 2);
    }
}

void func_ov142_0229b6cc(int arg0)
{
    if (data_021fbdd8) {
        func_ov142_02299ba4(arg0, data_021f6c54, 0);
    } else {
        func_ov142_02299b94((int) ((void *) arg0));
        func_ov002_02208098((void *) (arg0), 0);
    }
}

void func_ov142_0229b698(int param)
{
    if (data_021fbdd8) {
        func_ov142_02299ba4(param, data_021f6c54, 1);
    } else {
        func_ov142_02299b94(param);
        func_ov002_02208098((void *) (param), 0);
    }
}

void func_ov142_0229b670(int p)
{
    unsigned char f = data_021fbdd8;
    if (f) {
        func_ov142_02299830(p);
        return;
    }
    func_ov142_02299908(p);
    func_ov002_02208098((void *) (p), 0);
}

void func_ov142_0229b5e8(void *p)
{
    if (func_ov002_02208014(p)) {
        func_ov142_0229b278(p);
        return;
    }

    if (func_ov142_02299c64(p, func_ov002_02208008(p))) {
        func_ov142_0229af4c(p);
        return;
    }

    {
        unsigned short flags = data_021fbe40[1];

        if ((flags & 1) != 0) {
            func_ov142_0229aee8(p);
            return;
        }

        if ((flags & 2) != 0) {
            func_ov142_0229af94(p);
            func_ov142_0229b10c(p);
            return;
        }

        if ((flags & 8) != 0) {
            if (func_ov142_02299668(p, 0x20)) {
                func_ov142_0229af94(p);
                func_ov142_0229b138(p);
            }
        }
    }
}

void func_ov142_0229b59c(int param)
{
    if ((*(unsigned short *) data_021fbe40) & 1) {
        int ret1;
        int ret2;
        func_ov142_02299b08(param);
        ret1 = func_ov142_0229b04c(param);
        ret2 = func_ov142_0229afb0(param);
        func_ov002_0220a0b4(param + 0xE8, ret1, ret2);
    } else {
        func_ov142_02299b94(param);
        func_ov002_02208098((void *) (param), 6);
    }
}

void func_ov142_0229b55c(void *arg)
{
    int a, b;
    if (func_ov142_02299ae0(arg) != 0) {
        func_ov002_02208098((void *) (arg), 4);
        func_ov142_0229aec4(arg);
    }
    a = func_ov142_0229b04c((int) arg);
    b = func_ov142_0229afb0((int) arg);
    func_ov002_0220a0b4((int) ((char *) arg + 0xe8), a, b);
}

void func_ov142_0229b528(unsigned int arg)
{
    if ((*(unsigned short *) data_021fbe40) & 1) {
        func_ov142_02299830(arg);
    } else {
        func_ov142_02299908(arg);
        func_ov002_02208098((void *) (arg), 4);
        func_ov142_0229aec4((void *) arg);
    }
}
