/* func_ov004_02227a00 @ 0x02227a00, 0x1f4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    int mode;
    short heading, pad_06;
    int x, z;
    u8 phase;
} Route;
#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
#define P(p, o) (*(u8 **) ((p) + (o)))
extern "C" {
extern u8 data_021c75b8, data_ov004_02254b00[];
extern void func_ov004_022279a0(void *, int, int), func_ov004_02227794(void *, int, int),
    func_ov004_0222626c(void *, int, int);
extern void *func_020b5e10(void), *func_0209d5e8(void);
extern int func_020b6098(void *, int), func_0209d5f0(int);
extern int func_0209d850(void *), func_0209d848(void *);
extern Vec *func_0209d840(void *);
extern void func_020109a0(void *, int, int, int);
extern void func_0203ee14(void *, void *), func_0203ee08(void *, void *);
extern void func_0200f27c(void *, int), func_0200f268(void *, int), func_020a8164(void *, void *);
extern int func_02008258(void *, int), func_02009a44(void *, Vec *, int, int, int);
}
inline int disabled()
{
    if (data_021c75b8 == 0) {
        return 1;
    } else {
        return 0;
    }
}
inline u8 *base(u8 *self)
{
    u8 *p = self;
    if (p) {
        p += 0xec;
    }
    return p;
}
extern "C" void func_ov004_02227a00(u8 *self)
{
    Route *route = (Route *) (self + 0x7d4);
    u8 *phase = &route->phase;
    if (*phase == 0) {
        Vec *position = (Vec *) (self + 0x5c);
        if (W(self, 0x5c) == route->x && position->z == route->z && route->heading == S(self, 0x8e)) {
            if (route->mode == 1) {
                func_ov004_022279a0(self, 6, -1);
            } else {
                func_ov004_02227794(self, 6, -1);
            }
        }
        if (W(self, 0x704) == 1) {
            return;
        }
        if (W(self, 0x704) == 0x3e && (u16) (W(self, 0x2d8) >> 12) >= 6) {
            func_ov004_0222626c(self, 0, 6);
        }
        if (disabled()) {
            return;
        }
        if ((u16) (W(self, 0x2d8) >> 12) < 5) {
            return;
        }
        func_020b6098(func_020b5e10(), W(self, 0x804));
    } else {
        void *context = func_0209d5e8();
        switch (*phase) {
            case 1:
                if (!func_0209d5f0(W(self, 0x804))) {
                    break;
                }
                ++*phase;
            case 2:
                switch (func_0209d850(context)) {
                    case 0:
                        break;
                    case 2:
                        if (!func_0209d848(context)) {
                            func_020b6098(func_020b5e10(), W(self, 0x804));
                        } else {
                            *phase = 0;
                            func_020109a0(self, 0x3e, 3, 0);
                        }
                        break;
                    case 1:
                        func_0203ee14(self, base(self));
                        func_0200f27c(self, 0x11);
                        func_020a8164(self + 0xec, data_ov004_02254b00);
                        self[0x10a] = 0x15;
                        W(P(self, 0x12c), 8) = 1;
                        ++*phase;
                        break;
                }
                break;
            case 3:
                if (P(self, 0x12c) && W(P(self, 0x12c), 4)) {
                    ++*phase;
                }
                break;
            case 4:
                if (P(self, 0x12c) && !W(P(self, 0x12c), 4)) {
                    struct {
                        int unused;
                        Vec saved, copy;
                    } pair;
                    Vec *src = func_0209d840(context);
                    pair.saved.x = src->x;
                    pair.saved.y = src->y;
                    pair.saved.z = src->z;
                    func_0203ee08(self, base(self));
                    func_0200f268(self, 0x11);
                    W(self, 0x7fc) = func_02008258(self, W(self, 0x7f0));
                    pair.copy.x = pair.saved.x;
                    pair.copy.y = pair.saved.y;
                    pair.copy.z = pair.saved.z;
                    func_02009a44(self, &pair.copy, 0x333, 5, -1);
                }
                break;
        }
    }
}
