/* func_020c3dac @ 0x020c3dac, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020c3dac {
  public:
    virtual int vfunc();
    char pad_04[0x650];
    int unk_654;
};

typedef int (UnkStruct_020c3dac::*PMF)();

struct Entry {
    PMF pmf;
    int pad_08;
    int pad_0C;
};

extern Entry data_021fbd90[];

extern "C" void func_020c3dac(UnkStruct_020c3dac *self, int idx)
{
    int result = 1;
    if (data_021fbd90[idx].pmf != 0) {
        result = (self->*data_021fbd90[idx].pmf)();
    }
    if (result == 1) {
        self->unk_654 = idx;
    }
}
