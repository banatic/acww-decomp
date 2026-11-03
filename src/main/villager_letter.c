/* villager_letter: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207d3dc @ 0x0207d3dc, 0xe0 bytes, Thumb
 * func_0207d33c @ 0x0207d33c, 0xa0 bytes, Thumb
 */

#include "types.h"

struct Big {
    u8 b[0x104];
};

extern u8 data_021d1358[];
extern int func_020951bc(void *);
extern int func_02003704(void *);
extern void func_02066694(struct Big *);
extern int func_020036e8(void *);
extern int func_0209765c(int);
extern int func_020644cc(void *);
extern int func_0200366c(void *, void *, int, void *);
extern void func_02066228(struct Big *, u8 *, u8 *, u8 *, u8 *, void *, u8 *, void *, void *, int);
extern unsigned short func_02065ed0(struct Big *, int, int);
extern int func_020979f0(struct Big *, int);
extern void func_02066688(struct Big *);
extern void func_020662bc(void *, unsigned char *, void *, unsigned char *, int, int, int);
extern int data_021d1380;

int func_0207d3dc(void *p0, int p1, void *p2, void *p3, void *p4, u16 *p6)
{
    u8 buf[8];
    struct Big big;
    int v1;
    int v2;
    int v3;
    int v4;

    if (func_020951bc(p3) != 0 && func_02003704(p4) != 0) {
        func_02066694(&big);
        buf[0] = (u8) func_0209765c((int) func_020036e8(p4));
        v1 = p1 + func_020644cc(p2);
        v2 = p1 + func_020644cc(p2);
        v3 = p1 + func_020644cc(p2);
        v4 = p1 + func_020644cc(p2);
        func_0200366c(p4, data_021d1358, 0x28, p0);
        buf[1] = (u8) v1;
        buf[2] = (u8) v2;
        buf[3] = (u8) v3;
        buf[4] = (u8) v4;
        func_02066228(&big, &buf[1], &buf[2], &buf[3], &buf[4], data_021d1358, &buf[0], p4, p3, 1);
        if (p6 != 0 && *p6 != 0xfff1) {
            func_02065ed0(&big, *p6, 1);
        }
        if (func_020979f0(&big, 0) != 0) {
            func_02066688(&big);
            return 1;
        }
        func_02066688(&big);
    }
    return 0;
}

int func_0207d33c(int a, int b, int c, int d, void *e)
{
    unsigned char bytearr[2];
    unsigned int buf[65];

    if (func_020951bc((void *) c) == 0) {
        goto fail;
    }
    if (func_02003704((void *) d) == 0) {
        goto fail;
    }
    func_02066694((struct Big *) buf);
    bytearr[0] = (unsigned char) func_0209765c(func_020036e8((void *) d));
    func_0200366c((void *) d, &data_021d1380, 0x28, (void *) a);
    bytearr[1] = b;
    func_020662bc(buf, bytearr + 1, &data_021d1380, bytearr, d, c, 1);
    if (e && *(unsigned short *) e != 0xfff1) {
        func_02065ed0((struct Big *) buf, (unsigned short) (*(unsigned short *) e), 1);
    }
    if (func_020979f0((struct Big *) buf, 0) != 0) {
        func_02066688((struct Big *) buf);
        return 1;
    }
    func_02066688((struct Big *) buf);
fail:
    return 0;
}
