/* func_ov054_02261878 @ 0x02261878, 0xd4 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206fc6c(void);
extern void func_020984e8(void);
extern void func_020992fc(void);
extern int func_020983f0(void);
extern void func_02015fb0(void *self, int a, int b, int c, int d, int e);
extern int _s32_div_f(int a, int b);
extern void func_02015330(void *self, void *p, int a, int b, int c);
extern void func_020154b4(void *self, void *p, int a, int b, int c);
extern void func_ov054_02261cc4(void *self, int a);
extern void func_020155cc(void *self);
extern void func_0206844c(void *dst, void *src, int data);

typedef struct DataEntry {
    int unk_00;
    char pad[8];
} DataEntry;

extern DataEntry data_ov054_02262fac[];

typedef struct UnkStruct_02261878 {
    char pad[0x808];
    int val;
} UnkStruct_02261878;

typedef struct UnkStruct_02261878_2 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    UnkStruct_02261878 *unk_B0;
    char pad_B4[0xc0 - 0xb4];
    int unk_C0;
} UnkStruct_02261878_2;

typedef struct LocalBuf {
    u8 unk_00;
    u16 b1;
    u16 b2;
} LocalBuf;

void func_ov054_02261878(UnkStruct_02261878_2 *self)
{
    void *tmp;
    int data;
    int val;
    int r6;
    int act;
    LocalBuf buf;

    tmp = self->unk_40;
    val = self->unk_B0->val;
    data = data_ov054_02262fac[val].unk_00;

    if (func_0206fc6c() != 0) {
        func_020984e8();
        func_020992fc();
        r6 = func_020983f0();
        func_02015fb0(self, r6, 5, 10, 0, 0);
        val = _s32_div_f(r6, 0xc8);
        func_02015fb0(self, val, 6, 10, 0, 0);
        act = 0x17;
        if (r6 > self->unk_C0) {
            buf.b1 = 0x149b;
            func_02015330(self, &buf.b1, 0, 5, 1);
        } else {
            buf.b2 = 0x149b;
            func_020154b4(self, &buf.b2, 0, 5, 1);
        }
        func_ov054_02261cc4(self, 10);
    } else {
        act = 0x18;
        func_020155cc(self);
        func_ov054_02261cc4(self, 0);
    }

    buf.unk_00 = (u8) act;
    func_0206844c(tmp, &buf, data);
}
