/* func_02023a00 @ 0x02023a00, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02023a00 {
    int n;
    unsigned char b;
};

class UnkStruct_02023a00_2;
typedef void (UnkStruct_02023a00_2::*Pmf)(UnkStruct_02023a00 *);

class UnkStruct_02023a00_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};

extern int data_021c2f8c;
extern "C" void func_0202da88(UnkStruct_02023a00_2 *self, void *tbl);
extern "C" void func_0206844c(int a, void *b, int c);

extern "C" void func_02023a00(UnkStruct_02023a00_2 *self)
{
    unsigned char arg;
    UnkStruct_02023a00 out;

    func_0202da88(self, &data_021c2f8c);
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
