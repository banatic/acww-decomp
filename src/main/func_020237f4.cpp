/* func_020237f4 @ 0x020237f4, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020237f4 {
    int n;
    unsigned char b;
};
class UnkStruct_020237f4_2;
typedef void (UnkStruct_020237f4_2::*Pmf)(UnkStruct_020237f4 *);
struct UnkStruct_020237f4_3 {
    int unk_00, unk_04, unk_08;
};
class UnkStruct_020237f4_2 {
  public:
    char pad_00[0x40];
    UnkStruct_020237f4_3 *unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
};
extern int data_021c2f74;
extern "C" void func_0202da88(UnkStruct_020237f4_2 *self, void *tbl);
extern "C" void func_0206844c(UnkStruct_020237f4_3 *a, void *b, int c);

extern int data_021c2fd4;
extern "C" int func_02099fe8(void);
extern "C" void func_020237f4(UnkStruct_020237f4_2 *self)
{
    unsigned char arg;
    UnkStruct_020237f4 out;
    if (func_02099fe8() != -1) {
        func_0202da88(self, &data_021c2f74);
    } else {
        func_0202da88(self, &data_021c2fd4);
    }
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
