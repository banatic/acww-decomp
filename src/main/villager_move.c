/* villager_move: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207b410 @ 0x0207b410, 0xc bytes, Thumb
 * func_0207b3dc @ 0x0207b3dc, 0x32 bytes, Thumb
 * func_0207b310 @ 0x0207b310, 0xcc bytes, Thumb
 * func_0207b2f8 @ 0x0207b2f8, 0x18 bytes, Thumb
 * func_0207b268 @ 0x0207b268, 0x90 bytes, Thumb
 * func_0207b05c @ 0x0207b05c, 0x20c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0207b310 {
    char pad_00[0x4076];
    signed char unk_4076;
} UnkStruct_0207b310;

extern void *func_0209a778(void *record);
extern int func_0209bd44(void *);
extern int func_0209a774(int address);
extern int func_0207cf14(void *, void *);
extern unsigned short data_020cd4c4[];
extern void func_0209e474(void *p);
extern int func_0208150c(char *p);
extern int func_02003704(int x);
extern int func_0207f150(char *p);
extern int func_0207dca8(char *p);
extern int func_02080998(char *p, int n, void *buf);
extern int func_0207cc54(int a, int b, int c);
extern void *func_0207cec0(UnkStruct_0207b310 *self, int i);
extern unsigned char *func_02080890(unsigned int object);
extern int func_020644cc(int x);
extern int func_0207cad4(void *);
extern int func_0209a67c(void *sub);
extern void *func_0209a6fc(void *sub, unsigned char level);
extern void func_02095238(void *p);
extern void func_0209df64(u8 *d);
extern int func_0209dd9c(u8 *d, u8 *p);
extern void func_0209a77c(u8 *p);
extern int func_0209a654(u8 *p);
extern int func_0209a610(u8 *p, u8 *d);
extern int func_0209dcdc(u8 *a, u8 *b);
extern void func_0209dfd8(u8 *a, u8 *b, int c, int e, int f);
extern void func_0209e29c(u8 *a, int n);
extern void func_0209e140(u8 *a, int n);
extern void MI_CpuCopy8(u8 *a, u8 *b, int n);
extern void func_0209a710(u8 *p, void *q, u8 *d);
extern void func_0207a180(u8 *p);

unsigned int func_0207b410(unsigned int arg0)
{
    return arg0 + 0x3f90;
}

int func_0207b3dc(void *base)
{
    if (func_0209bd44(func_0209a778((void *) func_0207b410((unsigned int) base))) != 0) {
        return func_0207cf14(base, (void *) func_0209a774((int) func_0207b410((unsigned int) base)));
    }
    return -1;
}

int func_0207b310(UnkStruct_0207b310 *self, unsigned int k)
{
    // DECLS
    int cnt;
    int z;
    int buf[2];
    unsigned char mask;
    char *p;
    int i;
    int sel;
    void *e;
    unsigned char *q;
    // ENDDECLS

    if (k >= 0xc) {
        return -1;
    }
    mask = 0;
    buf[0] = 0;
    buf[1] = 0;
    p = (char *) self;
    cnt = 0;
    func_0209e474(buf);
    for (i = 0; i < 8; i++) {
        z = 0;
        if (i != self->unk_4076) {
            if (func_02003704(func_0208150c(p))) {
                if (func_0207f150(p) == 3) {
                    if (func_0207dca8(p) != 0) {
                        if (func_02080998(p, 0xf, buf) == ~z) {
                            mask |= 1 << i;
                            cnt++;
                        }
                    }
                }
            }
        }
        p += 0x7ec;
    }
    sel = func_0207cc54(mask, cnt, 8);
    e = func_0207cec0(self, sel);
    if (e != 0) {
        q = func_02080890((unsigned int) e);
        if (func_020644cc(data_020cd4c4[k]) < q[3] + 0x80) {
            return sel;
        }
    }
    return -1;
}

int func_0207b2f8(void *argument0)
{
    int result;
    if (func_0207cad4((void *) argument0) < 7) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

void func_0207b268(unsigned char *arg)
{
    int level;
    void *res;

    level = arg[0x404a];
    res = 0;

    if (func_0209a67c(arg + 0x3f90) != 0 || arg[0x4045] != 0) {
        if (level == 0) {
            level = 5;
        } else if ((unsigned char) level < 5) {
            level--;
        }
        arg[0x404a] = level;
        res = func_0209a6fc(arg + 0x3f90, arg[0x404a]);
    } else {
        if ((unsigned char) (level + 1) < 5) {
            arg[0x404a] = (unsigned char) (level + 1);
            res = func_0209a6fc(arg + 0x3f90, arg[0x404a]);
        } else if ((unsigned char) level < 5) {
            res = func_0209a6fc(arg + 0x3f90, (unsigned char) level);
        }
    }

    if (res != 0) {
        func_02095238(res);
    }
}

void func_0207b05c(u8 *self)
{
    int n;
    int flag;
    u8 d[0x10];
    int r;
    int cnt;
    int rem;
    int delta;
    void *o;

    r = func_0207b3dc((void *) self);
    func_0209df64(d);
    if (r == -1) {
        goto notfound;
    }
    if (func_0209dd9c(d, self + 0x4042) == 0) {
        func_0209a77c(self + 0x3f90);
        return;
    }
    if (func_0209a654(self + 0x3f90) != 0) {
        if (func_0209a610(self + 0x3f90, d) != 0) {
            return;
        }
        func_0209a77c(self + 0x3f90);
        return;
    }
    delta = func_0209dcdc(d, self + 0x4046);
    if (delta == 0) {
        return;
    }
    n = 0;
    cnt = 0;
    flag = 0;
    if (*(u8 *) (self + 0x4045) == 0) {
        if (func_0209dcdc(d, self + 0x4042) >= 0xa) {
            int x = func_0209dcdc(self + 0x4046, self + 0x4042);
            if (x >= 0 && x < 0xa) {
                n = 9 - x;
            }
            flag = 1;
        }
    }
    if (delta < 0) {
        rem = -delta;
    } else {
        rem = delta;
    }
    if (n > rem) {
        n = delta;
    }
    while (n > 0) {
        func_0207b268((unsigned char *) self);
        n--;
        rem--;
        cnt++;
    }
    if (flag != 0) {
        *(u8 *) (self + 0x4045) = 1;
    }
    while (rem > 0) {
        func_0207b268((unsigned char *) self);
        rem--;
        cnt++;
        if (func_0209a654(self + 0x3f90) != 0) {
            break;
        }
    }
    if (func_0209a654(self + 0x3f90) == 0) {
        goto copyout;
    }
    if (rem >= 3 && delta > 0) {
        func_0209a77c(self + 0x3f90);
        return;
    }
    if (cnt <= 0) {
        return;
    }
    func_0209dfd8(&d[4], self + 0x4046, 0, 0, 0);
    if (delta > 0) {
        func_0209e29c(&d[4], cnt);
        *(u8 *) (self + 0x4048) = d[9];
        *(u8 *) (self + 0x4047) = d[8];
        *(u8 *) (self + 0x4046) = d[7];
        return;
    }
    if (rem > 0) {
        func_0209a77c(self + 0x3f90);
        return;
    }
    func_0209e140(&d[4], cnt);
    *(u8 *) (self + 0x4048) = d[9];
    *(u8 *) (self + 0x4047) = d[8];
    *(u8 *) (self + 0x4046) = d[7];
    return;
copyout:
    MI_CpuCopy8(d, self + 0x4046, 4);
    return;
notfound:
    if (func_0207b2f8((void *) self) != 0) {
        r = func_0207b310((UnkStruct_0207b310 *) self, (u8) ((u8) (d[1] - 1)));
        if (r != -1) {
            o = func_0207cec0((UnkStruct_0207b310 *) self, r);
            if (o != 0) {
                if (func_02003704((int) ((void *) func_0208150c((char *) o))) != 0) {
                    func_0209a710(self + 0x3f90, (void *) func_0208150c((char *) o), d);
                    *(u8 *) (self + 0x4076) = (u8) r;
                    func_0207a180(self + 0x3f7c);
                }
            }
        }
    }
}
