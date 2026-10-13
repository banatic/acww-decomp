/* func_ov047_02262538 @ 0x02262538, 0x4c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02262538 {
  public:
    virtual int vfunc();
    char pad[0x650];
    int index;
};

struct FlagEntry {
    int flag;
    char pad[12];
};

struct PMFEntry {
    char pad[8];
    int (UnkStruct_02262538::*pmf)();
};

extern FlagEntry data_ov047_02263050[];
extern PMFEntry data_ov047_02263048[];

extern "C" int func_ov047_02262538(UnkStruct_02262538 *self)
{
    int result = 0;
    int idx = self->index;
    if (data_ov047_02263050[idx].flag != 0) {
        result = (self->*data_ov047_02263048[idx].pmf)();
    }
    return result;
}
