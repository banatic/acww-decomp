/* func_ov048_02263638 @ 0x02263638, 0x4c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02263638 {
  public:
    char pad[0x654];
    int idx;
};

typedef int (UnkStruct_02263638::*PMF)();

struct FlagEntry {
    int flag;
    char pad[12];
};

struct PMFEntry {
    char pad[8];
    PMF pmf;
};

extern FlagEntry data_ov048_022647b0[];
extern PMFEntry data_ov048_022647a8[];

extern "C" int func_ov048_02263638(UnkStruct_02263638 *self)
{
    int ret = 0;
    int i = self->idx;
    if (data_ov048_022647b0[i].flag != 0) {
        ret = (self->*data_ov048_022647a8[i].pmf)();
    }
    return ret;
}
