/* func_ov105_0229e180 @ 0x0229e180, 0x4c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov105_0229fad019func_ov105_0229e180Ev
 */

#include "cpp/ov105/Obj_ov105_0229fad0.h"

struct UnkStruct_0229e180 {
    char pad_to_2ba[0x2ba];
    unsigned char unk_2BA;
    char pad_between[2];
    unsigned char unk_2BD;
    char pad_to_24a4[0x24a4 - 0x2be];
    char unk_24A4;
};

extern "C" int func_ov002_02209f64(void *p);
extern "C" void func_ov002_02208098(struct UnkStruct_0229e180 *obj, unsigned char b);
extern "C" void func_ov105_0229d3b4(struct UnkStruct_0229e180 *obj, unsigned char b);
extern "C" void func_ov105_0229d17c(struct UnkStruct_0229e180 *obj);

void Obj_ov105_0229fad0::func_ov105_0229e180()
{
    struct UnkStruct_0229e180 *obj = (struct UnkStruct_0229e180 *) this;
    if (func_ov002_02209f64(&obj->unk_24A4) == 0) {
        func_ov002_02208098(obj, obj->unk_2BD);
        if (obj->unk_2BD == 7) {
            func_ov105_0229d3b4(obj, obj->unk_2BA);
        }
        ((Obj_ov105_0229fad0 *) obj)->func_ov105_0229f25c();
    }
    func_ov105_0229d17c(obj);
}
