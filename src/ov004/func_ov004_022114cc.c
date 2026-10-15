/* func_ov004_022114cc @ 0x022114cc, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022114cc UnkStruct_022114cc;
struct UnkStruct_022114cc {
    void (**vt)(UnkStruct_022114cc *, int, void *);
};
extern void func_ov004_022114a0(char *arg0);
void func_ov004_022114cc(char *self)
{
    UnkStruct_022114cc *o = *(UnkStruct_022114cc **) (*(char **) (self + 4) + 0x2c);
    if (o != 0) {
        o->vt[26](o, *(u8 *) (*(char **) self + 1), self);
    }
    *(void **) (self + 0x24) = (void *) func_ov004_022114a0;
    *(u8 *) (self + 0x92) = 2;
}
