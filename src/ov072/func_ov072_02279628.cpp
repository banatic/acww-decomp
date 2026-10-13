/* func_ov072_02279628 @ 0x02279628, 0x44 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279628 {
  public:
    char pad[0x654];
    int unk_654;
};

typedef int (UnkStruct_02279628::*PMF)();

struct Entry {
    PMF pmf;
    int pad[2];
};

extern Entry data_ov072_02279bd8[];

extern "C" void func_ov072_02279628(UnkStruct_02279628 *self, int idx)
{
    int ret = 1;
    if (data_ov072_02279bd8[idx].pmf != 0) {
        ret = (self->*data_ov072_02279bd8[idx].pmf)();
    }
    if (ret != 0) {
        self->unk_654 = idx;
    }
}
