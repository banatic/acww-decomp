/* room_surface: 20 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022329e0 @ 0x022329e0, 0x40 bytes, Thumb
 * func_ov004_022329c8 @ 0x022329c8, 0x18 bytes, Thumb
 * func_ov004_022329c4 @ 0x022329c4, 0x4 bytes, Thumb
 * func_ov004_022329c0 @ 0x022329c0, 0x2 bytes, Thumb
 * func_ov004_022329b4 @ 0x022329b4, 0xc bytes, Thumb
 * func_ov004_02232980 @ 0x02232980, 0x34 bytes, Thumb
 * func_ov004_02232968 @ 0x02232968, 0x16 bytes, Thumb
 * func_ov004_02232934 @ 0x02232934, 0x34 bytes, Thumb
 * func_ov004_022327a0 @ 0x022327a0, 0x194 bytes, Thumb
 * func_ov004_02232794 @ 0x02232794, 0xc bytes, Thumb
 * func_ov004_02232754 @ 0x02232754, 0x40 bytes, Thumb
 * func_ov004_0223273c @ 0x0223273c, 0x18 bytes, Thumb
 * func_ov004_02232738 @ 0x02232738, 0x4 bytes, Thumb
 * func_ov004_02232734 @ 0x02232734, 0x2 bytes, Thumb
 * func_ov004_02232728 @ 0x02232728, 0xc bytes, Thumb
 * func_ov004_022326f4 @ 0x022326f4, 0x34 bytes, Thumb
 * func_ov004_022326dc @ 0x022326dc, 0x16 bytes, Thumb
 * func_ov004_022326a8 @ 0x022326a8, 0x34 bytes, Thumb
 * func_ov004_02232514 @ 0x02232514, 0x194 bytes, Thumb
 * func_ov004_02232508 @ 0x02232508, 0xc bytes, Thumb
 */

#include "types.h"

extern int func_020574b4(void *);
extern void *func_020b9e58(void *);
extern void *func_020ba294(void *);
extern void func_020574b0(void *object);
extern int func_02057468(void *, int, void *);
extern char data_ov004_02255a90;
extern int func_020b67d4(void);
extern int func_020b6804(void);
extern void *func_02060ee0(void *, int);
extern void func_020611bc(void *, int, int);
extern char data_021ebcd4;
extern int func_02057a50(int, const char *name);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern int func_020ba1f4(void *, u16 *);
extern int func_020b6730(void);
extern int func_020573f0(void *, int, void *, void *);
extern int func_020ba1ec(void *);
extern int func_020b9d3c(void *, int, int, int, int, int);
extern int func_020b65c4(void);
extern int func_02034a00(int, u16 *);
extern int func_0204c100(u16 *);
extern int func_0204c090(u16 *);
extern int func_02072614(void);
extern int func_02072630(int, u8, u8);
extern int func_020573b8(void *, int, int, int);
extern int data_ov004_02255a84;
extern char data_ov004_02255b34;
extern char data_ov004_02255b40;
extern void func_020b9e2c(int arg);
extern void *func_0203cbcc(void *);
extern char data_ov004_02255aa0;
extern void func_02061194(void *, int, int);
extern int func_0203cb3c(void *, u16 *);
extern int func_0203cb34(void *);
extern int func_020349d0(int, u16 *);
extern int data_ov004_02255a80;
extern char data_ov004_02255b18;
extern char data_ov004_02255b24;

int func_ov004_022327a0(char *self, u16 *item, int a2, int a3);
int func_ov004_02232514(char *self, u16 *item, int a2, int a3);

void *func_ov004_022329e0(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self) = 0xfff1;
    *(u16 *) (self + 0x2) = 0xfff1;
    func_020b9e58(self + 0x4);
    func_020ba294(self + 0x2c);
    func_020574b4(self + 0x10f4);
    *(u16 *) (self) = 0xfff1;
    *(u16 *) (self + 0x2) = 0xfff1;
    *(void **) (self + 0x10f0) = 0x0;
    return self;
}

