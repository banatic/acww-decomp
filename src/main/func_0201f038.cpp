/* func_0201f038 @ 0x0201f038, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201f038 {
    int n;
    unsigned char b;
};
class UnkStruct_0201f038_2;
typedef void (UnkStruct_0201f038_2::*Pmf)(UnkStruct_0201f038 *);
struct UnkStruct_0201f038_3 {
    int unk_00, unk_04, unk_08;
};
class UnkStruct_0201f038_2 {
  public:
    char pad_00[0x40];
    UnkStruct_0201f038_3 *unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};
extern int data_021c25bc;
extern "C" void func_0202da88(UnkStruct_0201f038_2 *self, void *tbl);
extern "C" void func_0206844c(UnkStruct_0201f038_3 *a, void *b, int c);

extern "C" void func_0201f038(UnkStruct_0201f038_2 *self)
{
    unsigned char arg;
    UnkStruct_0201f038 out;
    func_0202da88(self, &data_021c25bc);
    UnkStruct_0201f038_3 *c = self->unk_40;
    if (c) {
        c->unk_08 = 1;
    }
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
