/* func_ov100_0229dc38 @ 0x0229dc38, 0x50 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov100_0229ecb819func_ov100_0229dc38Ev
 */

#include "cpp/ov100/Obj_ov100_0229ecb8.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" void func_ov002_02208098(void *, unsigned char);
extern "C" void func_ov100_0229d068(void *, unsigned char);
extern "C" void func_ov100_0229ce24(void *);

void Obj_ov100_0229ecb8::func_ov100_0229dc38()
{
    void *base = (void *) this;
    if (func_ov002_02209f64((char *) base + 0x2274) == 0) {
        func_ov002_02208098(base, *(unsigned char *) ((char *) base + 0x2924));
        if ((unsigned char) (*(unsigned char *) ((char *) base + 0x2924) + 0xFC) <= 1) {
            func_ov100_0229d068(base, *(unsigned char *) ((char *) base + 0x2921));
        }
        ((Obj_ov100_0229ecb8 *) base)->func_ov100_0229e7cc();
    }
    func_ov100_0229ce24(base);
}
