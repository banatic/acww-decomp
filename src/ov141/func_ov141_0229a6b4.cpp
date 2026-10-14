/* func_ov141_0229a6b4 @ 0x0229a6b4, 0x30 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov141_0229af4819func_ov141_0229a6b4Ev
 */

#include "cpp/ov141/Obj_ov141_0229af48.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" void func_ov002_02208098(void *, unsigned char);

void Obj_ov141_0229af48::func_ov141_0229a6b4()
{
    void *a = (void *) this;
    if (func_ov002_02209f64((char *) a + 0x0a38) != 0) {
        return;
    }
    func_ov002_02208098(a, *(unsigned char *) ((char *) a + 0x1a7e));
    ((Obj_ov141_0229af48 *) a)->func_ov141_0229abc0();
}
