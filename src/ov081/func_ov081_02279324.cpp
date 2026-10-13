/* func_ov081_02279324 @ 0x02279324, 0x4c bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279324 {
  public:
    virtual int vfunc();
    char pad[0x650];
    int unk_654;
};

typedef int (UnkStruct_02279324::*PMFPtr)();

struct PMFEntry {
    char pad[8];
    PMFPtr pmf;
};

struct FlagEntry {
    int flag;
    char pad[12];
};

extern FlagEntry data_ov081_022798bc[];
extern PMFEntry data_ov081_022798b4[];

extern "C" int func_ov081_02279324(UnkStruct_02279324 *obj)
{
    int result = 0;
    int idx = obj->unk_654;
    if (data_ov081_022798bc[idx].flag != 0) {
        result = (obj->*data_ov081_022798b4[idx].pmf)();
    }
    return result;
}
