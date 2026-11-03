/* aquarium_fish_classes_5: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02238e70 @ 0x02238e70, 0x40 bytes, Thumb
 * func_ov004_02238e08 @ 0x02238e08, 0x68 bytes, Thumb
 * func_ov004_02238d88 @ 0x02238d88, 0x80 bytes, Thumb
 */

#include "types.h"

#define F(k) (*(int *) (self + k))

struct UnkStruct_02238e70 {
    u8 pad_00[0x264];
    u8 mode;
    u8 pad_265[3];
    int ticks;
};

extern void func_ov004_02238d18(struct UnkStruct_02238e70 *self);
extern int func_020e88dc(int *argument0, int argument1, int argument2);

void func_ov004_02238e08(char *self);
void func_ov004_02238d88(char *self);

void func_ov004_02238e70(struct UnkStruct_02238e70 *self)
{
    switch (self->mode) {
        case 0:
            func_ov004_02238e08((char *) self);
            break;
        case 1:
            func_ov004_02238d88((char *) self);
            break;
        case 2:
            func_ov004_02238d18(self);
            break;
    }
    self->ticks++;
}

void func_ov004_02238e08(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x264) = 0x1;
    *(void **) (self + 0x268) = 0x0;
    if (*(u8 *) (self + 0x280) != 0x0) {
        func_020e88dc((int *) (self + 0x278), (int) (0x14), (int) (0x29));
        func_020e88dc((int *) (self + 0x27c), (int) (0xccd), (int) (0xcd));
        *(u8 *) (self + 0x280) = (*(u8 *) (self + 0x280) - 0x1);
    } else {
        *(int *) (self + 0x278) = 0x14;
        *(int *) (self + 0x27c) = 0xccd;
    }
}

void func_ov004_02238d88(char *self)
{
    F(0x258) = F(0x27c) + F(0x278) * F(0x268);
    if (F(0x258) >= 0x1000) {
        F(0x258) = 0x1000;
        F(0x25c) = 0x1000;
        F(0x260) = 0x1000;
        *(u8 *) (self + 0x264) = 2;
        F(0x268) = 0;
        if (*(u8 *) (self + 0x280) == 4) {
            F(0x27c) = 0x99a;
        }
    } else {
        F(0x25c) = F(0x258);
        F(0x260) = F(0x258);
    }
}
