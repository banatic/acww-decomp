/* missing_npc2_3: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c3950 @ 0x020c3950, 0x118 bytes, Thumb
 * func_020c38d0 @ 0x020c38d0, 0x80 bytes, Thumb
 * func_020c38ac @ 0x020c38ac, 0x24 bytes, Thumb
 * func_020c3838 @ 0x020c3838, 0x74 bytes, Thumb
 * func_020c3814 @ 0x020c3814, 0x24 bytes, Thumb
 * func_020c37f8 @ 0x020c37f8, 0x1c bytes, Thumb
 * func_020c37dc @ 0x020c37dc, 0x1c bytes, Thumb
 * func_020c37d4 @ 0x020c37d4, 0x8 bytes, Thumb
 * func_020c37cc @ 0x020c37cc, 0x8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020c3838 {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
    char pad_68[0x348];
    char unk_3B0;
    char pad_3B1[0x15f];
    char unk_510;
};

extern void *data_020d8c64;
extern void *data_020da088;
extern void *data_020e7ea4;
extern void *func_020edf70(unsigned int);
extern void *func_0203f130(void *);
extern void *func_0205467c(void *);
extern void func_0201b394(void *);
extern void *func_0201a430(void *);
extern int func_020169a8(void *);
extern int func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void *func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void *func_02032c64(void *);
extern void *func_02089c88(void *);
extern void *func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_020c33a4(void *);
extern int func_0202edc8(void *);
extern void func_0201c280(char *, char *);
extern void func_020c3350(char *, char *);
extern int func_020b65c4(void);
extern void func_0201af28(char *, int, int, int, int);
extern void *data_021fbca0;
extern unsigned int *func_0202eb88(void *object);
extern int data_020c8120;
extern int func_0202ec58(struct UnkStruct_020c3838 *self);
extern int func_020984e8(void);
extern void func_020c3690(struct UnkStruct_020c3838 *self, int b);
extern void func_0201ad18(void *p, int a, int b, int c, int d, int e, int f, int g);
extern int data_020c814c;
extern unsigned char data_021fbee8[];
extern int func_0202ec14(void *);
extern int data_020e7df0;
extern int data_020e7dc0;

void *func_020c3950(void)
{
    u8 *p;

    p = (u8 *) func_020edf70(0x714);
    if (p) {
        func_0203f130(p);
        *(void **) p = &data_020d8c64;
        *(u16 *) (p + 0xea) = 0xfff1;
        func_0205467c(p + 0xec);
        func_0201b394(p + 0x2a0);
        func_0201a430(p + 0x2ac);
        func_020169a8(p + 0x334);
        func_0201b324(p + 0x350);
        func_0201af14(p + 0x3a8);
        func_0201b370(p + 0x3aa);
        func_0201adec(p + 0x3b0);
        func_0201a7ec(p + 0x418);
        func_0201a794(p + 0x420);
        func_02032c64(p + 0x49c);
        func_02089c88(p + 0x4cc);
        func_020f55cc(p + 0x514);
        func_02013c2c(p + 0x558);
        func_02019eb0(p + 0x564);
        func_0201489c(p + 0x618);
        *(void **) p = &data_020da088;
        func_02082f60(p + 0x640);
        *(void **) p = &data_020e7ea4;
        func_020c33a4(p + 0x658);
    }
    return p;
}

int func_020c38d0(char *param)
{
    if (func_0202edc8(param) == 0) {
        return 0;
    }
    data_021fbca0 = param;
    func_0201c280(param, param + 0x658);
    func_020c3350(param + 0x658, param);
    if (func_020b65c4()) {
        func_0201af28(param + 0x350, 2, 0x333, 0xcc, 0x133);
        func_0201af28(param + 0x350, 1, 0x280, 0xcc, 0x133);
    }
    param[0x563] = 1;
    return 1;
}

int func_020c38ac(void *param1)
{
    int result;

    if (func_020b65c4() != 0) {

        result = (int) func_0202eb88(param1);
    } else {
        result = data_020c8120;
    }
    return result;
}

int func_020c3838(struct UnkStruct_020c3838 *self)
{
    int a;
    a = func_0202ec58(self);
    if (a == 0) {
        return 0;
    }
    func_020984e8();
    if ((((int) (func_020c3690(self, 0), self)), func_020b65c4()) == 0x2f) {
        self->unk_510 = 0;
        func_0201ad18(&self->unk_3B0, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
        self->unk_5C = 0x10000;
        self->unk_64 = 0x16800;
    }
    return 1;
}

int func_020c3814(void *argument0)
{
    if (func_0202ec14((void *) argument0) == 0) {
        return 0;
    } else {
        (*(int *) &data_021fbca0) = 0;
        return 1;
    }
}

void func_020c37f8(void)
{
    if (data_021fbca0) {
        func_020c3690((struct UnkStruct_020c3838 *) data_021fbca0, 4);
    }
}

void func_020c37dc(void)
{
    if ((*(int *) &data_021fbca0) != 0) {
        func_020c3690((struct UnkStruct_020c3838 *) ((*(int *) &data_021fbca0)), 6);
    }
}

int func_020c37d4(void)
{
    return (int) &data_020e7df0;
}

int func_020c37cc(void)
{
    return (int) &data_020e7dc0;
}
