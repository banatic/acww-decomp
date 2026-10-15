/* func_ov118_0229bb48 @ 0x0229bb48, 0x2c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov118_0229cc0819func_ov118_0229bb48Ev
 */

#include "cpp/ov118/Obj_ov118_0229cc08.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" unsigned char *func_ov002_02208098(void *, unsigned char);

void Obj_ov118_0229cc08::func_ov118_0229bb48()
{
    void *r0 = (void *) this;
    if (func_ov002_02209f64((char *) r0 + 0x6c0) == 0) {
        func_ov002_02208098(r0, *(unsigned char *) ((char *) r0 + 0xab));
        ((Obj_ov118_0229cc08 *) r0)->func_ov118_0229c554();
    }
}
