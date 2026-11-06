/* room_object_anims_2: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022107d4 @ 0x022107d4, 0x48 bytes, Thumb
 * func_ov004_0221078c @ 0x0221078c, 0x48 bytes, Thumb
 * func_ov004_02210744 @ 0x02210744, 0x48 bytes, Thumb
 * func_ov004_022106fc @ 0x022106fc, 0x48 bytes, Thumb
 * func_ov004_0221062c @ 0x0221062c, 0xd0 bytes, Thumb
 * func_ov004_0221041c @ 0x0221041c, 0x210 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0221062c {
    int unk_00;
    u16 unk_04;
};

extern int func_ov004_0220e5c8(void *self);
extern int func_ov004_0223a760(int x);
extern u16 data_ov004_0224fd38;
extern void func_ov004_0223cf40(void *p, int v, void *q);
extern int func_ov004_0223a750(int x);
extern void func_ov004_0223cf54(void *p, int v, void *q);
extern int func_ov004_0223a740(int x);
extern int func_ov004_0223a730(int x);
extern void *func_ov004_0220e220(void *p);
extern struct UnkStruct_0221062c *func_ov004_0220da04(void *p, int i);
extern struct UnkStruct_0221062c *func_ov004_0220d9f8(void *p, int i);
extern struct UnkStruct_0221062c *func_ov004_0220d9e0(void *p, int i);
extern struct UnkStruct_0221062c *func_ov004_0220d9d4(void *p, int i);
extern struct UnkStruct_0221062c *func_ov004_0220d9ec(void *p, int i);
extern void *func_ov004_0220ffa4(char *);
extern void *func_ov004_0220e050(void *);
extern int func_0209d324(void *);
extern int func_020564d0(void *, void *, int);
extern int func_0205650c(void *, void *, int);
extern int func_02055140(void *, int);
extern void func_02056478(void *, void *, u8, int, u16);
extern void func_02056424(void *, void *, void *, u8, int, u16);
extern void func_02055060(void *, void *, int, int, u16, u16);
extern void func_02055050(void *);
extern void *func_02055e00(void *);
extern void func_020563dc(void *, void *);

int func_ov004_022107d4(char *self)
{
    if (!func_ov004_0220e5c8(self)) {
        int v = func_ov004_0223a760(*(int *) (self + 0x284));
        if (v != data_ov004_0224fd38) {
            func_ov004_0223cf40(self + 0x798, v, self + 0x7b8);
            return 1;
        }
    }
    return 0;
}

int func_ov004_0221078c(char *self)
{
    if (!func_ov004_0220e5c8(self)) {
        int v = func_ov004_0223a750(*(int *) (self + 0x284));
        if (v != data_ov004_0224fd38) {
            func_ov004_0223cf54(self + 0x798, v, self + 0x7b8);
            return 1;
        }
    }
    return 0;
}

int func_ov004_02210744(char *self)
{
    if (!func_ov004_0220e5c8(self)) {
        int v = func_ov004_0223a740(*(int *) (self + 0x284));
        if (v != data_ov004_0224fd38) {
            func_ov004_0223cf54(self + 0x798, v, self + 0x7b8);
            return 1;
        }
    }
    return 0;
}

int func_ov004_022106fc(char *self)
{
    if (!func_ov004_0220e5c8(self)) {
        int v = func_ov004_0223a730(*(int *) (self + 0x284));
        if (v != data_ov004_0224fd38) {
            func_ov004_0223cf54(self + 0x798, v, self + 0x7b8);
            return 1;
        }
    }
    return 0;
}

u16 func_ov004_0221062c(char *self, int k)
{
    int i;

    i = k & 1;
    if (func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        return func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), i)->unk_04;
    }
    if (func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        return func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), i)->unk_04;
    }
    if (func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        return func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), i)->unk_04;
    }
    if (func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        return func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), i)->unk_04;
    }
    if (func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        return func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), i)->unk_04;
    }
    return 0;
}

void func_ov004_0221041c(char *self, int selector, u8 mode, int speed, u16 frame)
{
    void *context = func_ov004_0220ffa4(self);
    int slot = selector & 1;
    if ((void *) func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), slot)) {
        void *resource = *(void **) (self + 0x594);
        if (func_020564d0(self + 0x824, resource, func_0209d324(context))) {
            func_02056478(self + 0x824, (void *) func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), slot), mode, speed,
                          frame);
            func_020563dc(self + 0x824, func_02055e00(self + 0x538));
        }
    }
    if ((void *) func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), slot)) {
        void *resource = *(void **) (self + 0x594);
        if (func_0205650c(self + 0x7c4, resource, func_0209d324(context))) {
            func_02056478(self + 0x7c4, (void *) func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), slot), mode, speed,
                          frame);
            func_020563dc(self + 0x7c4, func_02055e00(self + 0x538));
        }
    }
    if ((void *) func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), slot)) {
        void *resource = *(void **) (self + 0x594);
        if (func_0205650c(self + 0x7e4, resource, func_0209d324(context))) {
            func_02056478(self + 0x7e4, (void *) func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), slot), mode, speed,
                          frame);
            func_020563dc(self + 0x7e4, func_02055e00(self + 0x538));
        }
    }
    if ((void *) func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), slot)) {
        void *resource = *(void **) (self + 0x594);
        if (func_0205650c(self + 0x804, resource, func_0209d324(context))) {
            void *res = (void *) func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), slot);
            func_02056424(self + 0x804, res, func_ov004_0220e050(self + 0x6cc), mode, speed, frame);
            func_020563dc(self + 0x804, func_02055e00(self + 0x538));
        }
    }
    if ((void *) func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), slot)) {
        if (func_02055140(self + 0x538, func_0209d324(context))) {
            func_02055060(self + 0x538, (void *) func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), slot), mode, speed,
                          frame, 0);
            func_02055050(self + 0x538);
        }
    }
}
