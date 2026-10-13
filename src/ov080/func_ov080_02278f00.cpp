/* func_ov080_02278f00 @ 0x02278f00, 0x44 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278f00 {
  public:
    virtual int f0();
    virtual int f1();
    char pad_04[0x650];
    int unk_654;
};

typedef int (UnkStruct_02278f00::*PMF)();

struct Entry {
    PMF pmf;
    int pad_08;
    int pad_0C;
};

extern Entry data_ov080_022793e0[];

extern "C" void func_ov080_02278f00(UnkStruct_02278f00 *self, int index)
{
    int flag = 1;
    if (data_ov080_022793e0[index].pmf != 0) {
        flag = (self->*data_ov080_022793e0[index].pmf)();
    }
    if (flag != 0) {
        self->unk_654 = index;
    }
}
