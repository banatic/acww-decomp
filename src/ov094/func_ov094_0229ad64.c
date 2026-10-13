/* func_ov094_0229ad64 @ 0x0229ad64, 0xac bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229ad64 UnkStruct_0229ad64;
typedef struct UnkStruct_0229ad64_2 UnkStruct_0229ad64_2;
struct UnkStruct_0229ad64 {
    u8 unk_00[0x184];
    u8 unk_184[0xa38 - 0x184];
    u8 unk_A38[4];
};
struct UnkStruct_0229ad64_2 {
    int unk_00;
    unsigned int b0 : 10;
    unsigned int b10 : 2;
    unsigned int b12 : 4;
    unsigned int b16 : 16;
};
extern void func_ov094_0229a34c(u8 *, int);
extern void func_ov094_0229a36c(u8 *, int);
extern int func_ov094_0229acb0(UnkStruct_0229ad64 *, u16 *, int);
extern UnkStruct_0229ad64_2 *func_ov094_0229a524(UnkStruct_0229ad64 *, int);
extern int func_ov094_0229b088(u8 *, int);
extern int func_ov094_0229b03c(u8 *, int);
extern void func_02002a88(int, int, int, int, int);

void func_ov094_0229ad64(UnkStruct_0229ad64 *self, int a, u16 *p2, int c)
{
    UnkStruct_0229ad64_2 *e;
    int idx;
    int t;
    int res;

    if (*p2 == 0xfff1) {
        func_ov094_0229a34c(self->unk_A38, a);
        return;
    }
    func_ov094_0229a36c(self->unk_A38, a);
    idx = func_ov094_0229acb0(self, p2, c);
    e = func_ov094_0229a524(self, a);
    t = e->b0;
    res = func_ov094_0229b088(self->unk_184, idx);
    func_02002a88(res, 8, t, t, t + 1);
    t += 0x20;
    func_02002a88(res + 0x400, 8, t, t, t + 1);
    e->b12 = func_ov094_0229b03c(self->unk_184, idx);
}
