/* pockets_room: 5 functions, module ov097
 * mwccarm 1.2/base -O4,s
 * func_ov097_022a29e4 @ 0x022a29e4, 0x90 bytes, Thumb
 * func_ov097_022a2954 @ 0x022a2954, 0x90 bytes, Thumb
 * func_ov097_022a28e4 @ 0x022a28e4, 0x70 bytes, Thumb
 * func_ov097_022a27fc @ 0x022a27fc, 0xe8 bytes, Thumb
 * func_ov097_022a27c0 @ 0x022a27c0, 0x3c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_022a27c0 {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
} UnkStruct_022a27c0;

typedef struct UnkStruct_022a27fc {
    unsigned char pad_00[0xb6];
    u8 unk_B6;
    unsigned char pad_B7[0xc4 - 0xb7];
    int unk_C4;
} UnkStruct_022a27fc;

extern UnkStruct_022a27c0 *data_020ccf94;

extern int func_02073d90(UnkStruct_022a27c0 *p);
extern unsigned int func_020b2300(void);
extern void func_02061b1c(unsigned short *out, unsigned short *in, int flag);
extern int func_0204bcdc(unsigned short *ptr);
extern int func_ov004_0223b540(int *out, unsigned short *in, int flag);
extern void func_0200467c(int cmd);
extern int func_020435fc(int value, unsigned short param);
extern int func_ov004_0223c660(int value);
extern int func_ov002_02208d4c(void *p, int a, int b);
extern u16 *func_02034b80(void *p, int a, int b, int c);
extern u16 *func_02034b04(void *p, int a, int b, int c);
extern void func_ov096_0229fb9c(UnkStruct_022a27fc *self);
extern void func_ov096_0229f874(UnkStruct_022a27fc *self, int a, int b, int c);
extern unsigned short func_ov096_0229f0dc(UnkStruct_022a27fc *self, int idx);
extern void func_ov096_0229c414(UnkStruct_022a27fc *self);
extern void func_ov096_0229f5e0(UnkStruct_022a27fc *self, int idx, int v, int z);
extern void func_ov096_0229f5ac(UnkStruct_022a27fc *self, int idx);

int func_ov097_022a27c0(void *self);

static __inline u16 Get(const u16 *p)
{
    return *p;
}

void func_ov097_022a29e4(UnkStruct_022a27fc *self)
{
    u16 v[2];
    u16 x;
    int idx;
    u32 ok;

    if (func_ov097_022a27c0(self) == 0) {
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 0x17, 0xff, 1);
    } else {
        idx = self->unk_B6;
        v[0] = (u16) func_ov096_0229f0dc(self, idx);
        func_ov096_0229c414(self);
        v[1] = *func_02034b04(v, 0, 1, 1);
        ok = 0;
        x = Get(&v[1]);
        if (v[1] >= 0x1144 && x <= 0x1187) {
            ok = 1;
        }
        if (ok > 0) {
            func_ov096_0229f5e0(self, idx, x, 0);
        } else {
            func_ov096_0229f5ac(self, idx);
        }
        func_ov096_0229fb9c(self);
    }
}

void func_ov097_022a2954(UnkStruct_022a27fc *self)
{
    u16 v[2];
    u16 x;
    int idx;
    u32 ok;

    if (func_ov097_022a27c0(self) == 0) {
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 0x18, 0xff, 1);
    } else {
        idx = self->unk_B6;
        v[0] = (u16) func_ov096_0229f0dc(self, idx);
        func_ov096_0229c414(self);
        v[1] = *func_02034b80(v, 0, 1, 1);
        ok = 0;
        x = Get(&v[1]);
        if (v[1] >= 0x1100 && x <= 0x1143) {
            ok = 1;
        }
        if (ok > 0) {
            func_ov096_0229f5e0(self, idx, x, 0);
        } else {
            func_ov096_0229f5ac(self, idx);
        }
        func_ov096_0229fb9c(self);
    }
}

void func_ov097_022a28e4(u8 *self, u16 arg)
{
    volatile u16 id;

    if (func_ov097_022a27c0(self) == 0) {
        return;
    }
    id = arg;
    {
        unsigned int ok = 0;
        u16 hi = id;
        u16 lo = id;
        if (lo >= 0x1144 && hi <= 0x1187) {
            ok = 1;
        }
        if (ok > 0) {
            func_ov002_02208d4c(self + 0x294c, 0xc, 0x13);
        } else if (hi >= 0x1100 && hi <= 0x1143) {
            func_ov002_02208d4c(self + 0x294c, 0xb, 0x12);
        }
    }
}

int func_ov097_022a27fc(UnkStruct_022a27fc *self, unsigned short param2)
{
    unsigned short a = param2;
    unsigned short b;
    int c;

    func_02061b1c(&b, &a, 0);
    if (func_0204bcdc(&b) != 0) {
        int code = func_ov004_0223b540(&c, &b, 1);
        switch (code) {
            case 0:
                func_ov096_0229fb9c(self);
                func_ov096_0229f874(self, 3, 0xff, 0);
                func_0200467c(0x73);
                return 0;
            case 1:
                func_ov096_0229fb9c(self);
                func_ov096_0229f874(self, 5, 0xff, 1);
                func_0200467c(0x73);
                return 0;
            case 2:
                func_ov096_0229fb9c(self);
                func_ov096_0229f874(self, 3, 0xff, 0);
                func_0200467c(0x73);
                return 0;
            default:
                func_ov004_0223c660(c);
                goto ret_1;
        }
    } else {
        int ret = func_020435fc(data_020ccf94->unk_64, param2);
        self->unk_C4 = ret;
        if (self->unk_C4 == -1) {
            func_ov096_0229fb9c(self);
            func_ov096_0229f874(self, 3, 0xff, 0);
            func_0200467c(0x73);
            return 0;
        } else {
            return 2;
        }
    }
ret_1:
    return 1;
}

int func_ov097_022a27c0(void *self)
{
    UnkStruct_022a27c0 *p = data_020ccf94;
    if (func_02073d90(p)) {
        if (p->unk_64 == 0 && func_020b2300() <= 1) {
            goto ret1;
        }
        return 0;
    }
    if (func_020b2300() <= 1) {
        goto ret1;
    }
    return 0;
ret1:
    return 1;
}
