/* func_ov009_02263694 @ 0x02263694, 0x82 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc19func_ov009_02263694Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

extern "C" int func_ov009_0226321c(void *, int *, short *);
extern "C" int *func_02095794(int);
extern "C" int func_ov003_02219ad0(int *, int *, short *);
extern "C" int func_ov009_02264c90(void *);
extern "C" int func_ov003_02219a64(unsigned int, int *, int *, int);

int Obj_ov009_022658dc::func_ov009_02263694()
{
    short b;
    int v;
    int out[3];

    if (func_ov009_0226321c(this, out, &b) != 0) {
        v = out[0];
        if (vfunc_94() == 0) {
            int *p = func_02095794(4);
            if (p != 0) {
                v = *p;
            }
        }
        if (vfunc_90() != 0) {
            if (func_ov003_02219ad0(&v, &out[2], &b) != 0) {
                return 1;
            }
        } else if (func_ov003_02219a64(func_ov009_02264c90(this) == 2, &v, &out[2], b) != 0) {
            return 1;
        }
    }
    return 0;
}
