/* func_ov104_0229e128 @ 0x0229e128, 0x48 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov104_0229f6d019func_ov104_0229e128Ev
 */

#include "cpp/ov104/Obj_ov104_0229f6d0.h"

extern "C" int func_ov002_02209f64(void *ptr);
extern "C" unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern "C" void func_ov104_0229d748(void *ptr, unsigned char byte);
extern "C" void func_ov104_0229d528(void *ptr);

typedef struct {
    char pad_00[0xb8];
    unsigned char b8;
    char pad_B9[2];
    unsigned char bb;
} UnkStruct_0229e128;

void Obj_ov104_0229f6d0::func_ov104_0229e128()
{
    UnkStruct_0229e128 *p = (UnkStruct_0229e128 *) this;
    if (func_ov002_02209f64((char *) p + 0x24a0) == 0) {
        func_ov002_02208098((void *) (p), p->bb);
        if (p->bb == 7) {
            func_ov104_0229d748(p, p->b8);
        }
        ((Obj_ov104_0229f6d0 *) p)->func_ov104_0229f05c();
    }
    func_ov104_0229d528(p);
}
