/* func_ov004_0220f52c @ 0x0220f52c, 0x2a8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define W(p, o) (*(int *) ((char *) (p) + (o)))
#define B(p, o) (*(u8 *) ((char *) (p) + (o)))
#define S(p, o) (*(short *) ((char *) (p) + (o)))
extern "C" {
int func_ov004_0220e5c8(char *);
void func_0204f7ac(void *, int, int, int, int);
int func_ov004_0223c5a4(void *);
void func_020eaca0(void *, void *, void *);
int func_020ea838(void *);
int FX_MulFunc(int, int);
short func_020e8ed8(int, int);
u16 func_0204bc50(int, int);
u8 func_020b65c4(void);
int func_02053de4(int);
int func_02053dac(int);
int func_02053be0(int);
int func_02053d60(int);
int func_02053d24(int);
int func_020538dc(int);
int func_0205389c(int);
int func_0205395c(int);
int func_02053818(int);
int func_ov004_0220d45c(void *, int, int, int);
void func_ov004_0220fb90(char *);
void func_ov004_0220d318(void *, char *);
void func_ov004_0220ef14(char *, int, int, int, int);
int func_ov004_0220f7d4(char *);
void func_ov004_0220f9c8(char *);
extern int data_021c67b8[], data_021c67d0[];
extern u16 data_ov004_02256c40, data_ov004_02256c3c;
}
// Empty destructors retain the ROM's temporary materialization.
struct Vec {
    int x, y, z;
    Vec() {}
    ~Vec() {}
    Vec(int a, int b, int c) : x(a), y(b), z(c) {}
};
extern "C" void func_ov004_0220f52c(char *self)
{
    // Eight bytes are reserved for this local view; only the first word is used.
    union Packed {
        u32 word;
        u32 storage[2];
        struct {
            u32 x : 4, z : 4, index : 16, direction : 2, mode : 2, raised : 1, rest : 3;
        } field;
        ~Packed() {}
    } bits;
    // Preserve the otherwise unused halfword write at 0220f64a.
    volatile u16 item;
    if (B(self, 0x289) != 0) {
        return;
    }
    bits.word = *(u32 *) (self + 8);
    if (!func_ov004_0220e5c8(self)) {
        func_0204f7ac(self + 0x5c, 0, 0, bits.field.x, bits.field.z);
        W(self, 0x60) = func_ov004_0223c5a4(self + 0x5c);
        W(self, 0x150) = 0x1000;
        W(self, 0x154) = 0x1000;
        W(self, 0x158) = 0x1000;
        W(self, 0x15c) = 0x1000;
    } else {
        Vec a(data_021c67b8[0], data_021c67b8[1], data_021c67b8[2]);
        Vec b(data_021c67d0[0], data_021c67d0[1], data_021c67d0[2]);
        Vec diff;
        func_020eaca0(&diff, &b, &a);
        func_020ea838(&diff);
        Vec scaled(FX_MulFunc(diff.x, 0x4000), FX_MulFunc(diff.y, 0x4000), FX_MulFunc(diff.z, 0x4000));
        W(self, 0x5c) = a.x + scaled.x;
        W(self, 0x60) = a.y + scaled.y;
        W(self, 0x64) = a.z + scaled.z;
        W(self, 0x150) = 0x400;
        W(self, 0x154) = 0x400;
        W(self, 0x158) = 0x400;
        W(self, 0x15c) = 0x1000;
        data_ov004_02256c40 = func_020e8ed8(diff.z, diff.y) - 0xb000;
        data_ov004_02256c3c = func_020e8ed8(diff.x, diff.z) + 0x8000;
    }
    S(self, 0x8e) = bits.field.direction << 14;
    W(self, 0x284) = bits.field.index;
    if (W(self, 0x284) >= 0x6e9) {
        W(self, 0x284) = 0x6e8;
    }
    item = func_0204bc50(W(self, 0x284), 0);
    B(self, 0x288) = bits.field.raised;
    if (!func_ov004_0220e5c8(self) && B(self, 0x288) == 0) {
        W(self, 0x60) = 0;
        if (func_020b65c4() == 10) {
            W(self, 0x60) = func_ov004_0223c5a4(self + 0x5c);
        }
    }
    W(self, 0x780) = func_02053de4(W(self, 0x284));
    W(self, 0x790) = func_02053dac(W(self, 0x284));
    W(self, 0x784) = func_02053be0(W(self, 0x284));
    W(self, 0x774) = func_02053d60(W(self, 0x284));
    W(self, 0x778) = func_02053d24(W(self, 0x284));
    B(self, 0x78c) = func_020538dc(W(self, 0x284));
    B(self, 0x78d) = func_0205389c(W(self, 0x284));
    W(self, 0x788) = func_0205395c(W(self, 0x284));
    W(self, 0x794) = func_02053818(W(self, 0x284));
    if (!func_ov004_0220e5c8(self)) {
        if (W(self, 0x784) == 2) {
            W(self, 0x5c) += 0x1000;
            W(self, 0x64) += 0x1000;
        }
        if (B(self, 0x288) == 1) {
            func_ov004_0220d45c(self + 0x17c, bits.field.x, bits.field.z, S(self, 0x8e));
        }
    }
    func_ov004_0220fb90(self);
    func_ov004_0220d318(self + 0x740, self);
    func_ov004_0220ef14(self, 1, 0, 0, 0);
    func_ov004_0220f7d4(self);
    func_ov004_0220f9c8(self);
    B(self, 0x289) = 1;
}
