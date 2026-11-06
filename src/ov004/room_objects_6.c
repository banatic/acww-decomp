/* room_objects_6: 27 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223cf10 @ 0x0223cf10, 0x8 bytes, Thumb
 * func_ov004_0223cf00 @ 0x0223cf00, 0x10 bytes, Thumb
 * func_ov004_0223cefc @ 0x0223cefc, 0x2 bytes, Thumb
 * func_ov004_0223cef4 @ 0x0223cef4, 0x6 bytes, Thumb
 * func_ov004_0223cec4 @ 0x0223cec4, 0x30 bytes, Thumb
 * func_ov004_0223cea8 @ 0x0223cea8, 0x1a bytes, Thumb
 * func_ov004_0223ce98 @ 0x0223ce98, 0x10 bytes, Thumb
 * func_ov004_0223ce8c @ 0x0223ce8c, 0xc bytes, Thumb
 * func_ov004_0223ce84 @ 0x0223ce84, 0x8 bytes, Thumb
 * func_ov004_0223ce74 @ 0x0223ce74, 0x10 bytes, Thumb
 * func_ov004_0223ce70 @ 0x0223ce70, 0x2 bytes, Thumb
 * func_ov004_0223ce60 @ 0x0223ce60, 0x10 bytes, Thumb
 * func_ov004_0223ce18 @ 0x0223ce18, 0x46 bytes, Thumb
 * func_ov004_0223cde8 @ 0x0223cde8, 0x2e bytes, Thumb
 * func_ov004_0223cdc0 @ 0x0223cdc0, 0x26 bytes, Thumb
 * func_ov004_0223cda4 @ 0x0223cda4, 0x1c bytes, Thumb
 * func_ov004_0223cd78 @ 0x0223cd78, 0x2a bytes, Thumb
 * func_ov004_0223cd58 @ 0x0223cd58, 0x20 bytes, Thumb
 * func_ov004_0223cd50 @ 0x0223cd50, 0x8 bytes, Thumb
 * func_ov004_0223cd40 @ 0x0223cd40, 0x10 bytes, Thumb
 * func_ov004_0223cd3c @ 0x0223cd3c, 0x2 bytes, Thumb
 * func_ov004_0223cd04 @ 0x0223cd04, 0x36 bytes, Thumb
 * func_ov004_0223ccc4 @ 0x0223ccc4, 0x40 bytes, Thumb
 * func_ov004_0223cc80 @ 0x0223cc80, 0x42 bytes, Thumb
 * func_ov004_0223cc5c @ 0x0223cc5c, 0x24 bytes, Thumb
 * func_ov004_0223cc10 @ 0x0223cc10, 0x4a bytes, Thumb
 * func_ov004_0223cbe8 @ 0x0223cbe8, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned long unk_00;
} UnkStruct_0223cef4;

extern char data_ov004_022595c4[];
extern void *func_020ea1bc(int, void *);
extern void *data_021fbe94;
extern void func_020e9fc8(void *parameter0);
extern int func_020e9948(void *p, int k);
extern void func_020e993c(void *heap, void *block);
extern char data_ov004_02259714[];
extern int func_ov004_0223c130(void);
extern char data_ov004_02259804[];
extern void func_0204f818(int *, int *, int);

void func_ov004_0223cef4(UnkStruct_0223cef4 *p);
void func_ov004_0223ce60(char *self);
void func_ov004_0223cd04(u8 *self);

void *func_ov004_0223cf10(void)
{
    return data_ov004_022595c4;
}

int func_ov004_0223cf00(int arg)
{
    func_ov004_0223cef4((UnkStruct_0223cef4 *) arg);
    return arg;
}

void func_ov004_0223cefc(void *object) {}

void func_ov004_0223cef4(UnkStruct_0223cef4 *p)
{
    p->unk_00 = 0;
}

int func_ov004_0223cec4(char *self, int n)
{
    if (*(void **) self == 0) {
        *(void **) self = func_020ea1bc(0x93e * n, data_021fbe94);
        return 1;
    }
    return 0;
}

void func_ov004_0223cea8(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self) != 0x0) {
        func_020e9fc8((void *) (*(int *) ((char *) (((unsigned int) (self) + (0x0))) + 0)));
    }
    func_ov004_0223cef4((UnkStruct_0223cef4 *) self);
}

int func_ov004_0223ce98(void **self, int actor)
{
    return func_020e9948(*self, 0x8da);
}

void func_ov004_0223ce8c(void **p, void *block)
{
    func_020e993c(*p, block);
}

void *func_ov004_0223ce84(void)
{
    return data_ov004_02259714;
}

int func_ov004_0223ce74(int arg)
{
    func_ov004_0223ce60((char *) arg);
    return arg;
}

void func_ov004_0223ce70(void *object) {}

void func_ov004_0223ce60(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    for (i = 0; i < 0x1c; i++) {
        *(void **) (self + (i << 2)) = 0x0;
    }
}

int func_ov004_0223ce18(int *arr, int val)
{
    unsigned int i = 0;
    while (i < (unsigned int) func_ov004_0223c130()) {
        int t = arr[i];
        if (t == val) {
            return 1;
        }
        i++;
    }
    i = 0;
    while (i < (unsigned int) func_ov004_0223c130()) {
        int t = arr[i];
        if (t == 0) {
            arr[i] = val;
            return 1;
        }
        i++;
    }
    return 0;
}

int func_ov004_0223cde8(int *arr, int val)
{
    unsigned int i = 0;
    while (i < (unsigned int) func_ov004_0223c130()) {
        int t = arr[i];
        if (t == val) {
            arr[i] = 0;
            return 1;
        }
        i++;
    }
    return 0;
}

int func_ov004_0223cdc0(int *a)
{
    int n = 0;
    unsigned int i;
    for (i = 0; i < (unsigned int) func_ov004_0223c130(); i++) {
        if (a[i] != 0) {
            n++;
        }
    }
    return n;
}

int func_ov004_0223cda4(char *self)
{
    int a = func_ov004_0223c130();
    return a - func_ov004_0223cdc0((int *) self);
}

int func_ov004_0223cd78(int *a, int v)
{
    unsigned int i;
    for (i = 0; i < (unsigned int) func_ov004_0223c130(); i++) {
        int t = a[i];
        if (t == v) {
            return i;
        }
    }
    return -1;
}

int func_ov004_0223cd58(int *self, unsigned int i)
{
    int r;
    if (i < (unsigned int) func_ov004_0223c130()) {
        r = self[i];
    } else {
        r = 0;
    }
    return r;
}

void *func_ov004_0223cd50(void)
{
    return data_ov004_02259804;
}

int func_ov004_0223cd40(int arg)
{
    func_ov004_0223cd04((u8 *) arg);
    return arg;
}

void func_ov004_0223cd3c(void *object) {}

void func_ov004_0223cd04(u8 *self)
{
    unsigned int k, j, i;
    for (k = 0; k < 2; k++) {
        for (j = 0; j < 0x10; j++) {
            for (i = 0; i < 0x10; i++) {
                *(self + (k << 8) + (j << 4) + i) = 0xff;
            }
        }
    }
}

int func_ov004_0223ccc4(u8 *base, int arg, int col, int row, u8 page)
{
    u8 *p;
    int id;

    p = base + ((page & 1) << 8) + ((row & 0xf) << 4) + (col & 0xf);
    id = func_ov004_0223cd78((int *) ((int) func_ov004_0223ce84()), arg);
    if (id != -1) {
        *p = (u8) id;
        return 1;
    }
    return 0;
}

int func_ov004_0223cc80(char *base, int a1, int a2, int a3, u8 a4)
{
    u8 *p = (u8 *) (base + ((a4 & 1) << 8) + ((a3 & 0xf) << 4) + (a2 & 0xf));
    if (func_ov004_0223cd78((int *) (func_ov004_0223ce84()), a1) != -1) {
        *p = 0xff;
        return 1;
    }
    return 0;
}

int func_ov004_0223cc5c(char *self, int a1, int a2, int a3)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + ((a3 & 0x1) << 8) + ((a2 & 0xf) << 4) + (a1 & 0xf)) == 0xff) {
        return -0x1;
    }
    return *(u8 *) (self + ((a3 & 0x1) << 8) + ((a2 & 0xf) << 4) + (a1 & 0xf));
}

void *func_ov004_0223cc10(char *base, int x, int y, int layer)
{
    unsigned char *p = (unsigned char *) base + ((layer & 1) << 8) + ((y & 0xf) << 4) + (x & 0xf);
    unsigned char id = *p;
    if (id != 0xff && id < (unsigned) func_ov004_0223c130() &&
        (void *) func_ov004_0223cd58((int *) (func_ov004_0223ce84()), id) != 0) {
        return (void *) func_ov004_0223cd58((int *) (func_ov004_0223ce84()), *p);
    }
    return 0;
}

void *func_ov004_0223cbe8(int a, int b, int c)
{
    int sp0;
    int sp4;

    func_0204f818(&sp0, &sp4, b);
    return func_ov004_0223cc10((char *) a, sp0, sp4, c);
}
