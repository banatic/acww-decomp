/* func_ov123_0229b7b8 @ 0x0229b7b8, 0x2c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov123_0229d02419func_ov123_0229b7b8Ev
 */

#include "cpp/ov123/Obj_ov123_0229d024.h"

extern "C" int func_ov002_02209f64(void *ptr);
extern "C" void func_ov002_02208098(void *ptr, unsigned char byte);

typedef struct {
    char pad_00[0xa0];
    unsigned char byte_at_a0;
    char pad_A1[0x1cc - 0xa0 - 1];
    int field_at_1cc;
} UnkStruct_0229b7b8;

void Obj_ov123_0229d024::func_ov123_0229b7b8()
{
    UnkStruct_0229b7b8 *self = (UnkStruct_0229b7b8 *) this;
    if (func_ov002_02209f64(&self->field_at_1cc)) {
        return;
    }
    func_ov002_02208098(self, self->byte_at_a0);
    ((Obj_ov123_0229d024 *) self)->func_ov123_0229c54c();
}
