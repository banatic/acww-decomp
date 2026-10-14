/* func_ov068_02272114 @ 0x02272114, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov068_0227775019func_ov068_02272114Ev
 */

#include "cpp/ov068/Obj_ov068_02277750.h"

typedef struct UnkStruct_02272114 {
    char pad_00[0x13c];
    int unk_13C;
    char pad_140[0x1d8 - 0x13c - 4];
    int unk_1D8;
    char pad_1DC[0x238 - 0x1d8 - 4];
    int unk_238;
} UnkStruct_02272114;

extern "C" void func_ov009_02262ed4(void *ptr, int value);
extern "C" int func_02056f94(void *ptr);
extern "C" void func_ov068_02272be4(UnkStruct_02272114 *self);
extern "C" void func_02055124(void *ptr);

void Obj_ov068_02277750::func_ov068_02272114()
{
    UnkStruct_02272114 *self = (UnkStruct_02272114 *) this;
    func_ov009_02262ed4(&self->unk_238, 0x889);
    if (func_02056f94(&self->unk_1D8) != 0) {
        ((Obj_ov068_02277750 *) self)->func_ov068_02272a7c(0x10);
    }
    func_ov068_02272be4(self);
    func_02055124(&self->unk_13C);
}
