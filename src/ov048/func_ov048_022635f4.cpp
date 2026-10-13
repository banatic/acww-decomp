/* func_ov048_022635f4 @ 0x022635f4, 0x44 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022635f4 {
  public:
    virtual int method();
    char pad[0x650];
    int unk_654;
};

typedef int (UnkStruct_022635f4::*PMF)();

struct Entry {
    PMF pmf;
    int pad[2];
};

extern Entry data_ov048_022647a8[];

extern "C" void func_ov048_022635f4(UnkStruct_022635f4 *self, int index)
{
    int result = 1;
    if (data_ov048_022647a8[index].pmf != 0) {
        result = (self->*(data_ov048_022647a8[index].pmf))();
    }
    if (result != 0) {
        self->unk_654 = index;
    }
}
