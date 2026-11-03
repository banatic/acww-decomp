/* trash_box: 14 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222f5cc @ 0x0222f5cc, 0x24 bytes, Thumb
 * func_ov004_0222f5c8 @ 0x0222f5c8, 0x4 bytes, Thumb
 * func_ov004_0222f590 @ 0x0222f590, 0x38 bytes, Thumb
 * func_ov004_0222f584 @ 0x0222f584, 0xc bytes, Thumb
 * func_ov004_0222f568 @ 0x0222f568, 0x1c bytes, Thumb
 * func_ov004_0222f54c @ 0x0222f54c, 0x1a bytes, Thumb
 * func_ov004_0222f524 @ 0x0222f524, 0x28 bytes, Thumb
 * func_ov004_0222f518 @ 0x0222f518, 0xc bytes, Thumb
 * func_ov004_0222f4fc @ 0x0222f4fc, 0x1c bytes, Thumb
 * func_ov004_0222f4f8 @ 0x0222f4f8, 0x2 bytes, Thumb
 * func_ov004_0222f4e4 @ 0x0222f4e4, 0x14 bytes, Thumb
 * func_ov004_0222f4e0 @ 0x0222f4e0, 0x2 bytes, Thumb
 * func_ov004_0222f484 @ 0x0222f484, 0x5c bytes, Thumb
 * func_ov004_0222f474 @ 0x0222f474, 0x10 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0222f5cc;

struct UnkStruct_0222f5cc_2;

struct UnkStruct_0222f5cc {
    int pad_00;
    void *unk_04;
};

struct UnkStruct_0222f5cc_2 {
    char pad_00[720];
    struct UnkStruct_0222f5cc *b;
};

extern void func_0203ee08(void *self, void *a);
extern int func_ov004_0222f6e8(void *self, int k);
extern int func_0209d3f8(int a, int b);
extern int func_0206fbf8(int k);
extern int data_021c8c9c;
extern int func_0206fbc0(void);
extern int func_0203e020(void *);
extern void *data_021c526c;
extern int func_020321bc(void *, int, int, int, void *, int, int);
extern int func_020b6590(void);
extern int func_020b7dc8(int, void *, void *, int, int, int, int, int, int);
extern int func_02032180(void *);

void func_ov004_0222f5cc(struct UnkStruct_0222f5cc_2 *self)
{
    struct UnkStruct_0222f5cc *b;
    b = self->b;
    if (b != 0) {
        if (b->unk_04 != 0) {
            func_ov004_0222f6e8((void *) self, 2);
        }
    }
}

int func_ov004_0222f5c8(void *callbackObject)
{
    return 1;
}

void func_ov004_0222f590(unsigned char *self)
{
    unsigned char *a, *p;
    p = *(unsigned char **) (self + 0x2d0);
    if (p != 0 && *(int *) (p + 4) == 0) {
        a = self;
        if (self != 0) {
            a = self + 0x290;
        }
        func_0203ee08(self, a);
        func_ov004_0222f6e8(self, 3);
    }
}

int func_ov004_0222f584(int arg)
{
    return func_0209d3f8(arg, 1);
}

void func_ov004_0222f568(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x24c) == 0x2) {
        func_ov004_0222f6e8(self, 0x4);
    }
}

int func_ov004_0222f54c(void *callbackObject)
{
    if (func_0206fbf8(0x20) != 0) {
        return 1;
    }
    return 0;
}

void func_ov004_0222f524(char *self)
{
    if (data_021c8c9c == 0 && func_0206fbc0() != 0) {
        func_ov004_0222f6e8((void *) self, 5);
    }
}

int func_ov004_0222f518(int a)
{
    return func_0209d3f8(a, 3);
}

void func_ov004_0222f4fc(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x24c) == 0x0) {
        func_0203e020(self);
    }
}

void func_ov004_0222f4f8(void *object) {}

void func_ov004_0222f4e4(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) ((char *) *(int *) ((char *) &data_021c526c) + 0x248) = 0x1a;
}

void func_ov004_0222f4e0(void *object) {}

int func_ov004_0222f484(char *self)
{
    // DECLS
    // ENDDECLS
    return func_020b7dc8(
        ((void) (func_020321bc(self + 0x2d8, 0x2000, 0x4000, 0x2000, self + 0x5c, 0x0, 0x0)), func_020b6590()), self + 0x374,
        self + 0x5c, 0x2000, 0x4000, 0x2000, 0x0, 0xc, 0xff);
}

int func_ov004_0222f474(char *self)
{
    // DECLS
    // ENDDECLS
    return func_02032180(self + 0x2d8);
}
