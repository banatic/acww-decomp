/* func_ov078_02279670 @ 0x02279670, 0x44 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279670 {
  public:
    char pad[0x654];
    int unk_654;
};

typedef int (UnkStruct_02279670::*PMF)();

struct Entry {
    PMF pmf;
    int pad[2];
};

extern Entry data_ov078_02279c48[];

extern "C" void func_ov078_02279670(UnkStruct_02279670 *self, int idx)
{
    int ret = 1;
    if (data_ov078_02279c48[idx].pmf != 0) {
        ret = (self->*data_ov078_02279c48[idx].pmf)();
    }
    if (ret != 0) {
        self->unk_654 = idx;
    }
}
