/* func_0201f738 @ 0x0201f738, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_020644cc(int);
extern "C" int func_02020a5c(void *, int);
extern "C" int func_020819bc(int);
extern "C" void func_0202da88(void *, int);
extern "C" void func_0202d8f8(void *, int *, int *, int, int);
extern "C" void func_020819e0(int);

struct UnkStruct_0201f738 {
    char pad_00[0x830];
    int unk_830;
};

class Class {
  public:
    char pad_00[0xb0];
    void (Class::*pmf)(int);
    char pad_B8[0x100 - 0xb0 - 8];
    UnkStruct_0201f738 *inner;
    char pad_104[0x128 - 0x104];
    int unk_128;
    int unk_12C;
};

extern unsigned char data_021c1fe4[];
extern unsigned char data_021c1ffc[];
extern unsigned char data_021c2014[];

extern "C" void func_0201f738(Class *self, int arg1)
{
    int r4 = self->inner->unk_830;
    int r6 = func_020644cc(0xa) & 1;

    if (func_02020a5c(self, arg1) != 0) {
        func_0202d8f8(self, &self->unk_12C, &self->unk_128, r4, 0);
        return;
    }

    if (!(self->unk_12C != 0 && func_020819bc(self->unk_12C) != 0)) {
        func_0202da88(self, (unsigned int) data_021c1fe4);
    } else {
        if (r6 == 0) {
            func_0202da88(self, (unsigned int) data_021c2014);
        } else {
            func_0202da88(self, (unsigned int) data_021c1ffc);
        }
    }

    if (self->pmf != 0) {
        (self->*self->pmf)(arg1);
    }

    func_0202d8f8(self, &self->unk_12C, &self->unk_128, r4, 0);
    if (self->unk_12C != 0) {
        func_020819e0(self->unk_12C);
    }
}
