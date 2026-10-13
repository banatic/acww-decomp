/* func_ov004_02238598 @ 0x02238598, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02238598;
typedef void (UnkStruct_02238598::*PMF)(void);
struct UnkStruct_02238598 {};
struct UnkStruct_02238598_2 {
    PMF fn;
};

extern "C" {
extern UnkStruct_02238598_2 data_ov004_02259444[];
}

extern "C" void func_ov004_02238598(UnkStruct_02238598 *self)
{
    int *p;
    (self->*(data_ov004_02259444[*(u8 *) ((char *) self + 0x20e)].fn))();
    p = (int *) ((char *) self + 0x158);
    *p = *p + 1;
}
