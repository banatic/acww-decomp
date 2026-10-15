/* func_ov111_022a05b0 @ 0x022a05b0, 0x2c bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov111_022a100819func_ov111_022a05b0Ev
 */

#include "cpp/ov111/Obj_ov111_022a1008.h"

extern "C" int func_ov002_02209f64(void *);
extern "C" unsigned char *func_ov002_02208098(void *object, unsigned char value);

void Obj_ov111_022a1008::func_ov111_022a05b0()
{
    void *r0 = (void *) this;
    void *r4 = r0;
    if (func_ov002_02209f64((char *) r4 + 0x3d38) == 0) {
        func_ov002_02208098((void *) (r4), *(unsigned char *) ((char *) r4 + 0x98));
        ((Obj_ov111_022a1008 *) r4)->func_ov111_022a0bcc();
    }
}
