/* func_020206d0 @ 0x020206d0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020206d0 {
    int n;
    unsigned char b;
};
class UnkStruct_020206d0_2;
typedef void (UnkStruct_020206d0_2::*Pmf)(UnkStruct_020206d0 *);
class UnkStruct_020206d0_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};
extern int data_021c249c;
extern "C" void func_0202da88(UnkStruct_020206d0_2 *self, void *tbl);

extern "C" void func_0206844c(int a, void *b, int c);
extern "C" int func_020155cc(UnkStruct_020206d0_2 *self);
extern "C" void func_020206d0(UnkStruct_020206d0_2 *self)
{
    unsigned char arg;
    UnkStruct_020206d0 out;
    func_0202da88(self, &data_021c249c);
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
    func_020155cc(self);
}
