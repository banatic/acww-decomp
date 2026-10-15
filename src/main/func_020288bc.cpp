/* func_020288bc @ 0x020288bc, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020288bc {
    int n;
    unsigned char b;
};
class UnkStruct_020288bc_2;
typedef void (UnkStruct_020288bc_2::*Pmf)(UnkStruct_020288bc *);
class UnkStruct_020288bc_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
    char pad_B8[0x140 - 0xb8];
    void *unk_140[1];
};
extern "C" void func_0202da88(UnkStruct_020288bc_2 *self, void *tbl);
extern "C" void func_0202dac0(UnkStruct_020288bc_2 *self);
extern "C" int func_02068484(int a, void *b, int c);
extern "C" void func_020288bc(UnkStruct_020288bc_2 *self, int unused, int i)
{
    unsigned char arg;
    UnkStruct_020288bc out;
    void *p = self->unk_140[i];
    if (p) {
        func_0202da88(self, p);
    } else {
        func_0202dac0(self);
    }
    if (self->pmf) {
        (self->*(self->pmf))(&out);
        if (out.n) {
            arg = out.b;
            func_02068484(self->unk_40, &arg, out.n);
        }
    }
}
