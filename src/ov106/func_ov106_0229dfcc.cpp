/* func_ov106_0229dfcc @ 0x0229dfcc, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov106_0229f6e019func_ov106_0229dfccEv
 */

#include "cpp/ov106/Obj_ov106_0229f6e0.h"

extern "C" int func_ov002_02209f64(void *p);
extern "C" void func_ov002_02208098(void *p, unsigned char b);
extern "C" void func_ov106_0229d028(void *p, unsigned char b);
extern "C" void func_ov106_0229ce0c(void *p);

void Obj_ov106_0229f6e0::func_ov106_0229dfcc()
{
    void *p = (void *) this;
    unsigned char *b = (unsigned char *) p;
    if (func_ov002_02209f64(b + 0x22a0) == 0) {
        func_ov002_02208098(p, b[0xbb]);
        if (b[0xbb] == 7) {
            func_ov106_0229d028(p, b[0xb8]);
        }
        ((Obj_ov106_0229f6e0 *) p)->func_ov106_0229ef8c();
    }
    func_ov106_0229ce0c(p);
}
