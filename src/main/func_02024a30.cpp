/* func_02024a30 @ 0x02024a30, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02024a30 {
    int n;
    unsigned char b;
};
class UnkStruct_02024a30_2;
typedef void (UnkStruct_02024a30_2::*Pmf)(UnkStruct_02024a30 *);
class UnkStruct_02024a30_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
    char pad_B8[0x164 - 0xb8];
    int unk_164;
};
extern int data_021c2e6c, data_021c2e54;
extern "C" void func_0202da88(UnkStruct_02024a30_2 *self, void *tbl);
extern "C" void func_0206844c(int a, void *b, int c);

extern "C" void *func_0202d9c4(UnkStruct_02024a30_2 *);
extern "C" int func_0209bc40(void *);
extern "C" void func_0202d730(UnkStruct_02024a30_2 *);
extern "C" void func_02024a30(UnkStruct_02024a30_2 *self)
{
    unsigned char arg;
    UnkStruct_02024a30 out;
    if (func_0209bc40(func_0202d9c4(self)) == 2) {
        func_0202da88(self, &data_021c2e6c);
    } else {
        if (func_0209bc40(func_0202d9c4(self)) == 3) {
            func_0202d730(self);
        }
        func_0202da88(self, &data_021c2e54);
    }
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
