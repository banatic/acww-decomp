/* func_ov053_02261524 @ 0x02261524, 0x44 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261524 {
  public:
    virtual bool vfunc_00() = 0;
    char pad[0x650];
    int unk_654;
};

struct Entry {
    bool (UnkStruct_02261524::*pmf)();
    int pad[2];
};

extern Entry data_ov053_02261c64[];

extern "C" void func_ov053_02261524(UnkStruct_02261524 *self, int index)
{
    bool result = true;
    Entry *entry = &data_ov053_02261c64[index];
    if (entry->pmf != 0) {
        result = (self->*entry->pmf)();
    }
    if (result) {
        self->unk_654 = index;
    }
}
