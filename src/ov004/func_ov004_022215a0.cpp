/* func_ov004_022215a0 @ 0x022215a0, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022215a0;

typedef int (UnkStruct_022215a0::*PMF)();

struct GArray1Entry {
    int flag;
    int pad[3];
};

struct GArray2Entry {
    int pad[2];
    PMF pmf;
};

extern GArray1Entry data_ov004_02257e98[];
extern GArray2Entry data_ov004_02257e90[];

extern "C" int func_ov004_022215a0(UnkStruct_022215a0 *self)
{
    int result = 0;
    unsigned int field = *(unsigned int *) ((char *) self + 0x910);
    if (data_ov004_02257e98[field].flag != 0) {
        result = (self->*data_ov004_02257e90[field].pmf)();
    }
    return result;
}
