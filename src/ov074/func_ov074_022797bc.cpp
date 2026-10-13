/* func_ov074_022797bc @ 0x022797bc, 0x4c bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022797bc {
  public:
    virtual void vfunc_00();
    unsigned char pad_04[0x650];
    int indexField;
};

struct ValidEntry {
    int valid;
    int pad_04[3];
};

struct PMFEntry {
    int pad_00;
    int pad_04;
    int (UnkStruct_022797bc::*pmf)();
};

extern ValidEntry data_ov074_02279da4[];
extern PMFEntry data_ov074_02279d9c[];

extern "C" int func_ov074_022797bc(UnkStruct_022797bc *self)
{
    int result = 0;
    int idx = self->indexField;
    if (data_ov074_02279da4[idx].valid) {
        PMFEntry *entry = &data_ov074_02279d9c[idx];
        result = (self->*entry->pmf)();
    }
    return result;
}
