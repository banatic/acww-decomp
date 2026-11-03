/* house_record_2: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206122c @ 0x0206122c, 0x3e bytes, Thumb
 * func_02061220 @ 0x02061220, 0xc bytes, Thumb
 * func_02061204 @ 0x02061204, 0x1c bytes, Thumb
 * func_020611e8 @ 0x020611e8, 0x1c bytes, Thumb
 * func_020611bc @ 0x020611bc, 0x2c bytes, Thumb
 * func_02061194 @ 0x02061194, 0x28 bytes, Thumb
 * func_02061188 @ 0x02061188, 0xc bytes, Thumb
 * func_0206117c @ 0x0206117c, 0xc bytes, Thumb
 * func_02061144 @ 0x02061144, 0x38 bytes, Thumb
 * func_02061118 @ 0x02061118, 0x2c bytes, Thumb
 * func_0206108c @ 0x0206108c, 0x8c bytes, Thumb
 * func_02061008 @ 0x02061008, 0x84 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x448];
    unsigned char pad_448[6];
    unsigned char flag : 1;
} UnkStruct_02061204;

typedef struct {
    char pad_00[0x448];
    unsigned short unk_448;
    char pad_44A[4];
    unsigned char unk_44E;
} UnkStruct_020611bc;

typedef struct OSOwnerInfo {
    u8 language;
    u8 favoriteColor;
    u8 birthday[2];
    u16 nickName[10];
    u16 nickNameLength;
    u16 comment[26];
    u16 commentLength;
} OSOwnerInfo;

typedef struct Flags {
    u32 f0 : 3;
    u32 f1 : 3;
    u32 f2 : 4;
    u32 f3 : 4;
    u32 f4 : 4;
    u32 f5 : 14;
} Flags;

typedef struct Parent {
    u8 pad_00[0x1594];
    u8 unk_1594[9];
    u8 pad_159D[3];
    Flags flags; // offset 0x15a0
} Parent;

extern void *func_0204f86c(int, int);
extern void func_0204f89c(void *);
extern void *func_020614c4(void *buffer);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_02060a94(void *ptr);
extern void *func_02061444(void *);
extern void *func_02061470(void *);
extern void func_02060a90(int arg);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_0206126c(void *p, int idx);
extern void func_02060974(u8 *p);
extern void OS_GetOwnerInfo(OSOwnerInfo *info);
extern int func_0204e414(void);
extern int func_0204f3e4(int, void *, void *, void *, void *, void *, void *, int, int);
extern void func_0204f800(void *, void *, int, int, int, int);
extern int func_0204bae8(int);
extern int func_0204f538(int, void *, int, int, int);

void *func_0206122c(char *base, int argument1)
{
    int *p;
    int i;

    p = (int *) func_0204f86c(1, (int) argument1);
    if (p != 0) {
        if (p != 0) {
            func_0204f89c(p);
        }
    }
    if (p != 0) {
        for (i = 0; i < 2; i++) {
            int *pt = p + i;
            pt[1] = (int) func_020614c4(base + i * 512);
        }
        p[3] = 0;
    }
    return p;
}

int func_02061220(int a)
{
    return a + 0x400;
}

UnkStruct_02061204 *func_02061204(UnkStruct_02061204 *self, int *out)
{
    if (out) {
        *out = self->flag;
    }
    return (UnkStruct_02061204 *) ((char *) self + 0x448);
}

unsigned char *func_020611e8(unsigned char *base, unsigned int *out)
{
    if (out) {
        *out = ((unsigned int) base[0x44e] << 30) >> 31;
    }
    return base + 0x44a;
}

void func_020611bc(UnkStruct_020611bc *base, unsigned short *src, int flag)
{
    unsigned char b;
    base->unk_448 = *src;
    b = base->unk_44E;
    b = (b & ~1) | ((unsigned char) flag & 1);
    base->unk_44E = b;
}

void func_02061194(char *buf, unsigned short *src, int flag)
{
    unsigned char *p;

    *(unsigned short *) (buf + 0x44a) = *src;
    p = (unsigned char *) buf + 0x44e;
    *p = (*p & ~2) | (((unsigned char) flag & 1) << 1);
}

unsigned int func_02061188(unsigned int r0)
{
    return r0 + 0x44c;
}

void func_0206117c(unsigned char *dst, unsigned short *src)
{
    *(unsigned short *) (dst + 0x44c) = *src;
}

void *func_02061144(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 5, 0x450, (((void (*)(void *)) func_02061470)), (((void (*)(void *)) func_02061444)));
    func_02060a94((void *) ((char *) arg + 0x1594));
    return arg;
}

int func_02061118(int arg)
{
    func_02060a90(arg + 0x1594);
    __cxa_vec_cleanup((void *) (arg), 5, 0x450, (((void (*)(void *)) func_02061444)));
    return arg;
}

void func_0206108c(Parent *self)
{
    int i;
    u8 *p;
    OSOwnerInfo info;

    p = (u8 *) self;
    for (i = 0; i < 5; i++) {
        func_0206126c(p, i);
        p += 0x450;
    }
    self->flags.f0 = 0;
    func_02060974((u8 *) self + 0x1594);
    OS_GetOwnerInfo(&info);
    self->flags.f3 = info.favoriteColor;
    self->flags.f2 = self->flags.f3;
    self->flags.f4 = 0;
}

int func_02061008(int arg1)
{
    struct {
        unsigned short x, y, z;
        unsigned int a, b, c, d, e, f;
        unsigned char pad[0x18];
    } s;
    int a0;

    a0 = func_0204e414();
    s.y = 0x5014;
    s.z = 0x501A;

    if (func_0204f3e4(a0, &s.c, &s.d, &s.e, &s.f, &s.y, &s.z, 1, 0) != 0) {
        func_0204f800(&s.a, &s.b, s.c, s.d, s.e, s.f);
        s.x = (unsigned short) func_0204bae8(arg1);
        if (func_0204f538(a0, &s.x, s.a, s.b, 0) != 0) {
            return 1;
        }
    }
    return 0;
}
