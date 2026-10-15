/* func_ov119_0229c434 @ 0x0229c434, 0x54 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov119_0229cea019func_ov119_0229c434Ev
 */

#include "cpp/ov119/Obj_ov119_0229cea0.h"

extern "C" int func_ov002_02207f3c(void *p, int x);
extern "C" void func_020027f0(int x);
extern "C" void func_ov119_0229a400(void *p, int x);
extern "C" unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern "C" void func_ov002_02207e80(void *p, int a, int b, int c);
extern "C" int func_ov002_02207f60(void *p);

struct Type {
    char pad_00[0x94];
    int unk_94;
};

void Obj_ov119_0229cea0::func_ov119_0229c434()
{
    struct Type *p = (struct Type *) this;
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov119_0229a400(p, 1);
        func_ov002_022080a0(p, 5);
    } else {
        func_ov002_02207e80(p, 6, 0, 0);
        func_ov002_02207e80(p, 4, 0, 0);
        p->unk_94 = func_ov002_02207f60(p);
    }
}
