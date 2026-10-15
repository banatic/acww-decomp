/* func_02025cd8 @ 0x02025cd8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02025cd8 {
    int n;
    unsigned char b;
};

class UnkStruct_02025cd8_2;
typedef void (UnkStruct_02025cd8_2::*Pmf)(UnkStruct_02025cd8 *);

class UnkStruct_02025cd8_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};

extern int data_021c2cec;
extern "C" void func_0202da88(UnkStruct_02025cd8_2 *self, void *tbl);
extern "C" int func_02068484(int a, void *b, int c);

extern "C" void func_02025cd8(UnkStruct_02025cd8_2 *self)
{
    unsigned char arg;
    UnkStruct_02025cd8 out;

    func_0202da88(self, &data_021c2cec);
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_02068484(self->unk_40, &arg, out.n);
}
