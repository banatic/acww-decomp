/* func_ov004_022256ec @ 0x022256ec, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022256ec {
  public:
    int method();
    char pad_00[0x654];
    int unk_654;
};

struct Entry {
    int (UnkStruct_022256ec::*pmf)();
    int pad_08;
    int pad_0C;
};

extern Entry data_ov004_02258190[];

extern "C" void func_ov004_022256ec(UnkStruct_022256ec *obj, int index)
{
    int cond = 1;
    if (data_ov004_02258190[index].pmf != 0) {
        cond = (obj->*data_ov004_02258190[index].pmf)();
    }
    if (cond != 0) {
        obj->unk_654 = index;
    }
}
