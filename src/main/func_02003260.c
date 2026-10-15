/* func_02003260 @ 0x02003260, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define F32(p, o) (*(int *) ((u8 *) (p) + (o)))
#define F16(p, o) (*(unsigned short *) ((u8 *) (p) + (o)))

extern int FX_MulFunc(int a, int b);
extern short FX_SinCosTable_[];

void func_02003260(void *a)
{
    int target;
    int np;

    if (F32(a, 0x98) == 0) {
        target = F32(a, 0xa0);
        np = F32(a, 0xa8) + F32(a, 0x9c);
        if (np >= target) {
            target = np;
        }
        F32(a, 0xa4) = 0;
        F32(a, 0xa8) = target;
        F32(a, 0xac) = 0;
    } else {
        int cos = FX_MulFunc(F32(a, 0x98), FX_SinCosTable_[((F16(a, 0x94) >> 4) << 1) + 1]);
        target = F32(a, 0xa0);
        np = F32(a, 0xa8) + F32(a, 0x9c);
        if (np >= target) {
            target = np;
        }

        F32(a, 0xa4) = FX_MulFunc(F32(a, 0x98), FX_SinCosTable_[(F16(a, 0x94) >> 4) << 1]);
        F32(a, 0xa8) = target;
        F32(a, 0xac) = cos;
    }
}
