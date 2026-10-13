/* func_ov004_0221fdf4 @ 0x0221fdf4, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0221fdf4 {
  public:
    int method();
    char pad_00[0x8a4];
    int unk_8A4;
};

struct Entry {
    int (UnkStruct_0221fdf4::*pmf)();
    int pad_08;
    int pad_0C;
};

extern Entry data_ov004_02257d58[];

extern "C" void func_ov004_0221fdf4(UnkStruct_0221fdf4 *obj, int index)
{
    int cond = 1;
    if (data_ov004_02257d58[index].pmf != 0) {
        cond = (obj->*data_ov004_02257d58[index].pmf)();
    }
    if (cond != 0) {
        obj->unk_8A4 = index;
    }
}
