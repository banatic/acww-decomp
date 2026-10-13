/* func_ov085_022790ec @ 0x022790ec, 0x44 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022790ec {
  public:
    virtual int method();
    char pad_04[0x650];
    int unk_654;
};

typedef int (UnkStruct_022790ec::*MemberFunc)();

struct TableEntry {
    MemberFunc pmf;
    int pad_08;
    int pad_0C;
};

extern TableEntry data_ov085_022795e0[];

extern "C" void func_ov085_022790ec(UnkStruct_022790ec *self, int id)
{
    int result = 1;
    if (data_ov085_022795e0[id].pmf != 0) {
        result = (self->*data_ov085_022795e0[id].pmf)();
    }
    if (result != 0) {
        self->unk_654 = id;
    }
}