void *func_ov004_022329c8(char *self)
{
    // DECLS
    // ENDDECLS
    func_020574b0(self + 0x10f4);
    return self;
}

void *func_ov004_022329c4(void *self)
{
    return (char *) self + 0x2;
}

unsigned short *func_ov004_022329c0(void *record)
{
    return (unsigned short *) record;
}

int func_ov004_022329b4(char *self)
{
    // DECLS
    // ENDDECLS
    return *(int *) (self + 0x10f0);
}

int func_ov004_02232980(char *self, int a1, int a2)
{
    if (a2 != 0) {
        func_02057468(self + 0x10f4, a1, &data_ov004_02255a90);
        *(int *) (self + 0x10fc) = a2;
        return 1;
    }
    return 0;
}

int func_ov004_02232968(char *self, int a1, int a2, int a3)
{
    // DECLS
    char frame[0x8];
    // ENDDECLS
    *(u16 *) (frame) = a1;
    return func_ov004_022327a0((char *) self, (u16 *) frame, a2, a3);
}

void func_ov004_02232934(int a0, int a1, int a2)
{
    void *p;
    if (func_020b67d4() != 0) {
        p = func_02060ee0(&data_021ebcd4, func_020b6804());
        if (p != 0) {
            func_020611bc(p, a1, a2);
        }
    }
}

int func_ov004_022327a0(char *self, u16 *item, int a2, int a3)
{
    int same;
    int ok;
    u16 v;
    if (func_02057a50(a2, (const char *) (data_ov004_02255a84)) == -1) {
        return 0;
    }
    if (func_0204bcdc(self + 2) != 0) {
        int mine = func_0204bc64(self + 2);
        same = (mine == func_0204bc64(item));
    } else {
        same = (*(u16 *) (self + 2) == *item);
    }
    if (same == 0 || *(int *) (self + 0x10f0) != a3) {
        ok = 0;
        v = *item;
        if (v >= 0x1100 && v <= 0x1143) {
            ok = 1;
        }
        if (ok != 0) {
            if (func_020ba1f4(self + 0x2c, item) != 0) {
                if (func_020b6730() == 0) {
                    func_020573f0(self + 0x10f4, *(int *) (self + 0x10fc), &data_ov004_02255b34, &data_ov004_02255b40);
                }
                if (func_020b9d3c(self + 4, a2, data_ov004_02255a84, func_020ba1ec(self + 0x2c), 0, 0) != 0) {
                    *(u16 *) self = *(u16 *) (self + 2);
                    *(u16 *) (self + 2) = *item;
                    func_ov004_02232934((int) self, (int) ((u16 *) (self + 2)), a3);
                    func_02034a00(func_020b65c4(), (u16 *) (self + 2));
                    return 1;
                }
            }
        } else if (v >= 0x1188 && v <= 0x11a7) {
            int c, d, x;
            c = func_0204c100(item);
            d = func_0204c090(item);
            x = func_02072630(func_02072614(), c, d);
            func_020573b8(self + 0x10f4, x, 0, 0);
            *(u16 *) self = *(u16 *) (self + 2);
            *(u16 *) (self + 2) = *item;
            *(int *) (self + 0x10f0) = a3;
            func_ov004_02232934((int) self, (int) ((u16 *) (self + 2)), a3);
            func_02034a00(func_020b65c4(), (u16 *) (self + 2));
            return 1;
        }
        return 0;
    }
    *(u16 *) self = *(u16 *) (self + 2);
    *(u16 *) (self + 2) = *item;
    *(int *) (self + 0x10f0) = a3;
    func_ov004_02232934((int) self, (int) ((u16 *) (self + 2)), a3);
    func_02034a00(func_020b65c4(), (u16 *) (self + 2));
    return 1;
}

void func_ov004_02232794(int arg)
{
    func_020b9e2c(arg + 4);
}

void *func_ov004_02232754(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self) = 0xfff1;
    *(u16 *) (self + 0x2) = 0xfff1;
    func_020b9e58(self + 0x4);
    func_0203cbcc(self + 0x2c);
    func_020574b4(self + 0x20f4);
    *(u16 *) (self) = 0xfff1;
    *(u16 *) (self + 0x2) = 0xfff1;
    *(void **) (self + 0x20f0) = 0x0;
    return self;
}

