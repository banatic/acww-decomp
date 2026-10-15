/* func_0200ab44 @ 0x0200ab44, 0x148 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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

extern void func_0204f794(void *, u8, u8);
extern int func_0204bcdc(void *);
extern u32 func_0204bc64(u16 *);
extern u16 *func_0204f5a8(void *, void *, int);
extern void func_0200acb0(void *, u32 *, u16, u8);
extern void func_020109a0(void *, int, int, unsigned short);
extern int func_0200fbe0(void *);
extern void func_0205eae0(void *, int, int, int);
extern int func_02073908(void *, u32);
extern void func_02035684(int, int, int);
extern unsigned int *func_0200f27c(void *, int);

extern void *data_021c80bc;
extern void *data_020ccf94;

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
    func_0200acb0((char *) self + 0x8f0, s, w2, r7);

    func_020109a0(self, 0x17, 3, 0);

    if (func_0200fbe0(self) == 4) {
        func_0205eae0((char *) self + 0x5a0, 0xd, 3, 1);
    }

    if (func_02073908(data_020ccf94, *(u32 *) ((char *) self + 0x800)) != 0) {
        func_02035684(0x12, 0xf, 0);
    }

    func_0200f27c(self, 0x1c);
}
