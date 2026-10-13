/* func_ov004_02237630 @ 0x02237630, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02237630;
typedef void (UnkStruct_02237630::*PMF)(void);
struct UnkStruct_02237630 {};

struct UnkStruct_02237630_2 {
    PMF fn;
};
extern "C" {
extern UnkStruct_02237630_2 data_ov004_0225949c[];
extern void func_ov004_02237454(UnkStruct_02237630 *);
}

extern "C" void func_ov004_02237630(UnkStruct_02237630 *self)
{
    (self->*(data_ov004_0225949c[*(u8 *) ((char *) self + 0x1ee)].fn))();
    func_ov004_02237454(self);
}
