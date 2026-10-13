/* func_ov076_02279370 @ 0x02279370, 0x44 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279370 {
  public:
    char pad[0x654];
    int unk_654;
};

typedef int (UnkStruct_02279370::*PMF)();

struct Entry {
    PMF pmf;
    int pad[2];
};

extern Entry data_ov076_0227988c[];

extern "C" void func_ov076_02279370(UnkStruct_02279370 *self, int idx)
{
    int ret = 1;
    if (data_ov076_0227988c[idx].pmf != 0) {
        ret = (self->*data_ov076_0227988c[idx].pmf)();
    }
    if (ret != 0) {
        self->unk_654 = idx;
    }
}
