/* func_0207b05c @ 0x0207b05c, 0x20c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0207b3dc(u8 *s);
extern void func_0209df64(u8 *d);
extern int func_0209dd9c(u8 *d, u8 *p);
extern void func_0209a77c(u8 *p);
extern int func_0209a654(u8 *p);
extern int func_0209a610(u8 *p, u8 *d);
extern int func_0209dcdc(u8 *a, u8 *b);
extern void func_0207b268(u8 *s);
extern void func_0209dfd8(u8 *a, u8 *b, int c, int e, int f);
extern void func_0209e29c(u8 *a, int n);
extern void func_0209e140(u8 *a, int n);
extern void MI_CpuCopy8(u8 *a, u8 *b, int n);
extern int func_0207b2f8(u8 *s);
extern int func_0207b310(u8 *s, u8 k);
extern void *func_0207cec0(u8 *s, int k);
extern void *func_0208150c(void *p);
extern int func_02003704(void *p);
extern void func_0209a710(u8 *p, void *q, u8 *d);
extern void func_0207a180(u8 *p);

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

    r = func_0207b3dc(self);
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
        func_0207b268(self);
        n--;
        rem--;
        cnt++;
    }
    if (flag != 0) {
        *(u8 *) (self + 0x4045) = 1;
    }
    while (rem > 0) {
        func_0207b268(self);
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
    if (func_0207b2f8(self) != 0) {
        r = func_0207b310(self, (u8) (d[1] - 1));
        if (r != -1) {
            o = func_0207cec0(self, r);
            if (o != 0) {
                if (func_02003704(func_0208150c(o)) != 0) {
                    func_0209a710(self + 0x3f90, func_0208150c(o), d);
                    *(u8 *) (self + 0x4076) = (u8) r;
                    func_0207a180(self + 0x3f7c);
                }
            }
        }
    }
}
