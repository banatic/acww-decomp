/* func_02025200 @ 0x02025200, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02025200 {
    int n;
    unsigned char b;
};
class UnkStruct_02025200_2;
typedef void (UnkStruct_02025200_2::*Pmf)(UnkStruct_02025200 *);
class UnkStruct_02025200_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
    char pad_B8[0x164 - 0xb8];
    int unk_164;
};
extern int data_021c2e9c, data_021c2ddc;
extern "C" void func_0202da88(UnkStruct_02025200_2 *self, void *tbl);
extern "C" void func_0206844c(int a, void *b, int c);
extern "C" unsigned int func_0209b914(int);
extern "C" void func_02025200(UnkStruct_02025200_2 *self)
{
    unsigned char arg;
    UnkStruct_02025200 out;
    if (func_0209b914(self->unk_164) >= 4) {
        func_0202da88(self, &data_021c2e9c);
    } else {
        func_0202da88(self, &data_021c2ddc);
    }
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
