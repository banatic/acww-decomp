/* func_ov132_0229b27c @ 0x0229b27c, 0x28 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov132_0229b99019func_ov132_0229b27cEv
 */

#include "cpp/ov132/Obj_ov132_0229b990.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" int func_ov002_02208098(void *, unsigned char);

void Obj_ov132_0229b990::func_ov132_0229b27c()
{
    void *r0 = (void *) this;
    void *r4 = r0;
    if (func_ov002_02209f64((char *) r0 + 0x94) == 0) {
        func_ov002_02208098(r4, *(unsigned char *) ((char *) r4 + 0x1503));
        ((Obj_ov132_0229b990 *) r4)->func_ov132_0229b6c0();
    }
}
