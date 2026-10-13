/* func_ov003_0222bd40 @ 0x0222bd40, 0xc8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222bd40;
typedef void (UnkStruct_0222bd40::*PMF)(void);
extern PMF data_ov003_0225f160[];

extern "C" {

int func_ov003_0222a16c(UnkStruct_0222bd40 *self);
short func_ov003_0222791c(int a, int b);

void func_ov003_0222bd40(UnkStruct_0222bd40 *self)
{
    int r;
    *(int *) ((char *) self + 0x120) = *(int *) ((char *) self + 0x12c);
    *(int *) ((char *) self + 0x124) = *(int *) ((char *) self + 0x130);
    *(int *) ((char *) self + 0x128) = *(int *) ((char *) self + 0x134);
    (self->*data_ov003_0225f160[*(u8 *) ((char *) self + 0x200)])();
    r = func_ov003_0222a16c(self);
    if (r != 0 && r != 5) {
        if (*(u8 *) ((char *) self + 0x1fc) == 0) {
            *(short *) ((char *) self + 0x138) += 0x2aa8;
        } else {
            *(short *) ((char *) self + 0x138) = func_ov003_0222791c(0, 0xaaa);
        }
        *(u8 *) ((char *) self + 0x201) = 0;
    } else {
        *(u8 *) ((char *) self + 0x201) += 1;
    }
    *(int *) ((char *) self + 0x13c) += 2;
}
}
