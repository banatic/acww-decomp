/* museum_aquarium_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02234a04 @ 0x02234a04, 0x94 bytes, Thumb
 * func_ov004_0223494c @ 0x0223494c, 0xb8 bytes, Thumb
 * func_ov004_02234810 @ 0x02234810, 0x13c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02234a04;

struct UnkStruct_02234a04_2 {
    struct UnkStruct_02234a04 *p;
};

struct UnkStruct_02234a04_3 {
    u8 pad_00[4];
};

typedef void (*Method)(char *);

extern u8 data_ov004_022593a0;
extern u8 data_ov004_022593a4;
extern u8 data_ov004_02255c30;
extern u8 data_ov004_02255c34;
extern struct UnkStruct_02234a04_2 data_ov004_022594d4[];
extern int func_020b6590(void);
extern int func_020b7e04(int h, void *p);
extern void func_ov004_02234b9c(struct UnkStruct_02234a04_3 *self, struct UnkStruct_02234a04_2 *x, int i);
extern void func_02089bec(void *d, void *a, int b, int c, int e, int f, int g, int h, int i);
extern void func_02089fc8(void *d);
extern void *func_0209d238(void *, void *);
extern char data_ov004_02255f04[];
extern char data_ov004_02255f20[];
extern int func_02064328(char *, char *, ...);
extern int func_0209d0ac(void *, void *, char *);
extern short func_ov004_02239474(int, int);
extern int func_0209d088(void *);
extern int func_02055f2c(void *, int, int);
extern int func_0209d324(void *);
extern void func_ov004_02235374(char *, int);
extern void *NNS_G3dGetJntAnmSet(void *);
extern int func_02107b44(void *, int);
extern int func_02055140(void *, int);
extern void func_02055060(void *, int, int, int, unsigned short, unsigned short);
extern void func_02055050(void *);
extern int func_02055478(void *, int);
extern void func_ov004_022347b8(char *, char **);

void func_ov004_0223494c(void *self, int n);

int func_ov004_02234a04(struct UnkStruct_02234a04_3 *self)
{
    u8 m;
    int i;
    struct UnkStruct_02234a04_2 *p;

    m = data_ov004_022593a0;
    if (m == 0) {
        func_020b7e04(func_020b6590(), (u8 *) self + 0x2a8);
        func_020b7e04(func_020b6590(), (u8 *) self + 0x550);
    } else if (m == 1) {
        func_020b7e04(func_020b6590(), (u8 *) self + 0x2a8);
    }
    i = data_ov004_02255c30 - 1;
    p = &data_ov004_022594d4[i];
    while (i >= data_ov004_022593a4) {
        if (p->p != 0) {
            func_ov004_02234b9c(self, p, i);
        }
        p--;
        i--;
    }
    func_ov004_0223494c((void *) self, data_ov004_02255c34);
    return 1;
}

void func_ov004_0223494c(void *self, int n)
{
    int i;
    int z;
    char *d;
    char *e;

    i = 0;
    z = i;
    for (; i < n; i++) {
        e = (char *) self + i * 0x64;
        d = (char *) self + 0x50 + i * 0x64;
        func_02089bec(d, (char *) self + 0xa0 + i * 0x64, *(int *) (e + 0xac), *(int *) (e + 0xb0), 0x102, 0x140, z, 0xff,
                      0x1000);
        func_02089fc8(d);
    }
    if ((*(unsigned char *) &data_ov004_022593a0) == 1) {
        func_02089bec((char *) self + 0x244, (char *) self + 0x294, *(int *) ((char *) self + 0x2a0),
                      *(int *) ((char *) self + 0x2a4), 0x202, 0x140, 0, 0xff, 0x1000);
        func_02089fc8((char *) self + 0x244);
    }
}

int func_ov004_02234810(char *self, char **slot, int which)
{
    int result, id;
    void *resource, *animation, *model;
    int value, track, group;
    char name[24];
    result = 0;
    id = *(int *) (*slot + 0x15c);
    resource = func_0209d238(self + 0x7f8, *slot + 0x166);
    animation = *slot + 0x168;
    group = id / 10 + 10;
    if (id < 10) {
        func_02064328(name, data_ov004_02255f04, group, id);
    } else {
        func_02064328(name, data_ov004_02255f20, group, id);
    }
    if (func_0209d0ac(animation, resource, name)) {
        *(short *) (*slot + 0x1c0) = func_ov004_02239474(0x168, 0);
        *(short *) (*slot + 0x1c2) = *(short *) (*slot + 0x1c0);
        (*(Method **) *slot)[0](*slot);
        model = *slot + 0x64;
        func_02055f2c(model, func_0209d088(animation), 0);
        value = func_0209d324(resource);
        if (!*(void **) (*slot + 0x54)) {
            func_ov004_02235374(self, which);
            return 0;
        }
        track = func_02107b44(NNS_G3dGetJntAnmSet(*(void **) (*slot + 0x54)), 0);
        if (func_02055140(model, value)) {
            func_02055060(model, track, 0, 0x1000, 1, 0);
            func_02055050(model);
            func_02055478(model, func_0209d324(resource));
            *(int *) (*slot + 0x160) = 2;
            (*slot)[0x1e8] = *(int *) (*slot + 0x15c);
            func_ov004_022347b8(self, slot);
            result = 1;
        }
    }
    return result;
}
