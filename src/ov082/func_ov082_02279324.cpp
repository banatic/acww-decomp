/* func_ov082_02279324 @ 0x02279324, 0x44 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279324 {
  public:
    virtual int v();
    char pad[0x650];
    int unk_654;
};

typedef int (UnkStruct_02279324::*PMF)();

struct TableEntry {
    PMF pmf;
    char pad[8];
};

extern TableEntry data_ov082_02279914[];

extern "C" void func_ov082_02279324(UnkStruct_02279324 *obj, int idx)
{
    int result = 1;
    if (data_ov082_02279914[idx].pmf != 0) {
        result = (obj->*data_ov082_02279914[idx].pmf)();
    }
    if (result) {
        obj->unk_654 = idx;
    }
}
