/* room_player_actor: 13 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222c070 @ 0x0222c070, 0x46 bytes, Thumb
 * func_ov004_0222c030 @ 0x0222c030, 0x3e bytes, Thumb
 * func_ov004_0222c00c @ 0x0222c00c, 0x24 bytes, Thumb
 * func_ov004_0222bfb4 @ 0x0222bfb4, 0x58 bytes, Thumb
 * func_ov004_0222bf74 @ 0x0222bf74, 0x3e bytes, Thumb
 * func_ov004_0222bf50 @ 0x0222bf50, 0x22 bytes, Thumb
 * func_ov004_0222bf20 @ 0x0222bf20, 0x2e bytes, Thumb
 * func_ov004_0222befc @ 0x0222befc, 0x22 bytes, Thumb
 * func_ov004_0222bed8 @ 0x0222bed8, 0x22 bytes, Thumb
 * func_ov004_0222beb4 @ 0x0222beb4, 0x24 bytes, Thumb
 * func_ov004_0222be7c @ 0x0222be7c, 0x38 bytes, Thumb
 * func_ov004_0222be58 @ 0x0222be58, 0x22 bytes, Thumb
 * func_ov004_0222be34 @ 0x0222be34, 0x24 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0222bfb4 {
    int x, y, z;
};

struct UnkStruct_0222be7c {
    unsigned char pad_00[0x7f0];
    unsigned int unk_7F0;
    unsigned char pad_7F4[8];
    unsigned int unk_7FC;
};

extern int func_ov004_02228850(void *p, int a, int b);
extern int func_ov004_02228b14(void *p, int a, int b);
extern int func_ov004_02228be0(void *p, int a, int b);
extern int func_ov004_02228628(void *p, int a, int b, int c, int d, int e, int f);
extern int func_02096718(int argument0);
extern int func_ov004_022282c0(int argument0, int argument1, int argument2, int argument3);
extern int func_ov004_0222683c(void *p, struct UnkStruct_0222bfb4 *v, int k, int m);
extern int func_ov004_02227e94(void *p, int k, int m);
extern void *func_ov004_02228100(void *, int, int, unsigned char, int, int, int, int);
extern int func_ov004_02227fe4(int, int, int);
extern int func_ov004_02227324(void *argument0, int argument1, int argument2, int argument3, short argument4);
extern int func_ov004_02226fa4(int, int, int);
extern int func_ov004_02226dfc(int, int, int);
extern int func_ov004_02228dfc(void *argument0, unsigned short argument1, void *argument2, void *argument3);
extern struct UnkStruct_0222be7c; // unused
extern unsigned int func_02008258(struct UnkStruct_0222be7c *ptr, unsigned int val);
extern int func_ov004_0222acf0(struct UnkStruct_0222be7c *ptr, int a, int b);
extern int func_ov004_02226d14(int, int, int);
extern void func_020109a0(int a, int b, int c, unsigned short d);

int func_ov004_0222c070(int k)
{
    void *p = (void *) func_02096718(4);
    if (p != 0) {
        switch (k) {
            case 0:
                func_ov004_02228850(p, 6, -1);
                break;
            case 1:
                func_ov004_02228b14(p, 6, -1);
                break;
            case 2:
                func_ov004_02228be0(p, 6, -1);
                break;
        }
    }
    return 0;
}

int func_ov004_0222c030(int *a, int *b, int *c, short *d)
{
    void *p = (void *) func_02096718(4);

    if (p != 0) {
        return func_ov004_02228628(p, (unsigned char) *a, *b, *c, *d, 6, -1);
    }
    return 0;
}

int func_ov004_0222c00c(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02096718(0x4);
    if (v1 != 0x0) {
        return func_ov004_022282c0(v1, *(int *) (self), 0x6, -0x1);
    }
    return 0x0;
}

int func_ov004_0222bfb4(void)
{
    char *p = (char *) func_02096718(4);

    if (p != 0) {
        if (*(int *) (p + 0x808) == 4) {
            struct UnkStruct_0222bfb4 v;
            struct UnkStruct_0222bfb4 *q = (struct UnkStruct_0222bfb4 *) (p + 0x5c);
            v.x = *(int *) (p + 0x5c);
            v.y = q->y;
            v.z = q->z;
            v.z = v.z + 0x6000;
            return func_ov004_0222683c(p, &v, 6, -1);
        }
        return func_ov004_02227e94(p, 6, -1);
    }
    return 0;
}

void *func_ov004_0222bf74(int a, int *b, unsigned char *c, int *d, int e)
{
    void *ptr;

    ptr = (void *) func_02096718(4);
    if (ptr != 0) {
        return func_ov004_02228100(ptr, a, *b, *c, *d, e, 6, -1);
    }
    return 0;
}

int func_ov004_0222bf50(void)
{
    int r;

    r = func_02096718(4);
    if (r != 0) {
        return func_ov004_02227fe4(r, 6, -1);
    }
    return 0;
}

int func_ov004_0222bf20(char *self, char *a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02096718((int) ((int) (0x4)));
    if (v1 != 0x0) {
        return func_ov004_02227324((void *) (v1), (int) (*(u8 *) (self)), (int) (*(u8 *) (a1)), (int) (0x6), (short) (-0x1));
    }
    return 0x0;
}

int func_ov004_0222befc(void)
{
    int r;

    r = func_02096718(4);
    if (r != 0) {
        return func_ov004_02226fa4(r, 6, -1);
    }
    return 0;
}

int func_ov004_0222bed8(void)
{
    int r;

    r = func_02096718(4);
    if (r != 0) {
        return func_ov004_02226dfc(r, 6, -1);
    }
    return 0;
}

int func_ov004_0222beb4(void)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02096718(0x4);
    if (v1 != 0x0) {
        return func_ov004_02228dfc((void *) (v1), (unsigned short) (0xa), (void *) (0x6), (void *) (-0x1));
    }
    return 0x0;
}

int func_ov004_0222be7c(void)
{
    struct UnkStruct_0222be7c *p = (struct UnkStruct_0222be7c *) func_02096718(4);
    if (p != 0) {
        p->unk_7FC = func_02008258(p, p->unk_7F0);
        return func_ov004_0222acf0(p, 5, -1);
    } else {
        return 0;
    }
}

int func_ov004_0222be58(void)
{
    int r;

    r = func_02096718(4);
    if (r != 0) {
        return func_ov004_02226d14(r, 6, -1);
    }
    return 0;
}

int func_ov004_0222be34(void)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02096718(0x4);
    if (v1 != 0x0) {
        func_020109a0(v1, 0x98, 0x0, 0x0);
        return 0x1;
    }
    return 0x0;
}
