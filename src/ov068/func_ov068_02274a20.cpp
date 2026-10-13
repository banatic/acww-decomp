/* func_ov068_02274a20 @ 0x02274a20, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_02274a20 {
  public:
    virtual void vfunc_00();
    char pad[0x654];
    int idx;
};

typedef int (UnkStruct_02274a20::*PMF)();

struct CondEntry {
    int cond;
    int pad[3];
};

struct PMFEntry {
    int pad[2];
    PMF pmf;
};

extern CondEntry data_ov068_02278848[];
extern PMFEntry data_ov068_02278840[];

int func_ov068_02274a20(UnkStruct_02274a20 *self)
{
    int ret = 0;
    int idx = self->idx;
    if (data_ov068_02278848[idx].cond) {
        ret = (self->*data_ov068_02278840[idx].pmf)();
    }
    return ret;
}
}
