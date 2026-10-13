/* func_ov004_02225ba4 @ 0x02225ba4, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02225ba4 {
  public:
    int method();
    char pad_00[0x654];
    int unk_654;
};

struct Entry {
    int (UnkStruct_02225ba4::*pmf)();
    int pad_08;
    int pad_0C;
};

extern Entry data_ov004_02258204[];

extern "C" void func_ov004_02225ba4(UnkStruct_02225ba4 *obj, int index)
{
    int cond = 1;
    if (data_ov004_02258204[index].pmf != 0) {
        cond = (obj->*data_ov004_02258204[index].pmf)();
    }
    if (cond != 0) {
        obj->unk_654 = index;
    }
}
