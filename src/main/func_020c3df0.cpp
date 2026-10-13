/* func_020c3df0 @ 0x020c3df0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020c3df0 {
    char pad_00[0x654];
    int idx;
};

typedef int (UnkStruct_020c3df0::*Handler)();

struct UnkStruct_020c3df0_2 {
    char pad_00[8];
    Handler h;
};

extern UnkStruct_020c3df0_2 data_021fbd90[];

extern "C" int func_020c3df0(UnkStruct_020c3df0 *self)
{
    int result = 0;
    if (data_021fbd90[self->idx].h != 0) {
        result = (self->*data_021fbd90[self->idx].h)();
    }
    return result;
}
