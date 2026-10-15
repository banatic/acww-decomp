/* func_ov119_0229bfdc @ 0x0229bfdc, 0x2c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov119_0229cea019func_ov119_0229bfdcEv
 */

#include "cpp/ov119/Obj_ov119_0229cea0.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" unsigned char *func_ov002_02208098(void *, unsigned char);

void Obj_ov119_0229cea0::func_ov119_0229bfdc()
{
    void *arg = (void *) this;
    if (!func_ov002_02209f64((char *) arg + 0xda8)) {
        func_ov002_02208098(arg, *(unsigned char *) ((char *) arg + 0x9f));
        ((Obj_ov119_0229cea0 *) arg)->func_ov119_0229c75c();
    }
}
