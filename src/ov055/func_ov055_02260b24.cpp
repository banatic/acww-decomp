/* func_ov055_02260b24 @ 0x02260b24, 0x44 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02260b24 {
  public:
    char pad[0x654];
    int flag;
};

struct Entry {
    int (UnkStruct_02260b24::*pmf)();
    int pad[2];
};

extern Entry data_ov055_02261084[];

extern "C" void func_ov055_02260b24(UnkStruct_02260b24 *obj, int index)
{
    int result = 1;
    Entry *e = &data_ov055_02261084[index];
    if (e->pmf != 0) {
        result = (obj->*e->pmf)();
    }
    if (result) {
        obj->flag = index;
    }
}
