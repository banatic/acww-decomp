/* func_ov004_02231614 @ 0x02231614, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02231614 {
    int a;
    ~UnkStruct_02231614() {}
};
extern "C" {
extern int func_020ea990(void *, void *);
extern int data_ov004_022478d0;
}
extern "C" int func_ov004_02231614(char *self, char *o)
{
    UnkStruct_02231614 t;
    if (o != 0) {
        if (func_020ea990(o + 0x5c, &data_ov004_022478d0) < 0x2333) {
            u16 d = (u16) (*(s16 *) (o + 0x8e) - (*(s16 *) (self + 0x8e) + 0x8000));
            if (d < 0x1000 || d >= 0xf000) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
