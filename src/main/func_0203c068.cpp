/* func_0203c068 @ 0x0203c068, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0203c068;
typedef void (UnkStruct_0203c068::*Pmf)();
struct Entry {
    int a, b;
    Pmf pmf;
};
extern Entry data_021c6820[];
class UnkStruct_0203c068 {
  public:
    char pad_00[0x1f8];
    int unk_1F8;
};
extern "C" void func_0203c3ec(UnkStruct_0203c068 *);
extern "C" void func_0203c068(UnkStruct_0203c068 *self)
{
    int i = self->unk_1F8;
    if (i < 0x15) {
        (self->*(data_021c6820[i].pmf))();
        func_0203c3ec(self);
    }
}
