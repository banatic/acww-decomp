/* func_02023568 @ 0x02023568, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02023568 {
    int n;
    unsigned char b;
};

// 8 bytes, 4-aligned, zeroed field-by-field by its constructor.
struct Stamp {
    Stamp()
    {
        w[0] = 0;
        w[1] = 0;
    }
    union {
        int w[2];
        struct {
            unsigned short f0;
            unsigned char f2;
            unsigned char f3;
            unsigned char f4;
            unsigned char f5;
            unsigned char f6;
            unsigned char f7;
        } f;
    };
};

class UnkStruct_02023568_2;
typedef void (UnkStruct_02023568_2::*Pmf)(UnkStruct_02023568 *);

class UnkStruct_02023568_2 {
  public:
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
    char pad_B8[0x100 - 0xb8];
    char *unk_100;
};

extern int data_021c301c, data_021c304c, data_021c3034, data_021c3064;

extern "C" void func_0209e474(Stamp *);
extern "C" void MI_CpuCopy8(const void *src, void *dst, int len);
extern "C" void func_0206f80c(Stamp *);
extern "C" int func_0209e350(Stamp *, Stamp *);
extern "C" int func_0207d578(int, Stamp *);
extern "C" void func_0202da88(UnkStruct_02023568_2 *self, void *tbl);
extern "C" void func_0206844c(int a, void *b, int c);

extern "C" void func_02023568(UnkStruct_02023568_2 *self)
{
    unsigned char arg;
    Stamp a;
    Stamp b;
    UnkStruct_02023568 out;

    func_0209e474(&b);
    MI_CpuCopy8(&b, &a, 8);
    func_0206f80c(&a);
    if (func_0209e350(&b, &a) <= 30) {
        func_0202da88(self, &data_021c301c);
    } else if (func_0207d578(*(int *) (self->unk_100 + 0x830), &a)) {
        func_0202da88(self, &data_021c304c);
    } else if (a.f.f2 < 6) {
        func_0202da88(self, &data_021c3034);
    } else {
        func_0202da88(self, &data_021c3064);
    }
    if (self->pmf) {
        (self->*(self->pmf))(&out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
