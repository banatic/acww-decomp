/* func_ov068_022749dc @ 0x022749dc, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022749dc {
  public:
    unsigned char pad[0x658];
    int unk_658;
};

typedef int (UnkStruct_022749dc::*PMF)();

struct TableEntry {
    PMF pmf;
    unsigned int pad[2];
};

extern TableEntry data_ov068_02278840[];

extern "C" void func_ov068_022749dc(UnkStruct_022749dc *self, int idx)
{
    int flag = 1;
    if (data_ov068_02278840[idx].pmf != 0) {
        flag = (self->*data_ov068_02278840[idx].pmf)();
    }
    if (flag != 0) {
        self->unk_658 = idx;
    }
}
