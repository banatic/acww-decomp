/* tailor_sister_2: 18 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02223324 @ 0x02223324, 0x64 bytes, Thumb
 * func_ov004_022232b4 @ 0x022232b4, 0x70 bytes, Thumb
 * func_ov004_02223228 @ 0x02223228, 0x8c bytes, Thumb
 * func_ov004_022231c4 @ 0x022231c4, 0x64 bytes, Thumb
 * func_ov004_022231c0 @ 0x022231c0, 0x4 bytes, Thumb
 * func_ov004_022231bc @ 0x022231bc, 0x4 bytes, Thumb
 * func_ov004_02223180 @ 0x02223180, 0x3c bytes, Thumb
 * func_ov004_02223150 @ 0x02223150, 0x30 bytes, Thumb
 * func_ov004_02223118 @ 0x02223118, 0x38 bytes, Thumb
 * func_ov004_0222301c @ 0x0222301c, 0xfc bytes, Thumb
 * func_ov004_02222fe4 @ 0x02222fe4, 0x38 bytes, Thumb
 * func_ov004_02222f8c @ 0x02222f8c, 0x58 bytes, Thumb
 * func_ov004_02222f68 @ 0x02222f68, 0x24 bytes, Thumb
 * func_ov004_02222f64 @ 0x02222f64, 0x4 bytes, Thumb
 * func_ov004_02222f2c @ 0x02222f2c, 0x38 bytes, Thumb
 * func_ov004_02222f14 @ 0x02222f14, 0x18 bytes, Thumb
 * func_ov004_02222efc @ 0x02222efc, 0x18 bytes, Thumb
 * func_ov004_02222edc @ 0x02222edc, 0x20 bytes, Thumb
 */

#include "types.h"

typedef void (*VF)(char *);

struct UnkStruct_02222f8c {
    char pad_00[0x64];
    int unk_64;
};

struct _Obj {
    void *vtbl;
};

extern int func_02019c20(void *, int, int, int, int, int);
extern void *data_020c80f8;
extern void func_ov004_02223388(void *self, int a);
extern int func_02016884(void *a, int b, void *c);
extern int func_ov004_0222fd70(void);
extern int func_ov004_0222fdb8(void);
extern void func_ov004_0222fd58(unsigned short v);
extern unsigned int func_ov004_02222b3c(void *self);
extern int func_ov004_0222fd94(void);
extern int func_020147e0(void *p, int a, int b);
extern int func_02016104(void *p);
extern int func_0201c314(void *self, int n);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *p);
extern char *data_020ccf94;
extern int func_02073d90(void *g);
extern int func_0202ea80(int a, int b);
extern void func_ov004_02222b24(void *self, unsigned int k);
extern int func_0203e020(void *self);
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern int func_02019e00(void *);
extern int func_02019de8(void *);
extern void func_0201ad18(int, int, int, int, int, int, int, int);
extern unsigned char data_020c814c[];
extern unsigned char data_021fbee8[];
extern int func_0201c0e0(char *self);
extern int func_0201c040(char *self, int *p, int *q);
extern void func_0201c054(char *self, int a, int b, int c);
extern int func_0201c2a4(char *self, int n);
extern void func_02016108(char *a, int b);
extern int func_020a7278(void);
extern void *func_0202eb70(void *arg);
extern int data_ov004_022543cc;
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *);

int func_ov004_02223324(char *self)
{
    // DECLS
    // ENDDECLS
    func_0201ad18((int) (self + 0x3b0), 0x0, 0x0, 0x0, (int) (((void **) data_021fbee8)), 0x4,
                  *(int *) ((char *) ((void **) data_020c814c)), 0x1);
    func_02019c20(self + 0x564, 0x1, 0xe4, 0x0, *(u16 *) ((char *) &data_020c80f8), *(u16 *) (self + 0x710));
    return 0x1;
}

int func_ov004_022232b4(char *self)
{
    unsigned int m, sh;

    if (*(short *) (self + 0x70c) != *(short *) (self + 0x8e)) {
        func_ov004_02223388(self, 3);
        return 1;
    }
    if (func_02016884(self + 0x334, 0xe4, self + 0x2a0) != 0) {
        if (func_ov004_0222fd70() != 0) {
            func_ov004_0222fdb8();
            m = *(unsigned char *) (self + 0x712) * 0x38;
            sh = (unsigned int) (*(int *) (self + 0x190) << 4) >> 16;
            func_ov004_0222fd58((unsigned short) (m + sh));
        }
    }
    return 1;
}

