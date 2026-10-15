/* func_ov003_0222b744 @ 0x0222b744, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222b744;
typedef int (UnkStruct_0222b744::*PMF)(void);

extern PMF data_ov003_0225f190[];

extern "C" {

int func_ov003_0222a784(UnkStruct_0222b744 *self);

void func_ov003_0222b744(UnkStruct_0222b744 *self)
{
    if ((self->*data_ov003_0225f190[*(unsigned char *) ((char *) self + 0x224)])() == 0) {
        func_ov003_0222a784(self);
    }
    *(int *) ((char *) self + 0x13c) += 1;
}
}
