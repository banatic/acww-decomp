/* func_ov083_02278e98 @ 0x02278e98, 0x44 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_02278e98 {
  public:
    virtual int method() = 0;
    char pad[0x654];
    int unk_658;
};

typedef int (UnkStruct_02278e98::*CMethod)();

struct Entry {
    CMethod m;
    int pad[2];
};

extern Entry data_ov083_02279360[];

void func_ov083_02278e98(UnkStruct_02278e98 *obj, int index)
{
    int result = 1;
    Entry *entry = &data_ov083_02279360[index];
    if (entry->m != 0) {
        result = (obj->*entry->m)();
    }
    if (result != 0) {
        obj->unk_658 = index;
    }
}
}
