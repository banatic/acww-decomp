/* func_0201fddc @ 0x0201fddc, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201fddc {
    int n;
    unsigned char b;
};
class UnkStruct_0201fddc_2;
typedef void (UnkStruct_0201fddc_2::*Pmf)(UnkStruct_0201fddc *);
class UnkStruct_0201fddc_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};
extern int data_021c2334;
extern "C" void func_0202006c(UnkStruct_0201fddc_2 *self);
extern "C" void func_0202da88(UnkStruct_0201fddc_2 *self, void *tbl);
extern "C" void func_0206844c(int a, void *b, int c);
extern "C" void func_0201fddc(UnkStruct_0201fddc_2 *self)
{
    unsigned char arg;
    UnkStruct_0201fddc out;
    func_0202006c(self);
    func_0202da88(self, &data_021c2334);
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
