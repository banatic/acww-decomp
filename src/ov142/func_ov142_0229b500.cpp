/* func_ov142_0229b500 @ 0x0229b500, 0x26 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov142_0229c3e819func_ov142_0229b500Ev
 */

#include "cpp/ov142/Obj_ov142_0229c3e8.h"

typedef struct UnkStruct_0229b500 {
    unsigned char pad_00[0xba];
    unsigned char unk_BA;
    unsigned char pad_BB[0xe8 - 0xbb];
    unsigned char unk_E8;
} UnkStruct_0229b500;

extern "C" int func_ov002_02209f64(unsigned char *ptr);
extern "C" void func_ov002_02208098(UnkStruct_0229b500 *p, unsigned char b);

void Obj_ov142_0229c3e8::func_ov142_0229b500()
{
    UnkStruct_0229b500 *p = (UnkStruct_0229b500 *) this;
    if (func_ov002_02209f64(&p->unk_E8) == 0) {
        func_ov002_02208098(p, p->unk_BA);
        ((Obj_ov142_0229c3e8 *) p)->func_ov142_0229bd90();
    }
}
