/* func_ov077_0227939c @ 0x0227939c, 0x4c bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0227939c {
  public:
    char pad_00[0x654];
    int idx;
};

typedef int (UnkStruct_0227939c::*PMF)();

struct Entry {
    char pad_00[8];
    PMF pmf;
};

extern Entry data_ov077_022799a0[];

extern "C" int func_ov077_0227939c(UnkStruct_0227939c *obj)
{
    int result = 0;
    if (data_ov077_022799a0[obj->idx].pmf) {
        result = (obj->*data_ov077_022799a0[obj->idx].pmf)();
    }
    return result;
}
