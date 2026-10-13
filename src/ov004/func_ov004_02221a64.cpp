/* func_ov004_02221a64 @ 0x02221a64, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02221a64 {
  public:
    int method();
    char pad_00[0x898];
    int unk_898;
};

struct Entry {
    int (UnkStruct_02221a64::*pmf)();
    int pad_08;
    int pad_0C;
};

extern Entry data_ov004_02257f48[];

extern "C" void func_ov004_02221a64(UnkStruct_02221a64 *obj, int index)
{
    int cond = 1;
    if (data_ov004_02257f48[index].pmf != 0) {
        cond = (obj->*data_ov004_02257f48[index].pmf)();
    }
    if (cond != 0) {
        obj->unk_898 = index;
    }
}
