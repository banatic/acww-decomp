/* func_ov073_02279608 @ 0x02279608, 0x44 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279608 {
  public:
    char pad[0x654];
    int unk_654;
};

typedef int (UnkStruct_02279608::*PMF)();

struct Entry {
    PMF pmf;
    int pad[2];
};

extern Entry data_ov073_02279c14[];

extern "C" void func_ov073_02279608(UnkStruct_02279608 *self, int idx)
{
    int ret = 1;
    if (data_ov073_02279c14[idx].pmf != 0) {
        ret = (self->*data_ov073_02279c14[idx].pmf)();
    }
    if (ret != 0) {
        self->unk_654 = idx;
    }
}
