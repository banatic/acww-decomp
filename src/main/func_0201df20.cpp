/* func_0201df20 @ 0x0201df20, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201df20 {
    int n;
    unsigned char b;
};
class UnkStruct_0201df20_2;
typedef void (UnkStruct_0201df20_2::*Pmf)(UnkStruct_0201df20 *);
class UnkStruct_0201df20_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};
extern int data_021c228c;
extern "C" void *func_0209a000(unsigned short *, int);
extern "C" void *func_020984e8(void *);
extern "C" int func_0209dee8(void *);
extern "C" void func_020992b8(void *, unsigned char);
extern "C" void func_0202da88(UnkStruct_0201df20_2 *self, void *tbl);
extern "C" void func_0206844c(int a, void *b, int c);
extern "C" void func_0201df20(UnkStruct_0201df20_2 *self)
{
    unsigned char arg;
    unsigned short h;
    UnkStruct_0201df20 out;
    h = 0x3818;
    void *p = func_020984e8(func_0209a000(&h, 0));
    func_020992b8(p, (unsigned char) func_0209dee8(p));
    func_0202da88(self, &data_021c228c);
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
