/* func_02026c1c @ 0x02026c1c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02026c1c {
    int n;
    unsigned char b;
};
class UnkStruct_02026c1c_2;
typedef void (UnkStruct_02026c1c_2::*Pmf)(UnkStruct_02026c1c *);
class UnkStruct_02026c1c_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};
extern int data_021c2c44, data_021c2c74;
extern "C" void *func_020984e8(void *);
extern "C" void *func_02099734(void *);
extern "C" int func_02098eb8(void *);
extern "C" void func_0202da88(UnkStruct_02026c1c_2 *self, void *tbl);
extern "C" void func_02068484(int a, void *b, int c);
extern "C" void func_02026c1c(UnkStruct_02026c1c_2 *self)
{
    unsigned char arg;
    UnkStruct_02026c1c out;
    void *a = func_020984e8(self);
    if (a && func_02098eb8(func_02099734(func_020984e8(a))) != -1) {
        func_0202da88(self, &data_021c2c44);
    } else {
        func_0202da88(self, &data_021c2c74);
    }
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_02068484(self->unk_40, &arg, out.n);
}
