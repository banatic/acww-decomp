/* func_ov101_0229d2fc @ 0x0229d2fc, 0x50 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov101_0229e07819func_ov101_0229d2fcEv
 */

#include "cpp/ov101/Obj_ov101_0229e078.h"

extern "C" int func_ov002_02209f64(const void *ptr);
extern "C" unsigned char *func_ov002_02208098(const void *ptr, unsigned char val);
extern "C" void func_ov101_0229cb60(const void *ptr, unsigned char val);
extern "C" void func_ov101_0229ca00(const void *ptr);

void Obj_ov101_0229e078::func_ov101_0229d2fc()
{
    void *p = (void *) this;
    if (func_ov002_02209f64((char *) p + 0x229c) == 0) {
        func_ov002_02208098(p, *(unsigned char *) ((char *) p + 0xb6));
        if ((unsigned char) (*(unsigned char *) ((char *) p + 0xb6) + 0xfa) <= 1) {
            func_ov101_0229cb60(p, *(unsigned char *) ((char *) p + 0xb3));
        }
        ((Obj_ov101_0229e078 *) p)->func_ov101_0229dbb0();
    }
    func_ov101_0229ca00(p);
}
