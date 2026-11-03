/* donation_list_states_2: 10 functions, module ov145
 * mwccarm 1.2/base -O4,s
 * func_ov145_0229a7b0 @ 0x0229a7b0, 0x28 bytes, Thumb
 * func_ov145_0229a778 @ 0x0229a778, 0x38 bytes, Thumb
 * func_ov145_0229a6c8 @ 0x0229a6c8, 0xb0 bytes, Thumb
 * func_ov145_0229a678 @ 0x0229a678, 0x50 bytes, Thumb
 * func_ov145_0229a5b0 @ 0x0229a5b0, 0xc8 bytes, Thumb
 * func_ov145_0229a57c @ 0x0229a57c, 0x34 bytes, Thumb
 * func_ov145_0229a548 @ 0x0229a548, 0x34 bytes, Thumb
 * func_ov145_0229a4e4 @ 0x0229a4e4, 0x64 bytes, Thumb
 * func_ov145_0229a498 @ 0x0229a498, 0x4c bytes, Thumb
 * func_ov145_0229a458 @ 0x0229a458, 0x3e bytes, Thumb
 */

#include "types.h"

struct Global021fbe40 {
    unsigned char pad_00[2];
    unsigned short flags;
};

extern void func_ov145_0229967c(void *);
extern void func_ov145_02299a34(void *);
extern void func_ov145_02299bd0(void *);
extern void func_ov002_0220a544(void *);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern unsigned char *data_021fbe94;
extern const unsigned char data_ov145_0229af10[];
extern const unsigned char data_ov145_0229af28[];
extern const unsigned char data_ov145_0229af40[];
extern const unsigned char data_ov145_0229af58[];
extern const unsigned char data_ov145_0229af70[];
extern const unsigned char data_ov145_0229af88[];
extern int func_02002c6c(const unsigned char *src, unsigned char *dst, int a, int b, int c, int d);
extern int func_02002d14(const unsigned char *src, unsigned char *dst, int a, int b, int c, int d);
extern int func_02064af4(const unsigned char *src, unsigned char *dst, int size);
extern int func_02002b40(unsigned char *dst, int val, int size, int flag);
extern void func_ov002_0220af94(void *receiver);
extern char data_ov145_0229aee0[];
extern char data_ov145_0229aef8[];
extern int func_ov002_02208054(void *self, int a);
extern void func_ov145_0229a330(void *self);
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov145_0229a2e0(void *self);
extern int func_ov145_022998c4(void *self, int a, int b);
extern int func_ov145_022998f0(void *self, int n);
extern int func_ov145_0229a298(void *self, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a574(void *p);
extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c54;
extern void func_ov145_0229a220(int a, int b, int c);
extern int func_ov145_0229a210(int unused0);
extern int func_ov002_02208014(void *receiver);
extern void *func_ov002_02208008(void *arg);
extern int func_ov145_022997d0(void *arg, void *arg2);
extern void func_ov145_02299e90(void *arg);
extern void func_ov145_0229a358(void *arg);
extern void func_ov145_02299e2c(void *arg);
extern void func_ov145_02299ed0(void *arg);
extern struct Global021fbe40 data_021fbe40;
extern void func_ov145_0229a184(char *param);
extern int func_ov145_02299f30(char *param);
extern int func_ov145_02299eec(char *param);
extern void func_ov002_0220a0b4(char *ptr, int a, int b);
extern int func_ov145_0229a15c(void *p);
extern void func_ov145_02299e08(void *p);

void func_ov145_0229a7b0(void *self)
{
    func_ov145_0229967c(self);
    func_ov145_02299a34(self);
    func_ov145_02299bd0(self);
    func_ov002_0220a544((char *) self + 0x12c);
}

void func_ov145_0229a778(void)
{
    func_02001c08(0);
    func_020029e8(6, 1);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
}

void func_ov145_0229a6c8(unsigned char *self)
{
    unsigned char *p = data_021fbe94;

    func_02002c6c(data_ov145_0229af10, p, 6, 0x11, 0x11, 0x63);
    func_02002c6c(data_ov145_0229af28, p, 6, 0x26e, 0x26e, 0x27d);
    func_02002d14(data_ov145_0229af40, p, 6, 1, 1, 7);

    func_02064af4(data_ov145_0229af58, self + 0x24c6, 0x20);
    func_02064af4(data_ov145_0229af70, self + 0xcc6, 0x800);
    func_02064af4(data_ov145_0229af88, self + 0x1cc6, 0x800);

    func_02002b40(self + 0x1cc6, 6, 0x800, 0);
}

void func_ov145_0229a678(char *param)
{
    int value;
    func_ov002_0220af94(param + 0x174);
    value = (*(int *) &data_021fbe94);
    func_02002c6c((const unsigned char *) data_ov145_0229aee0, (unsigned char *) value, 8, 0xc0, 0xc0, 0x13f);
    func_02002d14((const unsigned char *) data_ov145_0229aef8, (unsigned char *) value, 8, 4, 4, 9);
}

void func_ov145_0229a5b0(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov145_0229a330(self);
        return;
    }

    ok = ((*(u8 *) &data_021fbdd8) != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    if (func_ov002_0220a784(self + 0x174, 6) != 0) {
        func_ov145_0229a2e0(self);
        return;
    }

    a = data_021f6c58;
    b = (*(u8 *) &data_021f6c54);
    n = func_ov145_022998c4(self, a, b);
    if (n != 6) {
        func_ov145_022998f0(self, n);
        return;
    }

    if (*(int *) (self + 0xa4) <= 0) {
        return;
    }
    if (func_ov145_0229a298(self, a, b) != 0) {
        func_ov002_02208098((void *) (self), 1);
        return;
    }
    if (a < 0xe4) {
        return;
    }
    if (a > 0xec) {
        return;
    }
    if (b < 0x15) {
        return;
    }
    if (b > 0x8d) {
        return;
    }
    func_ov002_0220a574(self + 0x12c);
    func_ov002_02208098((void *) (self), 2);
}

void func_ov145_0229a57c(int param)
{
    if (data_021fbdd8 != 0) {
        func_ov145_0229a220(param, data_021f6c54, 0);
    } else {
        func_ov145_0229a210(param);
        func_ov002_02208098((void *) (param), 0);
    }
}

void func_ov145_0229a548(void *arg)
{
    if (data_021fbdd8 != 0) {
        func_ov145_0229a220((int) arg, (unsigned char) data_021f6c54, 1);
    } else {
        func_ov145_0229a210((int) arg);
        func_ov002_02208098((void *) (arg), 0);
    }
}

void func_ov145_0229a4e4(void *arg)
{
    unsigned short flags;

    if (func_ov002_02208014(arg)) {
        func_ov145_0229a358(arg);
        return;
    }
    if (func_ov145_022997d0(arg, func_ov002_02208008(arg))) {
        func_ov145_02299e90(arg);
        return;
    }
    flags = data_021fbe40.flags;
    if (flags & 1) {
        func_ov145_02299e2c(arg);
        return;
    }
    if (flags & 2) {
        func_ov145_02299ed0(arg);
        func_ov145_0229a2e0(arg);
    }
}

void func_ov145_0229a498(char *param)
{
    if ((*(unsigned short *) &data_021fbe40) & 1) {
        int res1, res2;
        func_ov145_0229a184(param);
        res1 = func_ov145_02299f30(param);
        res2 = func_ov145_02299eec(param);
        func_ov002_0220a0b4(param + 0xc8, res1, res2);
    } else {
        func_ov145_0229a210((int) param);
        func_ov002_02208098((void *) (param), 5);
    }
}

void func_ov145_0229a458(char *param)
{
    if (func_ov145_0229a15c(param)) {
        func_ov002_02208098((void *) (param), 3);
        func_ov145_02299e08(param);
    }
    {
        int v1 = func_ov145_02299f30((char *) param);
        int v2 = func_ov145_02299eec((char *) param);
        param += 0xc8;
        func_ov002_0220a0b4((char *) param, v1, v2);
    }
}
