/* func_ov085_02278c14 @ 0x02278c14, 0x154 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02278c14 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual void vf25();
    virtual void vf26();
    virtual void vf27();
    virtual void vf28();
    virtual void vf29();
    virtual void vf30();
    virtual void vf31();
    virtual void vf32();
    virtual void vf33();
    virtual void method();
    char pad_04[0x1e - 4];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
};

typedef struct Msg {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    u16 unk_04;
} Msg;

extern "C" void func_020154b4(UnkStruct_02278c14 *, u16 *, int, int, int);
extern "C" void func_0209a000(u16 *, int);
extern "C" void func_0206844c(void *, u8 *, const void *);
extern "C" void *func_020867a0(void *);
extern "C" void func_020867a4(void *, void *);
extern "C" void func_02094fd4(int *);
extern "C" void func_02094fbc(int *);
extern "C" int func_02003704(void *);
extern "C" char *func_0204c7c0(void);
extern "C" void func_020984e8(void);
extern "C" int func_02099870(void);
extern "C" char *func_0207cb10(char *, int);
extern "C" void *func_0208150c(char *);
extern "C" void func_02003618(void *, int *);
extern "C" void func_0203d7c4(int, int *);
extern "C" void func_02068404(void *, int, int *);
extern "C" void *func_020644cc(int);
extern "C" void func_02077f14(void *, const void *);
extern "C" void func_0207a44c(void *);
extern "C" int data_021f3aa4;
extern "C" int data_021e5a2c;
extern "C" const int data_ov085_0227959c;
extern "C" const int data_ov085_022795ac;
extern "C" const int data_ov085_022795bc;

extern "C" void func_ov085_02278c14(UnkStruct_02278c14 *self)
{
    Msg m;
    int blk[8];
    const void *tag = (const void *) &data_ov085_0227959c;
    int code = 0xff;
    void *o;
    char *c;

    if (self->unk_B4 >= 0) {
        if (self->unk_1E == 1 || self->unk_1E == 4) {
            self->unk_B4 = ~1;
        }
        if (self->unk_1E == 2) {
            m.unk_02 = 0x1559;
            func_020154b4(self, &m.unk_02, 0, 5, 0);
            m.unk_04 = 0x1559;
            func_0209a000(&m.unk_04, 0);
            m.unk_00 = 4;
            func_0206844c(self->unk_40, &m.unk_00, (const void *) &data_ov085_022795ac);
        }
        return;
    }

    if (self->unk_1E == 0xf) {
        o = func_020867a0(&data_021f3aa4);
        func_02094fd4(blk);
        if (func_02003704(o) == 0) {
            c = func_0204c7c0();
            func_020984e8();
            c = func_0207cb10(c + 0x9284, func_02099870());
            if (func_02003704(func_0208150c(c)) != 0) {
                func_020867a4(&data_021f3aa4, func_0208150c(c));
                o = func_020867a0(&data_021f3aa4);
            }
        }
        func_02003618(o, blk);
        func_0203d7c4(0, blk);
        func_02068404(self->unk_40, 1, blk);
        func_02077f14(func_020644cc(2), (const void *) &data_ov085_022795bc);
        func_0207a44c(&data_021e5a2c);
        code = 0x10;
        func_02094fbc(blk);
    }

    switch (self->unk_1E) {
        case 7:
        case 8:
        case 0x14:
        case 0x15:
            self->method();
            break;
    }

    if (code != 0xff) {
        m.unk_01 = (u8) code;
        func_0206844c(self->unk_40, &m.unk_01, tag);
    }
}
