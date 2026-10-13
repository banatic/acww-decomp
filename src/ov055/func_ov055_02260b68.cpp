/* func_ov055_02260b68 @ 0x02260b68, 0x4c bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02260b68 {
  public:
    virtual void vfunc();
    char pad[0x650];
    int index;
};

typedef int (UnkStruct_02260b68::*PMF)();

struct PMFEntry {
    char pad[8];
    PMF pmf;
};

struct FlagEntry {
    int flag;
    char pad[12];
};

extern FlagEntry data_ov055_0226108c[];
extern PMFEntry data_ov055_02261084[];

extern "C" int func_ov055_02260b68(UnkStruct_02260b68 *self)
{
    int result = 0;
    int idx = self->index;
    if (data_ov055_0226108c[idx].flag != 0) {
        PMFEntry *pe = &data_ov055_02261084[idx];
        result = (self->*pe->pmf)();
    }
    return result;
}