void *func_ov004_0223273c(char *self)
{
    // DECLS
    // ENDDECLS
    func_020574b0(self + 0x20f4);
    return self;
}

void *func_ov004_02232738(void *self)
{
    return (char *) self + 0x2;
}

unsigned short *func_ov004_02232734(void *record)
{
    return (unsigned short *) record;
}

int func_ov004_02232728(char *self)
{
    // DECLS
    // ENDDECLS
    return *(int *) (self + 0x20f0);
}

int func_ov004_022326f4(char *self, int a1, int a2)
{
    if (a2 != 0) {
        func_02057468(self + 0x20f4, a1, &data_ov004_02255aa0);
        *(int *) (self + 0x20fc) = a2;
        return 1;
    }
    return 0;
}

int func_ov004_022326dc(char *self, int a1, int a2, int a3)
{
    // DECLS
    char frame[0x8];
    // ENDDECLS
    *(u16 *) (frame) = a1;
    return func_ov004_02232514((char *) self, (u16 *) frame, a2, a3);
}

void func_ov004_022326a8(int a0, int a1, int a2)
{
    void *p;
    if (func_020b67d4() != 0) {
        p = func_02060ee0(&data_021ebcd4, func_020b6804());
        if (p != 0) {
            func_02061194(p, a1, a2);
        }
    }
}

int func_ov004_02232514(char *self, u16 *item, int a2, int a3)
{
    int same;
    int ok;
    u16 v;
    if (func_02057a50(a2, (const char *) (data_ov004_02255a80)) == -1) {
        return 0;
    }
    if (func_0204bcdc(self + 2) != 0) {
        int mine = func_0204bc64(self + 2);
        same = (mine == func_0204bc64(item));
    } else {
        same = (*(u16 *) (self + 2) == *item);
    }
    if (same == 0 || *(int *) (self + 0x20f0) != a3) {
        ok = 0;
        v = *item;
        if (v >= 0x1144 && v <= 0x1187) {
            ok = 1;
        }
        if (ok != 0) {
            if (func_0203cb3c(self + 0x2c, item) != 0) {
                if (func_020b6730() == 0) {
                    func_020573f0(self + 0x20f4, *(int *) (self + 0x20fc), &data_ov004_02255b18, &data_ov004_02255b24);
                }
                if (func_020b9d3c(self + 4, a2, data_ov004_02255a80, func_0203cb34(self + 0x2c), 0, 0) != 0) {
                    *(u16 *) self = *(u16 *) (self + 2);
                    *(u16 *) (self + 2) = *item;
                    func_ov004_022326a8((int) self, (int) ((u16 *) (self + 2)), a3);
                    func_020349d0(func_020b65c4(), (u16 *) (self + 2));
                    return 1;
                }
            }
        } else if (v >= 0x1188 && v <= 0x11a7) {
            int c, d, x;
            c = func_0204c100(item);
            d = func_0204c090(item);
            x = func_02072630(func_02072614(), c, d);
            func_020573b8(self + 0x20f4, x, 0, 0);
            *(u16 *) self = *(u16 *) (self + 2);
            *(u16 *) (self + 2) = *item;
            *(int *) (self + 0x20f0) = a3;
            func_ov004_022326a8((int) self, (int) ((u16 *) (self + 2)), a3);
            func_020349d0(func_020b65c4(), (u16 *) (self + 2));
            return 1;
        }
        return 0;
    }
    *(u16 *) self = *(u16 *) (self + 2);
    *(u16 *) (self + 2) = *item;
    *(int *) (self + 0x20f0) = a3;
    func_ov004_022326a8((int) self, (int) ((u16 *) (self + 2)), a3);
    func_020349d0(func_020b65c4(), (u16 *) (self + 2));
    return 1;
}

void func_ov004_02232508(int arg)
{
    func_020b9e2c(arg + 4);
}
