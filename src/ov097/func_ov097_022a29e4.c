/* func_ov097_022a29e4 @ 0x022a29e4, 0x90 bytes, Thumb, module ov097
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022a29e4 {
    u8 pad_00[0xb6];
    u8 unk_B6;
} UnkStruct_022a29e4;

extern int func_ov097_022a27c0(void);
extern void func_ov096_0229fb9c(UnkStruct_022a29e4 *self);
extern void func_ov096_0229f874(UnkStruct_022a29e4 *self, int a, int b, int c);
extern unsigned short func_ov096_0229f0dc(UnkStruct_022a29e4 *self, int idx);
extern void func_ov096_0229c414(UnkStruct_022a29e4 *self);
extern u16 *func_02034b04(void *p, int a, int b, int c);
extern void func_ov096_0229f5e0(UnkStruct_022a29e4 *self, int idx, int v, int z);
extern void func_ov096_0229f5ac(UnkStruct_022a29e4 *self, int idx);

static __inline u16 Get(const u16 *p)
{
    return *p;
}

void func_ov097_022a29e4(UnkStruct_022a29e4 *self)
{
    u16 v[2];
    u16 x;
    int idx;
    u32 ok;

    if (func_ov097_022a27c0() == 0) {
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
