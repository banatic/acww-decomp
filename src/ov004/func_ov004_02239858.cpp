/* func_ov004_02239858 @ 0x02239858, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02239858 {
    int a;
    ~UnkStruct_02239858() {}
};

extern "C" {
extern int func_02056f28(void *, unsigned);
extern int func_ov004_02239804(void *);
}
extern "C" int func_ov004_02239858(char *self)
{
    UnkStruct_02239858 t;
    int r = 0;
    if (*(u8 *) (self + 0x1c6) != 0) {
        if (*(u8 *) (self + 0x22e) != 0) {
            if (func_02056f28(self + 0x100, (unsigned) (*(int *) (self + 0x104) << 4) >> 16) != 0) {
                func_ov004_02239804(self);
                r = 1;
            }
        }
    }
    return r;
}
