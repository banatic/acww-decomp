/* func_020c3690 @ 0x020c3690, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020c3690 {
  public:
    int method();
    char pad_00[0x654];
    int unk_654;
};

struct Entry {
    int (UnkStruct_020c3690::*pmf)();
    int pad_08;
    int pad_0C;
};

extern Entry data_021fbcd8[];

extern "C" void func_020c3690(UnkStruct_020c3690 *obj, int index)
{
    int cond = 1;
    if (data_021fbcd8[index].pmf != 0) {
        cond = (obj->*data_021fbcd8[index].pmf)();
    }
    if (cond != 0) {
        obj->unk_654 = index;
    }
}
