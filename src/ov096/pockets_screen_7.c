/* pockets_screen_7: 5 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229e79c @ 0x0229e79c, 0x26 bytes, Thumb
 * func_ov096_0229e71c @ 0x0229e71c, 0x80 bytes, Thumb
 * func_ov096_0229e6b0 @ 0x0229e6b0, 0x6c bytes, Thumb
 * func_ov096_0229e6a0 @ 0x0229e6a0, 0x10 bytes, Thumb
 * func_ov096_0229e67c @ 0x0229e67c, 0x24 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229e6b0 {
    u8 pad_00[0xac];
    volatile u16 unk_AC;
    u8 unk_AE[2];
    u8 unk_B0;
    u8 unk_B1;
    u8 unk_B2[2];
    u8 unk_B4;
} UnkStruct_0229e6b0;

extern int func_ov096_0229f650(void *arg0, int arg1);
extern int func_ov096_0229f4ac(void *arg0, int arg1);
extern void func_ov096_0229fb9c(void *);
extern void func_ov096_0229f874(void *, int, int, int);
extern void func_ov096_0229e82c(void *, int);
extern int func_ov096_0229da6c(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov096_0229c2dc(void *, int);
extern int func_ov096_0229daec(UnkStruct_0229e6b0 *self, u16 id);
extern void func_0206f848(int);
extern void func_ov096_0229ff54(void *);

int func_ov096_0229e6b0(UnkStruct_0229e6b0 *self);
void func_ov096_0229e6a0(unsigned char *p);

int func_ov096_0229e79c(void *arg0, int arg1)
{
    unsigned char type = *((unsigned char *) arg0 + 0xb1);

    switch (type) {
        case 2:
            return func_ov096_0229f650(arg0, arg1);
        case 1:
            return func_ov096_0229f4ac(arg0, arg1);
        default:
            return 0;
    }
}

int func_ov096_0229e71c(void *param)
{
    if (func_ov096_0229e6b0((UnkStruct_0229e6b0 *) param) == 0) {
        func_ov096_0229fb9c(param);
        func_ov096_0229f874(param, 9, 0xff, 1);
        func_ov096_0229e82c(param, 1);
        return 0;
    } else {
        typedef struct {
            char pad[0xac];
            unsigned short field;
        } UnkStruct_0229e71c;
        unsigned short s = ((UnkStruct_0229e71c *) param)->field;
        int ret = func_ov096_0229da6c(param, s);
        if (ret == 0) {
            func_ov096_0229e82c(param, 1);
            return 0;
        } else if (ret == 1) {
            func_ov096_0229e6a0((unsigned char *) param);
            return 1;
        } else if (ret == 2) {
            func_ov002_02208098((void *) (param), 0x28);
            func_ov096_0229c2dc(param, 0x1000);
            return 0;
        } else {
            func_ov096_0229e82c(param, 1);
            return 0;
        }
    }
}

int func_ov096_0229e6b0(UnkStruct_0229e6b0 *self)
{
    volatile u16 id;

    if (self->unk_B1 != 2) {
        return 0;
    }
    if (self->unk_B0 != 0) {
        return 0;
    }
    id = self->unk_AC;
    {
        unsigned int ok = 0;
        u16 hi = id;
        u16 lo = id;
        if (lo >= 0x1492 && hi <= 0x14fd) {
            ok = 1;
        }
        if (ok > 0) {
            if (self->unk_B4 == 0x25) {
                return 0;
            }
        }
    }
    return func_ov096_0229daec(self, self->unk_AC);
}

void func_ov096_0229e6a0(unsigned char *p)
{
    p[0xb1] = 0;
    func_0206f848(0);
}

void func_ov096_0229e67c(void *p)
{
    func_ov002_02208098((void *) (p), 0x25);
    func_ov096_0229ff54(p);
    func_ov096_0229c2dc(p, 0x8000);
}
