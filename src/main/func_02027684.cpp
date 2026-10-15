/* func_02027684 @ 0x02027684, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02027684 {
    int n;
    unsigned char b;
};
class UnkStruct_02027684_2;
typedef void (UnkStruct_02027684_2::*Pmf)(UnkStruct_02027684 *);
class UnkStruct_02027684_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};
extern int data_021c2bb4;
extern "C" void func_0202da88(UnkStruct_02027684_2 *self, void *tbl);

extern "C" int func_02068484(int a, void *b, int c);
extern "C" int func_02015094(UnkStruct_02027684_2 *self);
extern "C" void func_02027684(UnkStruct_02027684_2 *self)
{
    unsigned char arg;
    UnkStruct_02027684 out;
    func_0202da88(self, &data_021c2bb4);
    func_02015094(self);
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_02068484(self->unk_40, &arg, out.n);
}
