/* clock_setter: 5 functions, module ov134
 * mwccarm 1.2/base -O4,s
 * func_ov134_0229bed4 @ 0x0229bed4, 0x88 bytes, Thumb
 * func_ov134_0229beb0 @ 0x0229beb0, 0x24 bytes, Thumb
 * func_ov134_0229bd38 @ 0x0229bd38, 0x176 bytes, Thumb
 * func_ov134_0229bd2c @ 0x0229bd2c, 0xc bytes, Thumb
 * func_ov134_0229bcf0 @ 0x0229bcf0, 0x3c bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x18];
    char sub18[0xa0];
    int zeros[8];
    char subD8[0x804 - 0xd8];
    char unk_804;
    char pad_805[0x828 - 0x805];
    char unk_828;
    char pad_829[0x84c - 0x829];
    char unk_84C;
} UnkStruct_0229bed4;

extern void *func_ov002_0220a5fc(void *p);
extern void *func_020b9cfc(void *p);
extern void __cxa_vec_ctor(void *p, int a, int b, void (*cb1)(void *), void (*cb2)(void *));
extern int **func_02070be8(void *unused0);
extern void *func_02070c08(void *unused0);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_ov002_0220a5e4(void *);
extern void func_ov002_0220a580(void *);
extern void func_ov134_022995b0(void *, int);
extern void func_0209e474(void *);
extern void func_0209e29c(void *, int);
extern void MI_CpuCopy8(void *, void *, int);
extern void func_0209e268(void *, int);
extern void func_ov134_0229af60(void *);
extern void func_ov134_0229b6b4(void *unused0);
extern void func_0200277c(unsigned char);
extern void func_020b9ccc(void *);

#define VisitElement_02070c08 (void (*)(void *)) func_02070c08
#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov134_0229bed4(UnkStruct_0229bed4 *self)
{
    func_ov002_0220a5fc(self->sub18);
    self->zeros[0] = 0;
    self->zeros[1] = 0;
    self->zeros[2] = 0;
    self->zeros[3] = 0;
    self->zeros[4] = 0;
    self->zeros[5] = 0;
    self->zeros[6] = 0;
    self->zeros[7] = 0;
    __cxa_vec_ctor(self->subD8, 0x11, 0x6c, VisitElement_02070c08, VisitElement_02070be8);
    func_020b9cfc(&self->unk_804);
    func_020b9cfc(&self->unk_828);
    func_020b9cfc(&self->unk_84C);
    return self;
}

#undef VisitElement_02070c08
#undef VisitElement_02070be8

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

char *func_ov134_0229beb0(char *obj)
{
    __cxa_vec_cleanup(obj + 0xd8, 0x11, 0x6c, VisitElement_02070be8);
    func_ov002_0220a5e4(obj + 0x18);
    return obj;
}

#undef VisitElement_02070be8

void func_ov134_0229bd38(void *arg0, int p1, int p2, int p3, u8 p4)
{
    char *r4 = (char *) arg0;

    *(u16 *) (r4 + 0x90) = 0;
    *(u8 *) (r4 + 0xb7) = 0;
    *(u8 *) (r4 + 0xa0) = (u8) p1;
    *(u8 *) (r4 + 0x98) = 0;

    switch (*(u8 *) (r4 + 0xa0)) {
        case 0:
        case 1:
            *(u8 *) (r4 + 0xa1) = 0;
            break;
        case 2:
            *(u8 *) (r4 + 0xa1) = 1;
            break;
        case 3:
            *(u8 *) (r4 + 0xa1) = 2;
            break;
    }

    *(u8 *) (r4 + 0xa2) = (u8) p2;
    *(u8 *) (r4 + 0xa3) = (u8) p3;
    *(u8 *) (r4 + 0xa4) = p4;

    *(int *) (r4 + 0x70) = 0;
    *(int *) (r4 + 0x74) = 0;
    *(int *) (r4 + 0x78) = 0;

    func_ov002_0220a580(r4 + 0x18);

    *(int *) (r4 + 4) = 0;

    switch (*(u8 *) (r4 + 0xa0)) {
        case 0:
        case 3:
            *(u8 *) (r4 + 0xb1) = 0;
            break;
        case 1:
            *(u8 *) (r4 + 0xb1) = 3;
            func_ov134_022995b0(r4, 0x40);
            func_ov134_022995b0(r4, 0x80);
            break;
        case 2:
            *(u8 *) (r4 + 0xb1) = 1;
            break;
    }

    if (*(u8 *) (r4 + 0xa0) == 2) {
        *(int *) (r4 + 0xb8) = 0;
        *(int *) (r4 + 0xbc) = 0;
        *(u8 *) (r4 + 0xbd) = 1;
        *(u8 *) (r4 + 0xbc) = 1;
        *(u8 *) (r4 + 0xbb) = 1;
    } else {
        func_0209e474(r4 + 0xb8);
        *(u8 *) (r4 + 0xb8) = 0;

        if (*(u8 *) (r4 + 0xa0) == 3) {
            func_0209e29c(r4 + 0xb8, 1);
        }

        MI_CpuCopy8(r4 + 0xb8, r4 + 0xc8, 8);
        MI_CpuCopy8(r4 + 0xb8, r4 + 0xd0, 8);
        func_0209e268(r4 + 0xd0, 0xc);

        *(u8 *) (r4 + 0xb2) = *(u8 *) (r4 + 0xca);
        *(u8 *) (r4 + 0xb3) = *(u8 *) (r4 + 0xd2);
        *(u8 *) (r4 + 0xb4) = *(u8 *) (r4 + 0xc9);

        func_ov134_0229af60(r4);
    }
}

void func_ov134_0229bd2c(int p0)
{
    func_ov134_022995b0((void *) p0, 128);
}

void func_ov134_0229bcf0(void *self)
{
    func_ov134_0229b6b4(self);
    func_0200277c(*(unsigned char *) ((char *) self + 0xa4));
    func_020b9ccc((char *) self + 0x804);
    func_020b9ccc((char *) self + 0x828);
    func_020b9ccc((char *) self + 0x84c);
}
