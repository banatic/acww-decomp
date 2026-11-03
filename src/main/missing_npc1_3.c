/* missing_npc1_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c2b1c @ 0x020c2b1c, 0x118 bytes, Thumb
 * func_020c2a40 @ 0x020c2a40, 0xdc bytes, Thumb
 * func_020c2898 @ 0x020c2898, 0x1a8 bytes, Thumb
 * func_020c2868 @ 0x020c2868, 0x30 bytes, Thumb
 * func_020c2860 @ 0x020c2860, 0x8 bytes, Thumb
 * func_020c2858 @ 0x020c2858, 0x8 bytes, Thumb
 */

#include "types.h"

extern void *data_020d8c64;
extern void *data_020da088;
extern void *data_020e7c60;
extern void *func_020edf70(unsigned int);
extern void *func_0203f130(void *);
extern void *func_0205467c(void *);
extern void func_0201b394(void *);
extern void *func_0201a430(void *);
extern int func_020169a8(void *);
extern int func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void *func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void *func_02032c64(void *);
extern void *func_02089c88(void *);
extern void *func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_020c1b84(void *);
extern int func_0202edc8(void *arg);
extern void func_0201c280(void *a, void *b);
extern void func_020c1b30(void *a, void *b);
extern void func_0201af28(void *a, int b, int c, int d, int e);
extern int func_020b65c4(void);
extern void *data_021fbbe0;
extern int func_0202ec58(void *p);
extern void *func_020984e8(void);
extern int func_020b65b8(void);
extern void func_0204f7e0(void *a, void *b);
extern int func_02078dd4(void *a, int b, int c, int d);
extern int func_02078e98(void *a, int b);
extern int func_0208602c(void);
extern int func_020860c4(int x);
extern int func_02087f30(int x);
extern void func_02087f40(int x, void *a);
extern void *func_0204e414(void);
extern int func_0204e08c(void *a, void *b, int c, int d);
extern int func_02099020(int a, int b);
extern int func_0202ea80(int a, int b);
extern void func_020c1b28(void *a, int b);
extern void func_020c26b4(void *a, int b);
extern void func_0203e334(void);
extern int func_0202ec14(int arg);
extern void func_0203e328(void);
extern int data_020e7bac;
extern int data_020e7b7c;

void *func_020c2b1c(void)
{
    u8 *p;

    p = (u8 *) func_020edf70(0x72c);
    if (p) {
        func_0203f130(p);
        *(void **) p = &data_020d8c64;
        *(u16 *) (p + 0xea) = 0xfff1;
        func_0205467c(p + 0xec);
        func_0201b394(p + 0x2a0);
        func_0201a430(p + 0x2ac);
        func_020169a8(p + 0x334);
        func_0201b324(p + 0x350);
        func_0201af14(p + 0x3a8);
        func_0201b370(p + 0x3aa);
        func_0201adec(p + 0x3b0);
        func_0201a7ec(p + 0x418);
        func_0201a794(p + 0x420);
        func_02032c64(p + 0x49c);
        func_02089c88(p + 0x4cc);
        func_020f55cc(p + 0x514);
        func_02013c2c(p + 0x558);
        func_02019eb0(p + 0x564);
        func_0201489c(p + 0x618);
        *(void **) p = &data_020da088;
        func_02082f60(p + 0x640);
        *(void **) p = &data_020e7c60;
        func_020c1b84(p + 0x658);
    }
    return p;
}

int func_020c2a40(unsigned char *arg)
{
    if (func_0202edc8(arg) == 0) {
        return 0;
    }
    func_0201c280(arg, arg + 0x658);
    func_020c1b30(arg + 0x658, arg);
    func_0201af28(arg + 0x350, 2, 0x333, 0xcc, 0x133);
    func_0201af28(arg + 0x350, 1, 0x1b3, 0xcc, 0x133);
    if (func_020b65c4() == 0xb) {
        *(short *) (arg + 0x8e) = -32768;
        *(short *) (arg + 0x94) = -32768;
    }
    if (func_020b65c4() == 0xc) {
        *(short *) (arg + 0x8e) = -32768;
        *(short *) (arg + 0x94) = -32768;
    }
    if (func_020b65c4() == 0x2f) {
        *(short *) (arg + 0x8e) = 0;
        *(short *) (arg + 0x94) = 0;
        *(int *) (arg + 0x5c) = 0xe000;
        *(int *) (arg + 0x64) = 0x4000;
        func_0201af28(arg + 0x350, 1, 0x280, 0xcc, 0x133);
    }
    *(unsigned char *) (arg + 0x563) = 1;
    return 1;
}

int func_020c2898(void *p)
{
    int a, b;
    void *q;

    if (func_0202ec58(p) == 0) {
        return 0;
    }

    data_021fbbe0 = p;
    *(int *) ((char *) p + 0x724) = -1;
    q = func_020984e8();

    if (func_020b65c4() == 0) {
        func_0204f7e0((char *) p + 0x5c, (char *) p + 0x5c);
        if (func_02078dd4((char *) p + 0x5c, 1, 0, 0)) {
            func_02078e98((char *) p + 0x5c, 0);
            *(int *) ((char *) p + 0x5c) += 0x2000;
            *(int *) ((char *) p + 0x64) += 0x2000;
        }

        a = func_0208602c();
        b = func_020860c4(a);
        if (func_02087f30(b) != 0) {
            if (func_020b65b8() == 0xb) {
                func_0204e08c(func_0204e414(), (char *) p + 0x5c, 0, 0);
                *(int *) ((char *) p + 0x64) -= 0x2000;
                func_020c1b28((char *) p + 0x658, 3);
                func_020c26b4(p, 5);
                *(char *) ((char *) p + 0x510) = 0;
            } else {
                func_020c1b28((char *) p + 0x658, 5);
                func_020c26b4(p, 1);
            }
        } else {
            if (func_02099020((int) q, 0x33) == 0) {
                if (func_02099020((int) q, 0x31) == 0) {
                    func_020c1b28((char *) p + 0x658, 0);
                } else {
                    func_020c1b28((char *) p + 0x658, 1);
                }
                func_020c26b4(p, 1);
            } else {
                if (func_0202ea80(0x29, 0) == 0) {
                    func_020c1b28((char *) p + 0x658, 2);
                } else {
                    func_020c1b28((char *) p + 0x658, 3);
                }
                func_020c26b4(p, 1);
            }
        }
    } else {
        if (func_020b65c4() == 0xb) {
            func_020c1b28((char *) p + 0x658, 3);
            func_020c26b4(p, 5);
            *(char *) ((char *) p + 0x510) = 0;
        } else if (func_020b65c4() == 0xc) {
            a = func_0208602c();
            b = func_020860c4(a);
            func_02087f40(b, (char *) p + 0x5c);
            func_020c1b28((char *) p + 0x658, 3);
            func_020c26b4(p, 5);
        } else if (func_020b65c4() == 0x2f) {
            *(char *) ((char *) p + 0x510) = 0;
            func_0203e334();
            func_020c26b4(p, 8);
        }
    }
    return 1;
}

int func_020c2868(int arg)
{
    int result;

    if (func_0202ec14(arg) == 0) {
        return 0;
    }
    (*(int *) &data_021fbbe0) = 0;
    result = func_020b65c4();
    if (result == 0x2f) {
        func_0203e328();
    }
    return 1;
}

int func_020c2860(void)
{
    return (int) &data_020e7bac;
}

int func_020c2858(void)
{
    return (int) &data_020e7b7c;
}
