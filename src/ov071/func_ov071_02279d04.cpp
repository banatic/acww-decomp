/* func_ov071_02279d04 @ 0x02279d04, 0x44 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279d04;
struct Entry {
    int (UnkStruct_02279d04::*pmf)();
    char pad[8];
};
extern Entry data_ov071_0227a3a4[];
class UnkStruct_02279d04 {
  public:
    virtual int vfunc_00();
    char pad[0x650];
    int unk_654;
};
extern "C" void func_ov071_02279d04(UnkStruct_02279d04 *obj, int index)
{
    int result = 1;
    Entry &e = data_ov071_0227a3a4[index];
    if (e.pmf) {
        result = (obj->*e.pmf)();
    }
    if (result != 0) {
        obj->unk_654 = index;
    }
}
