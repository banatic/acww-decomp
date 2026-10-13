/* func_ov003_022273f8 @ 0x022273f8, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 *p;
    u8 kind;
    u8 pad_05;
    u16 count;
} UnkStruct_022273f8;

extern UnkStruct_022273f8 data_ov003_02236b0c[];

u8 *func_ov003_022273f8(u16 *pv)
{
    u8 *r;
    u16 v;
    int hi;
    UnkStruct_022273f8 *e;
    int lo;

    r = 0;
    if (pv != 0) {
        v = *pv;
        hi = (v & 0xf000) >> 12;
        lo = v & 0xfff;
        e = data_ov003_02236b0c;
        while (e->p != 0) {
            if (hi == e->kind) {
                if (e->count > lo) {
                    r = e->p + 3 * lo;
                }
                break;
            }
            e++;
        }
        if (r != 0 && *r == 0) {
            r = 0;
        }
    }
    return r;
}
