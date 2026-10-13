/* func_0202534c @ 0x0202534c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202534c {
    int n;
    unsigned char b;
};

class UnkStruct_0202534c_2;
typedef void (UnkStruct_0202534c_2::*Pmf)(UnkStruct_0202534c *);

class UnkStruct_0202534c_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};

extern int data_021c2dc4;
extern "C" void func_0202da88(UnkStruct_0202534c_2 *self, void *tbl);
extern "C" void func_02068484(int a, void *b, int c);

extern "C" void func_0202534c(UnkStruct_0202534c_2 *self)
{
    unsigned char arg;
    UnkStruct_0202534c out;

    func_0202da88(self, &data_021c2dc4);
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_02068484(self->unk_40, &arg, out.n);
}
