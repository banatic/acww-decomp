/* func_ov077_02279358 @ 0x02279358, 0x44 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279358 {
  public:
    char pad_00[0x654];
    int unk_654;
};
typedef int (UnkStruct_02279358::*PMF)();
struct PMFRep {
    int unk_00;
    int p1;
    int pad_08;
    int pad_0C;
};
union PMFValue {
    PMF pmf;
    PMFRep rep;
};
extern PMFValue data_ov077_022799a0[];
extern "C" void func_ov077_02279358(UnkStruct_02279358 *obj, int idx)
{
    int result = 1;
    if (data_ov077_022799a0[idx].rep.unk_00 != 0) {
        result = (obj->*data_ov077_022799a0[idx].pmf)();
    }
    if (result != 0) {
        obj->unk_654 = idx;
    }
}
