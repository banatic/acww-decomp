/* field_actor_states_14: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200acd4 @ 0x0200acd4, 0x50 bytes, Thumb
 * func_0200acb0 @ 0x0200acb0, 0x22 bytes, Thumb
 * func_0200ac8c @ 0x0200ac8c, 0x22 bytes, Thumb
 * func_0200ab44 @ 0x0200ab44, 0x148 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} SrcType;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
    unsigned char unk_04;
} DstType;

typedef struct Other Other;

struct Other {
    u8 pad_00[0xc];
    u16 unk_0C;
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
};

typedef struct Sub7D4 Sub7D4;

struct Sub7D4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
};

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200ad78(void *, void *, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020778b0(unsigned char *addr, void *arg2);
extern unsigned short func_02077898(const unsigned char *);
extern void func_0204f794(void *, u8, u8);
extern int func_0204bcdc(void *);
extern u32 func_0204bc64(u16 *);
extern u16 *func_0204f5a8(void *, void *, int);
extern void func_020109a0(void *, int, int, unsigned short);
extern int func_0200fbe0(void *);
extern void func_0205eae0(void *, int, int, int);
extern int func_02073908(void *, u32);
extern void func_02035684(int, int, int);
extern unsigned int *func_0200f27c(void *, int);
extern void *data_021c80bc;
extern void *data_020ccf94;

int func_0200acd4(void *a1, int *a2, int a3, int a4, int a5, short a6)
{
    int a4_save = a4;
    int copy[2];
    char buf1[12];
    char buf2[20];
    int res;

    func_0200e92c(buf1);
    func_0200e90c(buf1, 0x1a, a5, a6);
    copy[0] = a2[0];
    copy[1] = a2[1];
    func_0200ad78(buf2, copy, a3, a4_save);
    res = func_0200e894(a1, buf1);
    func_0200e91c(buf1);
    return res;
}

void func_0200acb0(DstType *dst, SrcType *src, void *arg2, unsigned char arg3)
{
    dst->unk_03 = (unsigned char) src->unk_00;
    dst->unk_04 = (unsigned char) src->unk_04;
    func_020778b0(&dst->unk_01, arg2);
    dst->unk_00 = arg3;
}

void func_0200ac8c(const unsigned char *src, unsigned int *dst, unsigned short *dst2, unsigned char *dst3)
{
    dst[0] = src[3];
    dst[1] = src[4];
    *dst2 = func_02077898(src + 1);
    *dst3 = src[0];
}

void func_0200ab44(void *self, Other *other, int previous)
{
    u8 *p = (u8 *) other + 0xc;
    u8 r4 = p[2];
    u8 r6 = p[3];
    struct {
        u16 lo, hi;
    } hw;
    u8 r7;
    Sub7D4 *sub;
    int result;
    u32 s[2];
    u16 w2;

    hw.lo = other->unk_0C;
    r7 = p[4];

    sub = (Sub7D4 *) ((char *) self + 0x7d4);
    sub->unk_01 = 0;
    sub->unk_02 = r4;
    sub->unk_03 = r6;
    sub->unk_00 = r7;

    func_0204f794((char *) self + 0x824, r4, r6);

    *(u32 *) ((char *) self + 0x830) = 0x1000;
    *(u32 *) ((char *) self + 0x834) = 0x1000;
    *(u32 *) ((char *) self + 0x838) = 0x1000;

    if (func_0204bcdc(&hw) != 0) {
        hw.hi = 0xfff1;
        if (func_0204bc64(&hw.lo) == func_0204bc64(&hw.hi)) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        if (hw.lo == 0xfff1) {
            result = 1;
        } else {
            result = 0;
        }
    }

    if (result != 0) {
        *(u16 *) ((char *) self + 0x822) = *func_0204f5a8(data_021c80bc, (char *) self + 0x824, 0);
        *(u16 *) ((char *) self + 0x820) = *(u16 *) ((char *) self + 0x822);
    } else {
        *(u16 *) ((char *) self + 0x822) = hw.lo;
        *(u16 *) ((char *) self + 0x820) = *(u16 *) ((char *) self + 0x822);
    }

    w2 = *(u16 *) ((char *) self + 0x820);
    s[0] = r4;
    s[1] = r6;
    func_0200acb0((DstType *) ((char *) self + 0x8f0), (SrcType *) s, (void *) w2, (u8) r7);

    func_020109a0(self, 0x17, 3, 0);

    if (func_0200fbe0(self) == 4) {
        func_0205eae0((char *) self + 0x5a0, 0xd, 3, 1);
    }

    if (func_02073908(data_020ccf94, *(u32 *) ((char *) self + 0x800)) != 0) {
        func_02035684(0x12, 0xf, 0);
    }

    func_0200f27c(self, 0x1c);
}
