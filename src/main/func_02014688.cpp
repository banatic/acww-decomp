/* func_02014688 @ 0x02014688, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02014688;
typedef void (UnkStruct_02014688::*Pmf0)();
typedef void (UnkStruct_02014688::*Pmf1)(void *);
struct Entry {
    Pmf0 a;
    Pmf1 b;
};
extern Entry data_021c17c4[];
class UnkStruct_02014688 {
  public:
    char pad_00[8];
    unsigned char unk_08;
};
extern "C" void func_020146cc(UnkStruct_02014688 *self);
extern "C" void func_02014688(UnkStruct_02014688 *self, void *arg)
{
    func_020146cc(self);
    if (self->unk_08 < 5) {
        (self->*(data_021c17c4[self->unk_08].b))(arg);
    }
}
