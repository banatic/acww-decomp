/* func_ov070_02279974 @ 0x02279974, 0x44 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279974 {
  public:
    virtual ~UnkStruct_02279974();
    virtual void vf0();
    char pad_04[0x650];
    int unk_654;
};

typedef int (UnkStruct_02279974::*PMF)();

struct TableEntry {
    PMF pmf;
    unsigned int pad_08[2];
};

extern TableEntry data_ov070_02279f24[];

extern "C" void func_ov070_02279974(UnkStruct_02279974 *self, int idx)
{
    int result = 1;
    if (data_ov070_02279f24[idx].pmf != 0) {
        result = (self->*data_ov070_02279f24[idx].pmf)();
    }
    if (result == 1) {
        self->unk_654 = idx;
    }
}
