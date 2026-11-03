/* villager_house_items: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207f708 @ 0x0207f708, 0x64 bytes, Thumb
 * func_0207f6dc @ 0x0207f6dc, 0x2c bytes, Thumb
 * func_0207f5e4 @ 0x0207f5e4, 0xf8 bytes, Thumb
 * func_0207f5c8 @ 0x0207f5c8, 0x1c bytes, Thumb
 * func_0207f590 @ 0x0207f590, 0x38 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x078c];
    unsigned short arr[10];
} UnkStruct_0207f6dc;

typedef struct Triple {
    int unk_00[3];
} Triple;

extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern Triple data_020e18c0;
extern int func_0208150c(void *self);
extern int func_02003704(int t);
extern int func_020644cc(int n);
extern unsigned int func_0207f1c8(void *self);
extern int func_0209b5ec(void *);
extern int func_0209c330(unsigned char *);
extern int func_0209c2c0(int y);
extern int func_0207fe94(void *self, int *a, int *b, int i, int s1, int s2);
extern int func_0207fbb4(void *self, int s1, int a, int b);
extern int func_0207ffa0(void *self, int v);
extern int func_0207fb98(u16 *p);
extern int func_02053bc0(int item);
extern unsigned short data_020cd42c[];

int func_0207f708(unsigned char *base, unsigned short *other)
{
    unsigned short *p;
    int flag1, flag2, count, i;
    int tmp, result;

    p = (unsigned short *) (base + 0x78c);
    count = 0;
    i = count;
    flag1 = count;
    flag2 = count;
    while (i < 10) {
        if (func_0204bcdc(p)) {
            tmp = func_0204bc64(p);
            result = (tmp == func_0204bc64(other)) ? 1 : flag1;
        } else {
            result = (*p == *other) ? 1 : flag2;
        }
        if (result != 0) {
            count++;
        }
        p++;
        i++;
    }
    return count;
}

int func_0207f6dc(UnkStruct_0207f6dc *base)
{
    unsigned short *p;
    int i;
    int count;

    p = base->arr;
    count = 0;
    for (i = 0; i < 10; i++) {
        if (*p != 0xfff1) {
            count++;
        }
        p++;
    }
    return count;
}

void func_0207f5e4(char *self)
{
    int y;
    int s1;
    int s2;
    Triple arr;
    int count;
    int a;
    int b;
    int i;
    int sel;
    int t;
    u16 *p;
    u16 *base;

    if (func_02003704(func_0208150c(self)) == 0) {
        return;
    }
    if (func_0207f6dc((UnkStruct_0207f6dc *) self) < 7) {
        return;
    }
    if (func_020644cc(2) != 0) {
        return;
    }

    y = func_0209b5ec((void *) func_0207f1c8(self));
    s1 = func_0209c330((unsigned char *) y);
    s2 = func_0209c2c0(y);

    arr = data_020e18c0;

    count = 0;
    a = 0;
    b = 0;
    for (i = 0; i < 3; i++) {
        if (func_0207fe94(self, &a, &b, i, s1, s2) != 0) {
            arr.unk_00[i] = func_0207fbb4(self, s1, a, b);
            if (func_0207ffa0(self, arr.unk_00[i]) != 0) {
                count++;
            }
        }
    }

    if (count <= 0) {
        return;
    }
    sel = func_020644cc(count);
    if (sel >= 3) {
        return;
    }

    for (i = 0; i < 3; i++) {
        t = arr.unk_00[i];
        if (func_0207ffa0(self, t) != 0) {
            if (sel == 0) {
                base = (u16 *) (self + 0x78c);
                p = &base[t];
                if (base[t] != 0xfff1) {
                    func_0207fb98(p);
                }
                *p = 0xfff1;
                return;
            }
            sel--;
        }
    }
}

void func_0207f5c8(unsigned short *p)
{
    unsigned short *q = (unsigned short *) ((unsigned char *) p + 0x78e);
    int i;
    for (i = 0; i < 2; i++) {
        *q++ = 0xfff1;
    }
}

void func_0207f590(unsigned short *r5, int r1, int r2)
{
    unsigned short *p = r5;
    int r4 = r2;
    int r0;

    *p = 0xfff1;
    r0 = func_0204bcdc((unsigned short *) ((void *) r4));
    if (r0 != 0) {
        r0 = func_02053bc0(r4);
        if (r0 < 3) {
            *p = data_020cd42c[r0];
        }
    }
}
