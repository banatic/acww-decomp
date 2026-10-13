/* func_02020f14 @ 0x02020f14, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02020f14 {
    int n;
    unsigned char b;
};

class UnkStruct_02020f14_2;
typedef void (UnkStruct_02020f14_2::*Pmf)(UnkStruct_02020f14 *);

class UnkStruct_02020f14_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};

extern int data_021c219c;
extern "C" void func_0202da88(UnkStruct_02020f14_2 *self, void *tbl);
extern "C" void func_0206844c(int a, void *b, int c);

extern "C" void func_02020f14(UnkStruct_02020f14_2 *self)
{
    unsigned char arg;
    UnkStruct_02020f14 out;

    func_0202da88(self, &data_021c219c);
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
