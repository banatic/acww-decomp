/* func_ov075_02278da4 @ 0x02278da4, 0x44 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278da4 {
  public:
    virtual void vfunc() {}
    char pad[0xAC];
    int m_index;
};

typedef void (UnkStruct_02278da4::*PMF)();

struct FlagEntry {
    unsigned char flag;
    char pad_01[11];
};

struct PMFEntry {
    PMF pmf;
    char pad_08[4];
};

extern FlagEntry data_ov075_02279938[];
extern PMFEntry data_ov075_02279930[];

extern "C" void func_ov075_02278da4(UnkStruct_02278da4 *obj)
{
    int idx = obj->m_index;
    if (data_ov075_02279938[idx].flag != 0) {
        PMFEntry *e = &data_ov075_02279930[idx];
        if (e->pmf != 0) {
            (obj->*e->pmf)();
        }
    }
}
