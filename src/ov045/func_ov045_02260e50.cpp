/* func_ov045_02260e50 @ 0x02260e50, 0x44 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02260e50 {
  public:
    char pad[0x658];
    int flag;
};

struct Entry {
    int (UnkStruct_02260e50::*pmf)();
    int pad[2];
};

extern Entry data_ov045_022615bc[];

extern "C" void func_ov045_02260e50(UnkStruct_02260e50 *obj, int index)
{
    int result = 1;
    Entry *e = &data_ov045_022615bc[index];
    if (e->pmf != 0) {
        result = (obj->*e->pmf)();
    }
    if (result) {
        obj->flag = index;
    }
}
