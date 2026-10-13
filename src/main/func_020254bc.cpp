/* func_020254bc @ 0x020254bc, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020254bc {
    int n;
    unsigned char b;
};
class UnkStruct_020254bc_2;
typedef void (UnkStruct_020254bc_2::*Pmf)(UnkStruct_020254bc *);
struct UnkStruct_020254bc_3 {
    int unk_00, unk_04, unk_08;
};
class UnkStruct_020254bc_2 {
  public:
    char pad_00[0x40];
    UnkStruct_020254bc_3 *unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};
extern int data_021c2dac;
extern "C" void func_0202da88(UnkStruct_020254bc_2 *self, void *tbl);
extern "C" void func_0206844c(UnkStruct_020254bc_3 *a, void *b, int c);

extern "C" void func_020254bc(UnkStruct_020254bc_2 *self)
{
    unsigned char arg;
    UnkStruct_020254bc out;
    UnkStruct_020254bc_3 *c = self->unk_40;
    if (c) {
        c->unk_08 = 1;
    }
    func_0202da88(self, &data_021c2dac);
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
