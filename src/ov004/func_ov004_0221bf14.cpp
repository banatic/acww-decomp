/* func_ov004_0221bf14 @ 0x0221bf14, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/sp2 -O4,s
 * compiler-emitted symbol: _ZThn236_N18Obj_ov004_022533e017vfunc_02066994_18Ev
 */

#include "types.h"
#include "cpp/ov004/Obj_ov004_022533e0.h"

extern "C" {
typedef struct {
    char unk_00, unk_01, unk_02, unk_03;
    u16 unk_04;
} UnkStruct_0221b60c;

extern int func_ov004_0221b98c(char *self);
extern void func_0206837c(int a);
extern int func_020ab504(void);
extern unsigned int func_ov004_0221b9f4(char *self);
extern int func_020712b0(void *a, u16 *b);
extern void func_0206844c(void *a, char *b, int c);
extern int data_021f38f8;
extern u8 data_021f43e8;
}

Obj_ov004_022533e0::~Obj_ov004_022533e0() {}

void Obj_ov004_022533e0::vfunc_02066994_18()
{
    char *self = (char *) this;

    UnkStruct_0221b60c s;
    unsigned int k;

    if (func_ov004_0221b98c(self) != 0) {
        return;
    }
    func_0206837c(*(int *) (self + 0x12c));
    if (func_020ab504() == 0) {
        s.unk_04 = (*(u16 **) (self + 0x164))[(u8) self[0x155]];
        if (*(unsigned int *) (self + 0x15c) <= 1) {
            k = func_ov004_0221b9f4(self);
            if (k > 3) {
                k = 3;
            }
            s.unk_00 = (char) ((k - 1) % 3 + 5);
            func_0206844c(*(void **) (self + 0x12c), &s.unk_00, 0);
        } else if (func_020712b0(&data_021f38f8, &s.unk_04) != 2) {
            s.unk_01 = 1;
            func_0206844c(*(void **) (self + 0x12c), &s.unk_01, 0);
        } else {
            s.unk_02 = 2;
            func_0206844c(*(void **) (self + 0x12c), &s.unk_02, 0);
        }
    } else {
        s.unk_03 = data_021f43e8;
        func_0206844c(*(void **) (self + 0x12c), &s.unk_03, 0);
    }
}
