/* func_ov088_02279784 @ 0x02279784, 0x44 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_02279784 {
  public:
    char pad[0x654];
    int unk_654;
};

typedef int (UnkStruct_02279784::*PMF)();
struct Entry {
    PMF pmf;
    char pad[8];
};

extern Entry data_ov088_02279e28[];
}

extern "C" void func_ov088_02279784(UnkStruct_02279784 *obj, int index)
{
    int result = 1;
    if (data_ov088_02279e28[index].pmf != 0) {
        result = (obj->*data_ov088_02279e28[index].pmf)();
    }
    if (result != 0) {
        obj->unk_654 = index;
    }
}
