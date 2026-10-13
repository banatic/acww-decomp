/* func_ov004_02229fb8 @ 0x02229fb8, 0x1c0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Prefix {
    u8 bytes[0xec];
};
struct Embedded {
    u8 bytes[0x44];
};
struct Actor : Prefix, Embedded {};

// Local of the talk-start sequence (as in func_ov004_02211720); its inline destructor
// keeps the 8-byte frame slot although the object folds away.
struct D {
    int a, b;
    ~D() {}
};

extern "C" {
#define W(p, o) (*(int *) ((p) + (o)))
#define P(p, o) (*(u8 **) ((p) + (o)))
extern int func_0200dc8c(void *), func_02008258(void *, int), func_020b2300(void), func_0200dc10(void *), func_020b67d4(void),
    func_0203e1c4(void), func_0203e19c(void);
extern int func_0200d4e8(void *, int, int, int);
extern void func_ov004_02229bb4(void *, int, int), func_ov004_02229d24(void *, int, int);
extern int func_ov004_02229eac(void *, int, int, int);
extern void func_0203ee14(void *, void *), func_0203ee08(void *, void *), func_0200f27c(void *, int),
    func_0200f268(void *, int), func_020a8164(void *, void *);
extern u8 data_ov004_02254b00[];
void func_ov004_02229fb8(u8 *self)
{
    u8 *flags = self + 0x7d4;
    u8 *phase = flags + 1;
    switch (*phase) {
        case 0:
            if (!flags[0] && func_0200dc8c(self) < 0x333) {
                flags[0] = 1;
            }
            if (!self[0x141]) {
                W(self, 0x7fc) = func_02008258(self, W(self, 0x7f0));
                func_0200d4e8(self, 3, 1, -1);
            } else if (func_0200dc8c(self) > 0x333) {
                if ((unsigned int) func_020b2300() <= 1) {
                    W(self, 0x7fc) = func_02008258(self, W(self, 0x7f0));
                    switch (func_0200dc10(self)) {
                        case 2:
                            func_ov004_02229bb4(self, 6, -1);
                            break;
                        case 0:
                            func_ov004_02229d24(self, 6, -1);
                            break;
                        case 3:
                            if (flags[0]) {
                                if (!func_ov004_02229eac(self, 1, 6, -1)) {
                                    flags[0] = 0;
                                }
                            }
                            break;
                        case 1:
                            if (flags[0]) {
                                if (!func_ov004_02229eac(self, 0, 6, -1)) {
                                    flags[0] = 0;
                                }
                            }
                            break;
                    }
                } else if (func_020b67d4() && !W(self, 0x800)) {
                    ++*phase;
                }
            }
            break;
        case 1:
            if (func_0203e1c4()) {
                D t;
                ++*phase;
                func_0203ee14(self, (Embedded *) (Actor *) self);
                func_0200f27c(self, 0x11);
                func_020a8164(self + 0xec, data_ov004_02254b00);
                self[0x10a] = 1;
                W(P(self, 0x12c), 8) = 1;
            }
            break;
        case 2:
            if (P(self, 0x12c) && W(P(self, 0x12c), 4)) {
                ++*phase;
            }
            break;
        case 3:
            if (P(self, 0x12c) && !W(P(self, 0x12c), 4)) {
                func_0203ee08(self, (Embedded *) (Actor *) self);
                func_0200f268(self, 0x11);
                func_0203e19c();
                *phase = 0;
            }
            break;
    }
}
}
