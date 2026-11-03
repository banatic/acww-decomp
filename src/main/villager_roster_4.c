/* villager_roster_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207d080 @ 0x0207d080, 0x70 bytes, Thumb
 * func_0207d03c @ 0x0207d03c, 0x44 bytes, Thumb
 * func_0207cf80 @ 0x0207cf80, 0xbc bytes, Thumb
 */

#include "types.h"

typedef struct Unk0x7EC {
    u8 data[0x7ec];
} Unk0x7EC;

typedef struct UnkStruct_0207cf80 {
    Unk0x7EC arr[8];  // 0x000
    char objA[0x1c];  // 0x3f60
    char objB[0x14];  // 0x3f7c
    char objC[0xbc];  // 0x3f90
    u8 flag1;         // 0x404c
    u8 flag2;         // 0x404d
    u8 flag3;         // 0x404e
    u8 flag4;         // 0x404f
    u32 word1;        // 0x4050
    u32 word2;        // 0x4054
    u32 word3;        // 0x4058
    u32 word4;        // 0x405c
    char buf[20];     // 0x4060
    signed char neg2; // 0x4074
    signed char neg1; // 0x4075
    u8 pad_4076[2];   // 0x4076
    char small[2];    // 0x4078
} UnkStruct_0207cf80;

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_02081710(void *);
extern void *func_020817a8(void *);
extern void func_02079cc0(void *);
extern void func_0207a338(void *);
extern void *func_0209a814(void *);
extern void *func_0209a7e8(void *);
extern void func_0207a334(void *);
extern void func_02079cbc(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02081660(void *p);
extern void func_02079cb0(void *p);
extern void func_0207a318(void *p);
extern void func_0209a77c(void *p);
extern void MI_CpuFill8(void *p, int v, int len);

void *func_0207d080(void *self)
{
    __cxa_vec_ctor((void *) (self), 8, 0x7ec, (((void (*)(void *)) func_020817a8)), (((void (*)(void *)) func_02081710)));
    func_02079cc0((char *) self + 0x3f60);
    func_0207a338((char *) self + 0x3f7c);
    func_0209a814((char *) self + 0x3f90);
    *(unsigned int *) ((char *) self + 0x4050) = 0;
    *(unsigned int *) ((char *) self + 0x4054) = 0;
    *(unsigned int *) ((char *) self + 0x4058) = 0;
    *(unsigned int *) ((char *) self + 0x405c) = 0;
    return self;
}

void *func_0207d03c(void *p)
{
    func_0209a7e8((char *) p + 0x3f90);
    func_0207a334((char *) p + 0x3f7c);
    func_02079cbc((char *) p + 0x3f60);
    __cxa_vec_cleanup((void *) (p), 8, 0x7ec, (((void (*)(void *)) func_02081710)));
    return p;
}

void func_0207cf80(UnkStruct_0207cf80 *self)
{
    int i;

    for (i = 0; i < 8; i++) {
        func_02081660(&self->arr[i]);
    }

    func_02079cb0(self->objA);
    func_0207a318(self->objB);
    func_0209a77c(self->objC);

    self->flag1 = 1;
    self->flag2 = 1;
    self->flag3 = 0;
    self->flag4 = 0;
    self->word1 = 0;
    self->word2 = 0;
    self->word3 = 0;
    self->word4 = 0;

    self->neg1 = -1;
    self->neg2 = -1;

    MI_CpuFill8(self->small, 0, 2);
    MI_CpuFill8(self->buf, 0, 20);
}
