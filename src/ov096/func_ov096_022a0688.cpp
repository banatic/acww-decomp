/* func_ov096_022a0688 @ 0x022a0688, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov096_022a23e819func_ov096_022a0688Ev
 */

#include "cpp/ov096/Obj_ov096_022a23e8.h"

typedef struct UnkStruct_022a0688 {
    int pad_00;
} UnkStruct_022a0688;

typedef struct UnkStruct_022a0688_2 {
    unsigned char pad_00[0x00b5];
    unsigned char unk_B5;
    unsigned char pad_B6[0x04];
    unsigned char unk_BA;
    unsigned char pad_BB[0x2500 - 0xbb];
    UnkStruct_022a0688 sub;
} UnkStruct_022a0688_2;

extern "C" int func_ov002_02209f64(const UnkStruct_022a0688 *);
extern "C" unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern "C" void func_ov096_0229ed74(UnkStruct_022a0688_2 *, unsigned char);
extern "C" int func_ov096_0229ea5c(UnkStruct_022a0688_2 *);

void Obj_ov096_022a23e8::func_ov096_022a0688()
{
    UnkStruct_022a0688_2 *self = (UnkStruct_022a0688_2 *) this;
    if (func_ov002_02209f64(&self->sub) == 0) {
        func_ov002_02208098((void *) (self), self->unk_BA);
        if ((unsigned char) (self->unk_BA + 0xf6) <= 2) {
            func_ov096_0229ed74(self, self->unk_B5);
        }
        ((Obj_ov096_022a23e8 *) self)->func_ov096_022a1a0c();
    }
    func_ov096_0229ea5c(self);
}
