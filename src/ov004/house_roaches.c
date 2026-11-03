/* house_roaches: 9 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223ea60 @ 0x0223ea60, 0x18 bytes, Thumb
 * func_ov004_0223ea44 @ 0x0223ea44, 0x1c bytes, Thumb
 * func_ov004_0223ea24 @ 0x0223ea24, 0x20 bytes, Thumb
 * func_ov004_0223ea04 @ 0x0223ea04, 0x20 bytes, Thumb
 * func_ov004_0223e9dc @ 0x0223e9dc, 0x28 bytes, Thumb
 * func_ov004_0223e998 @ 0x0223e998, 0x44 bytes, Thumb
 * func_ov004_0223e878 @ 0x0223e878, 0x120 bytes, Thumb
 * func_ov004_0223e834 @ 0x0223e834, 0x44 bytes, Thumb
 * func_ov004_0223e7b4 @ 0x0223e7b4, 0x80 bytes, Thumb
 */

#include "types.h"

extern int func_020edf70(int);
extern void *func_ov004_0223e520(char *argument0);
extern void *func_020ee660(void *);
extern void func_020ee62c(void *ptr);
extern void *const data_ov004_022561dc[];
extern void *const data_020da13c[];
extern void func_020edf54(void *p);
extern int func_020b67d4(void);
extern int func_02073d90(void *);
extern void func_02060d64(void *, int);
extern void *data_020ccf94;
extern char data_021ebcd4;
extern u8 data_ov004_02259a0c;
extern void *data_ov004_02259a10;
extern void func_ov004_0223e3d4(void *, int);
extern void func_020ee470(void *);
extern int func_ov004_0223e3e0(void *);
extern char *func_020961a8(int);
extern int func_020ea990(void *, void *);
extern char *data_ov004_02259a18[3];
extern u8 data_ov004_02259a08;
extern int func_ov004_0223e5f0(void *receiver);
extern int func_ov004_0223e618(void *);
extern int func_02003348(int, int, void *, void *, void *);

void *func_ov004_0223ea24(void *self);

void func_ov004_0223ea60(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_ov004_0223ea24((void *) result);
}

void func_ov004_0223ea44(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x268)))) {
        func_ov004_0223e520((char *) conditionInput0);
    }
}

void *func_ov004_0223ea24(void *self)
{
    func_020ee660(self);
    *(void **) self = (void *) ((int *) data_020da13c);
    *(void **) self = (void *) ((int *) data_ov004_022561dc);
    return self;
}

void *func_ov004_0223ea04(void *p)
{
    volatile int *vp;
    vp = (volatile int *) p;
    *vp = (int) ((int *) data_ov004_022561dc);
    *vp = (int) ((int *) data_020da13c);
    func_020ee62c(p);
    return p;
}

void *func_ov004_0223e9dc(const void **self)
{
    *self = data_ov004_022561dc;
    *self = data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

int func_ov004_0223e998(void)
{
    if (func_020b67d4() == 0 || func_02073d90(data_020ccf94) != 0) {
        return 1;
    }
    func_02060d64(&data_021ebcd4, data_ov004_02259a0c);
    data_ov004_02259a10 = 0;
    return 1;
}

int func_ov004_0223e878(void *self)
{
    u8 mask;
    signed char sel;
    int i;

    if (func_020b67d4() == 0 || func_02073d90(data_020ccf94) != 0) {
        return 1;
    }

    mask = 0;
    sel = 0;
    for (i = 0; i < 3; i++) {
        char **slot = &data_ov004_02259a18[i];
        char *o = *slot;
        if (o == 0) {
            continue;
        }
        if (*(int *) (o + 8) == 0xffff) {
            *(int *) (o + 8) = 0;
            func_ov004_0223e3d4(*slot, 0);
            func_020ee470(*slot);
            *slot = 0;
            if (data_ov004_02259a08 != 0) {
                data_ov004_02259a08--;
                data_ov004_02259a0c--;
            }
        } else if (func_ov004_0223e3e0(o) == 1) {
            mask |= 1 << i;
            sel--;
        } else if (func_ov004_0223e3e0(*slot) == 2) {
            mask = 0xff;
        }
    }
    if (mask != 0xff && mask != 0) {
        char *o = func_020961a8(4);
        int best = 0x0fffffff;
        if (o != 0) {
            int j;
            char *p;
            p = o + 0x5c;
            for (j = 0; j < 3; j++) {
                if (data_ov004_02259a18[j] == 0) {
                    continue;
                }
                if (((mask >> j) & 1) == 0) {
                    continue;
                }
                if (sel == -1) {
                    sel = j;
                    break;
                } else {
                    int d = func_020ea990(p, data_ov004_02259a18[j] + 0x5c);
                    if (best > d) {
                        best = d;
                        sel = j;
                    }
                }
            }
        }
        func_ov004_0223e3d4(data_ov004_02259a18[sel], 2);
    }
    return 1;
}

int func_ov004_0223e834(void *self)
{
    if (func_020b67d4() == 0 || func_02073d90(data_020ccf94) != 0) {
        return 1;
    }
    data_ov004_02259a10 = self;
    if (func_ov004_0223e5f0(self) == 0) {
        return 1;
    }
    func_ov004_0223e618(self);
    return 1;
}

int func_ov004_0223e7b4(void *a, void *b)
{
    int ok = 0;
    int i;
    int *p;
    if (func_02073d90(data_020ccf94) != 0) {
        return ok;
    }
    if (data_ov004_02259a08 < 3 && (int) data_ov004_02259a0c - (int) data_ov004_02259a08 > 0) {
        i = ok;
        p = ((int *) data_ov004_02259a18);
        for (; i < 3; i++) {
            if (p[i] == 0) {
                p[i] = func_02003348(0xc0, 0, a, b, data_ov004_02259a10);
                data_ov004_02259a08 = (u8) (data_ov004_02259a08 + 1);
                ok = 1;
                break;
            }
        }
    }
    return ok;
}
