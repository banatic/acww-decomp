/* func_ov054_0226194c @ 0x0226194c, 0xb4 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 a;
    u32 b;
    u32 c;
} TblEntry;
extern TblEntry data_ov054_02262fac[];
extern u8 data_021ebcd4;
extern u8 data_021dc7a8;

extern int func_0206fc6c(void);
extern int func_02060d3c(void *ptr);
extern void func_02015fb0(void *a, int b, int c, int d, int e, int f);
extern int func_0208602c(void);
extern void func_020860f0(int a, int b);
extern void func_0209f100(void *a, int b);
extern void func_02015330(void *a, void *b, int c, int d, int e);
extern void func_ov054_02261cc4(void *a, int b);
extern void func_020155cc(void *a);
extern void func_0206844c(void *a, void *b, int c);

typedef struct UnkStruct_0226194c UnkStruct_0226194c;
struct UnkStruct_0226194c {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad_44[0x6c];
    void *unk_B0;
};

struct UnkStruct_0226194c_2 {
    u8 unk_00;
    u8 pad_01;
    u16 unk_02;
};

void func_ov054_0226194c(UnkStruct_0226194c *self)
{
    struct UnkStruct_0226194c_2 local;
    int r5;
    void *r6;
    int r7;
    u32 idx;

    r6 = self->unk_40;
    idx = *(u32 *) ((char *) self->unk_B0 + 0x808);
    r7 = (int) data_ov054_02262fac[idx].a;

    if (func_0206fc6c() != 0) {
        r5 = func_02060d3c(&data_021ebcd4);
        func_02015fb0(self, r5, 4, 0xa, 0, 0);
        if (r5 == 0) {
            r5 = 0x15;
            func_020860f0(func_0208602c(), 0);
            func_0209f100(&data_021dc7a8, 0x10);
        } else {
            r5 = 0x14;
        }
        local.unk_02 = 0x149b;
        func_02015330(self, &local.unk_02, 0, 5, 1);
        func_ov054_02261cc4(self, 0xa);
    } else {
        r5 = 0x13;
        func_020155cc(self);
        func_ov054_02261cc4(self, 0);
    }
    local.unk_00 = (u8) r5;
    func_0206844c(r6, &local, r7);
}
