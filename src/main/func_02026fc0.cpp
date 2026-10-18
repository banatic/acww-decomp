/* func_02026fc0 @ 0x02026fc0, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02026fc0 {
    int n;
    unsigned char b;
};
class UnkStruct_02026fc0_2;
typedef void (UnkStruct_02026fc0_2::*Pmf)(UnkStruct_02026fc0 *);
class UnkStruct_02026fc0_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};
struct UnkStruct_02026fc0_3 {
    char pad_00[0x18];
};
extern UnkStruct_02026fc0_3 data_021c29d4[];
// {0x17, 0x18, 0x19}, the template of the local index table
struct Map {
    int v[3];
};
extern const Map data_020d9b50;
extern "C" void func_0202da88(UnkStruct_02026fc0_2 *self, void *tbl);
extern "C" int func_02068484(int a, void *b, int c);
extern "C" void func_02026fc0(UnkStruct_02026fc0_2 *self, int unused, int i)
{
    unsigned char arg;
    UnkStruct_02026fc0 out;
    Map map = data_020d9b50;
    if (i < 0 || i >= 3) {
        i = 0;
    }
    func_0202da88(self, &data_021c29d4[map.v[i]]);
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_02068484(self->unk_40, &arg, out.n);
}