int func_ov004_02223228(char *self)
{
    int n, r;

    if (func_ov004_02222b3c(self) >= 6) {
        func_0201ad18((int) (self + 0x3b0), 1, 0, 0, (int) ((int *) data_021fbee8), 4, (*(int *) data_020c814c), 1);
    }
    func_ov004_0222fd94();
    if (func_ov004_02222b3c(self) < 6) {
        func_020147e0(self + 0x618, 1, 0);
    } else {
        n = func_02016104(self + 0x658);
        r = 0;
        if (n != 0) {
            r = func_0201c314(self, n);
        }
        func_020147fc(self + 0x618, 0, r, 0);
    }
    return 1;
}

int func_ov004_022231c4(char *self)
{
    unsigned int k;

    if (func_02014868(self + 0x618) != 0) {
        return 1;
    }
    if (func_02073d90(data_020ccf94) == 0) {
        if (func_0202ea80(0x11, 1) == 0) {
            k = (unsigned char) ((int) func_ov004_02222b3c(self) + 1);
            if (k > 0xf) {
                k = 0xf;
            }
            func_ov004_02222b24(self, k);
        }
    }
    func_0203e020(self);
    func_ov004_02223388(self, 2);
    return 1;
}

int func_ov004_022231c0(void)
{
    return 1;
}

int func_ov004_022231bc(void)
{
    return 1;
}

int func_ov004_02223180(void *self)
{
    int arg5;
    int arg6;
    int arg7;
    int arg8;
    int arg9;
    int arg10;
    int arg11;

    arg5 = 0;
    arg6 = 0;
    arg7 = *(signed short *) ((char *) self + 0x70c);
    arg8 = 0;
    arg9 = 0;
    arg10 = (*(unsigned short *) &data_020c80f8);
    arg11 = 0;

    func_02019d0c((char *) self + 0x564, 3, 1, 0, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
    return 1;
}

int func_ov004_02223150(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_ov004_02223388(self, 0);
        }
    }
    return 1;
}

int func_ov004_02223118(int a)
{
    func_0201ad18(a + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, *((int *) data_020c814c), 1);
    return 1;
}

int func_ov004_0222301c(char *self)
{
    // DECLS
    int p, q;
    char *o;
    int k;
    // ENDDECLS

    if (func_0201c0e0(self) != 0) {
        p = 4;
        q = 4;
        if (func_0201c040(self, &p, &q) != 0 && p == *(int *) (data_020ccf94 + 0x64) && p == q) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), *(int *) (data_020ccf94 + 0x64));
            o = self + 0x658;
            (*(VF *) (*(char **) o + 8))(o);
            func_02016108(self + 0x658, func_0201c2a4(self, 4));
            func_ov004_02223388((void *) self, 1);
        } else if (func_020a7278() != 0 && q == 4) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), 4);
            func_ov004_02223388((void *) self, 0);
        }
    } else if (func_020a7278() == 0) {
        if (func_02016884((void *) (self + 0x334), 0xe4, (void *) (self + 0x2a0)) != 0) {
            if (func_ov004_0222fd70() != 0) {
                func_ov004_0222fdb8();
                k = *(u8 *) (self + 0x712) * 0x38;
                func_ov004_0222fd58((u16) ((u16) (k + (u16) (*(int *) (self + 0x190) >> 12))));
            }
        } else if (func_ov004_0222fd70() == 0) {
            func_ov004_0222fd94();
        }
    }
    return 1;
}

int func_ov004_02222fe4(int a)
{
    func_0201ad18(a + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, *((int *) data_020c814c), 1);
    return 1;
}

int func_ov004_02222f8c(int arg)
{
    int a, b;
    if (func_0201c0e0((char *) arg) != 0) {
        a = 4;
        b = 4;
        if (func_0201c040((char *) arg, &a, &b) != 0) {
            if (a == 4) {
                if (func_020a7278() != 0) {
                    func_0201c054((char *) arg, 1, (*(struct UnkStruct_02222f8c **) &data_020ccf94)->unk_64, 4);
                    func_ov004_02223388((void *) arg, 0);
                }
            }
        }
    }
    return 1;
}

int func_ov004_02222f68(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222fd94();
    *(u16 *) (self + 0x710) = (*(int *) (self + 0x190) >> 12);
    return 0x1;
}

int func_ov004_02222f64(void)
{
    return 1;
}

void func_ov004_02222f2c(char *self)
{
    // DECLS
    // ENDDECLS
    func_0201ad18((int) (self + 0x3b0), (unsigned char) 0x0, 0x0, 0x0, (int) (((void **) data_021fbee8)), 0x4,
                  *(int *) ((char *) ((void **) data_020c814c)), (unsigned char) 0x1);
}

void *func_ov004_02222f14(void *arg)
{
    func_0202eb70(arg);
    *(void **) arg = &data_ov004_022543cc;
    return arg;
}

void *func_ov004_02222efc(void *arg)
{
    *((void **) arg) = &data_ov004_022543cc;
    func_0202eb20(arg);
    return arg;
}

void *func_ov004_02222edc(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_022543cc);
    func_0202eb20(obj);
    func_020edb3c(obj);
    return obj;
}
