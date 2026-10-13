/* func_ov002_02209984 @ 0x02209984, 0xf4 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02209984_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4(int a, int b);
};

struct UnkStruct_02209984 {
    int f0;
    int f4;
    int unk_08;
    int unk_0C;
    int unk_10;
    u16 unk_14;
    u8 unk_16;
    u8 unk_17;
    u8 unk_18;
    u8 unk_19;
    u8 unk_1A;
    u8 unk_1B;
    u8 unk_1C;
    u8 pad_1D[7];
    void *unk_24;
};

extern "C" void *func_02064b2c(void *a, void *g, int c, int d);
extern "C" void func_020e993c(void *g, void *n);
extern "C" void func_ov002_02209b6c(char *p, u8 a, u16 w, u8 c, u8 d);
extern "C" void func_0208f210(char *p, int a, int b);
extern "C" void func_0208f258(char *p);
extern "C" void func_0208f260(char *p);
extern "C" void func_0208f0c4(char *p, int a);
extern "C" void func_ov002_0220b04c(char *p);
extern "C" void func_ov002_0220b06c(char *p, int a, int b, int c);
extern "C" void func_0208aa98(char *p);

extern void *data_021fbe94;
extern const char data_ov002_0220bc18[];

extern "C" void func_ov002_02209984(UnkStruct_02209984 *self, u8 a, int b, void *res)
{
    void *g;
    void *n;
    u16 w;
    int i;

    self->unk_1A = a;
    self->unk_10 = b;
    self->unk_08 = 0;
    self->unk_0C = 0;
    self->unk_16 = 0;
    self->unk_17 = 0;
    self->unk_18 = 0;
    self->unk_19 = 0;
    self->unk_1B = 0xd;
    self->unk_1C = 5;
    if (res == 0) {
        self->unk_24 = (void *) data_ov002_0220bc18;
    } else {
        self->unk_24 = res;
    }
    g = data_021fbe94;
    n = func_02064b2c(self->unk_24, g, -4, 0);
    self->f4 = *(u16 *) ((char *) n + 0x44) & 0x3ff;
    func_020e993c(g, n);
    w = self->f4;
    for (i = 0; i < 5; i++) {
        func_ov002_02209b6c((char *) self + 0x28 + i * 0x74, a, w, 1, 9);
        w = w + 0x1a;
    }
    ((UnkStruct_02209984_2 *) ((char *) self + 0x26c))->f4(0x60, 0x8c);
    func_0208f210((char *) self + 0x26c, 0, 0);
    func_0208f258((char *) self + 0x26c);
    func_0208f260((char *) self + 0x26c);
    func_0208f0c4((char *) self + 0x26c, 1);
    func_ov002_0220b04c((char *) self + 0x2e4);
    func_ov002_0220b06c((char *) self + 0x2e4, 0x1f, 0x80, 0xc);
    func_0208aa98((char *) self + 0x2e4);
    self->unk_14 = 0;
}
