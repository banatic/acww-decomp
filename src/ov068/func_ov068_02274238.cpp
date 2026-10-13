/* func_ov068_02274238 @ 0x02274238, 0xbc bytes, Thumb, module ov068
 * mwccarm 1.2/base -O2,s
 */

#include "types.h"

class UnkStruct_02274238 {
  public:
    u8 unk_00[0x1e];
    u8 unk_1E;
    u8 p1[0x40 - 0x1f];
    int unk_40;
};

typedef void (UnkStruct_02274238::*PMF)(int);
extern PMF data_ov068_02277a1c, data_ov068_02277a44, data_ov068_02277a4c, data_ov068_022779c4, data_ov068_022779dc;

struct UnkStruct_02274238_2 {
    int key;
    PMF pmf;
};

extern "C" int func_0206837c(int);
extern "C" int func_020ab504(int);

extern "C" void func_ov068_02274238(UnkStruct_02274238 *self)
{
    static UnkStruct_02274238_2 tbl[5] = {{1, data_ov068_02277a1c},
                                          {2, data_ov068_02277a44},
                                          {3, data_ov068_02277a4c},
                                          {5, data_ov068_022779c4},
                                          {0xe, data_ov068_022779dc}};
    unsigned int i;
    int a;
    u8 *k;
    int key;

    i = 0;
    k = &self->unk_1E;
    for (; i < 5; i++) {
        key = ((UnkStruct_02274238_2 *) ((char *) tbl + i * 12))->key;
        if (key == *k) {
            a = func_020ab504(func_0206837c(self->unk_40));
            (self->*((UnkStruct_02274238_2 *) ((int) tbl + i * 12))->pmf)(a);
        }
    }
}
