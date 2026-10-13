/* func_020bb8e0 @ 0x020bb8e0, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    int x;
    int y;
};

struct Big {
    u32 unk_00;
    unsigned char pad0[0x1208];
    u32 unk_120C;
    unsigned char pad_1210[0x310];
    u32 unk_1520;
    unsigned char pad_1524[0x8];
    s32 unk_152C;
    u32 unk_1530;
    unsigned char pad_1534[0x8];
    u16 unk_153C;
    u16 unk_153E;
    unsigned char pad_1540[0x30];
    u32 unk_1570;
    u32 unk_1574;
    u32 unk_1578;
    unsigned char pad_157C[0x10];
    u32 unk_158C;
};

extern struct Global8 {
    unsigned char pad0[5];
    unsigned char flag;
} data_021f3b28;

extern int func_020bb6b0(struct Big *self, int a);
extern void func_020bb7e0(struct Big *self, int a, int b);
extern int func_020644cc(int a);
extern void func_0209e474(struct Pair *p);
extern int func_020bb1d4(struct Big *self, struct Pair *p);
extern void func_0209e100(struct Pair *p, int n);
extern int func_020bb214(struct Big *self, struct Pair *p);

void func_020bb8e0(struct Big *self)
{
    int ret;
    struct Pair stack;

    ret = func_020bb6b0(self, 0);
    switch (ret) {
        case 3:
        case 4:
            data_021f3b28.flag = 1;
            break;
        default:
            break;
    }
    func_020bb7e0(self, ret, ret);
    self->unk_00 = 1;
    self->unk_158C = 0;
    self->unk_152C = -1;
    self->unk_1530 = 2;
    self->unk_1574 = func_020644cc(2);
    self->unk_1570 = self->unk_1574;
    self->unk_1520 = 0;
    self->unk_1578 = 0;
    self->unk_120C = 0;
    stack.x = 0;
    stack.y = 0;
    func_0209e474(&stack);
    self->unk_153E = (u16) func_020bb1d4(self, &stack);
    func_0209e100(&stack, 6);
    self->unk_153C = (u16) func_020bb214(self, &stack);
}
