/* func_020274e0 @ 0x020274e0, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020274e0 {
    int n;
    unsigned char b;
};
class UnkStruct_020274e0_2;
typedef void (UnkStruct_020274e0_2::*Pmf)(UnkStruct_020274e0 *);
struct UnkStruct_020274e0_3 {
    int unk_00, unk_04, unk_08;
};
class UnkStruct_020274e0_2 {
  public:
    char pad_00[0x40];
    UnkStruct_020274e0_3 *unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};
extern int data_021c2bb4;
extern "C" void func_0202da88(UnkStruct_020274e0_2 *self, void *tbl);
extern "C" void func_0206844c(UnkStruct_020274e0_3 *a, void *b, int c);

extern "C" void func_020274e0(UnkStruct_020274e0_2 *self)
{
    unsigned char arg;
    UnkStruct_020274e0 out;
    UnkStruct_020274e0_3 *c = self->unk_40;
    if (c->unk_04 == 5) {
        c->unk_08 = 1;
    }
    func_0202da88(self, &data_021c2bb4);
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
