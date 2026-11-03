/* outdoor_villager_bonds: 5 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226ada8 @ 0x0226ada8, 0x58 bytes, Thumb
 * func_ov068_0226ad78 @ 0x0226ad78, 0x30 bytes, Thumb
 * func_ov068_0226ad44 @ 0x0226ad44, 0x34 bytes, Thumb
 * func_ov068_0226aca8 @ 0x0226aca8, 0x9a bytes, Thumb
 * func_ov068_0226ac40 @ 0x0226ac40, 0x68 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0226ada8 {
    int pad_00;
};

struct UnkStruct_0226ac40 {
    int pad_00;
};

extern char data_021e5a2c[];
extern int func_0207cc94(struct UnkStruct_0226ada8 *, int *, int);
extern int func_0208150c(unsigned int value);
extern char *func_02137550(int *, int);
extern void func_ov068_0226ae48(void *, int, int, void *);
extern void func_0201cc6c(void *, int, int);
extern void func_0201cc48(void *);
extern int func_020644cc(int);
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_020951bc(void *argument0);
extern int func_020807a8(int, int);
extern int func_02081d20(int);
extern char data_021ed278[];
extern void *func_02072a48(struct UnkStruct_0226ac40 *, u8);
extern int func_02072dd4(void *, void *);
extern unsigned int func_0207cc54(u16, int, int);

void func_ov068_0226ada8(void *self, int unused, void *arg)
{
    struct UnkStruct_0226ada8 *g;
    int key;
    int status;
    int t;

    g = (struct UnkStruct_0226ada8 *) data_021e5a2c;
    if (g != 0) {
        if ((status = func_0207cc94(g, 0, 0)) != 0) {
            key = func_0208150c(status);
            func_02137550(&t, 4);
            t = key;
            if ((status = func_0207cc94(g, &t, 1)) != 0) {
                func_ov068_0226ae48(self, key, func_0208150c(status), arg);
            }
        }
    }
}

void func_ov068_0226ad78(int unused, void *ptr, int x, int y, unsigned char flag)
{
    func_0201cc6c((char *) ptr + 0x83c, x, y);
    if (flag) {
        func_0201cc48((char *) ptr + 0x83c);
    }
}

void func_ov068_0226ad44(int a, int b, unsigned char *arr, int d, unsigned char p5, unsigned char p6)
{
    unsigned char c = arr[func_020644cc(d)];
    if (c == 0) {
        p5 = 0;
    }
    func_ov068_0226ad78(a, (void *) b, (unsigned char) c, (unsigned char) p5, p6);
}

int func_ov068_0226aca8(int unused, int *out1, int *out2, int val1, int val2)
{
    int sp0;
    int a;
    int b;
    int c;
    int d;

    if (func_020984e8()) {
        sp0 = func_02099870(func_020984e8());
    } else {
        sp0 = 0;
    }
    if (sp0 == 0 || func_020951bc((void *) sp0) == 0) {
        goto fail;
    }

    a = -128;
    b = -128;

    c = func_020807a8(val1, sp0);
    d = func_020807a8(val2, sp0);

    if (c) {
        a = func_02081d20(c);
    }
    if (d) {
        b = func_02081d20(d);
    }

    if (a > b) {
        goto success0;
    }
    if (a != b) {
        goto success1;
    }
    if (func_020644cc(2) != 0) {
        goto success1;
    }

success0:
    *out1 = val1;
    *out2 = val2;
    return 0;

success1:
    *out1 = val2;
    *out2 = val1;
    return 1;

fail:
    *out1 = val1;
    *out2 = val2;
    return 0;
}

void *func_ov068_0226ac40(void *unused, void *arg)
{
    unsigned int i;
    u16 mask;
    int count;
    unsigned int k;

    if ((struct UnkStruct_0226ac40 *) data_021ed278 != 0) {
        mask = 0;
        count = 0;
        i = 0;
        goto test;
    body:
        if (arg != 0) {
            if (func_02072dd4(func_02072a48((struct UnkStruct_0226ac40 *) data_021ed278, (u8) i), arg) != 0) {
                goto next;
            }
        }
        mask = (u16) (mask | (1 << i));
        count++;
    next:
        i++;
    test:
        if (i < 8) {
            goto body;
        }
        k = func_0207cc54(mask, count, 8);
        if (k < 8) {
            return func_02072a48((struct UnkStruct_0226ac40 *) data_021ed278, (u8) k);
        }
    }
    return 0;
}
