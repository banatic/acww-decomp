/* func_020243d8 @ 0x020243d8, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020243d8 {
    int n;
    unsigned char b;
};
class UnkStruct_020243d8_2;
typedef void (UnkStruct_020243d8_2::*Pmf)(UnkStruct_020243d8 *);
class UnkStruct_020243d8_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
    char pad_B8[0x164 - 0xb8];
    int unk_164;
};
extern int data_021c2e9c, data_021c2e84;
extern "C" void func_0202da88(UnkStruct_020243d8_2 *self, void *tbl);
extern "C" void func_0206844c(int a, void *b, int c);

extern "C" void *func_0202d9c4(UnkStruct_020243d8_2 *);
extern "C" void *func_0209bc40(void *);
extern "C" int func_0209b8d0(void *);
extern "C" int func_0209b914(int);
extern "C" void func_020243d8(UnkStruct_020243d8_2 *self)
{
    unsigned char arg;
    UnkStruct_020243d8 out;
    int n = func_0209b8d0(func_0209bc40(func_0202d9c4(self)));
    if (func_0209b914(self->unk_164) >= n - 1) {
        func_0202da88(self, &data_021c2e9c);
    } else {
        func_0202da88(self, &data_021c2e84);
    }
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
