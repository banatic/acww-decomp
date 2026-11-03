/* design_picker_4: 11 functions, module ov125
 * mwccarm 1.2/base -O4,s
 * func_ov125_022a06f4 @ 0x022a06f4, 0x4 bytes, Thumb
 * func_ov125_022a06f0 @ 0x022a06f0, 0x4 bytes, Thumb
 * func_ov125_022a06e0 @ 0x022a06e0, 0x10 bytes, Thumb
 * func_ov125_022a06c4 @ 0x022a06c4, 0x1c bytes, Thumb
 * func_ov125_022a0664 @ 0x022a0664, 0x60 bytes, Thumb
 * func_ov125_022a063c @ 0x022a063c, 0x28 bytes, Thumb
 * func_ov125_022a05cc @ 0x022a05cc, 0x70 bytes, Thumb
 * func_ov125_022a0594 @ 0x022a0594, 0x38 bytes, Thumb
 * func_ov125_022a0564 @ 0x022a0564, 0x30 bytes, Thumb
 * func_ov125_022a0510 @ 0x022a0510, 0x54 bytes, Thumb
 * func_ov125_022a04e4 @ 0x022a04e4, 0x2c bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x180];
    u8 sub180[1];
    u8 pad_181[0x574 - 0x181];
    u8 sub574[1];
    u8 pad_575[0x878 - 0x575];
    u16 unk_878;
    u8 unk_87A;
    u8 unk_87B;
    u8 unk_87C;
} UnkStruct_022a0510;

extern void func_020ee470(void *parameter0);
extern void func_ov125_022a0428(void);
extern void func_ov125_022a0418(unsigned int arg);
extern void func_ov002_022097b8(void *);
extern void func_ov125_022a0334(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern int func_ov002_0220ab84(void *, int);
extern void func_ov125_0229f75c(void *, int);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_02207f48(int, int);
extern unsigned char *func_ov002_022080a0(int, unsigned char value);
extern void func_ov125_0229fe98(int);
extern void func_ov125_0229faf8(void *p);
extern int __arm func_020ee45c(void *p);
extern int func_0206fca4(void);
extern int func_ov125_0229f76c(void *p, int b);
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_02207f04(void *p, int a, int b, int c, int d);
extern int func_ov002_02207f3c(void *p, int arg);
extern void func_020027f0(int arg);
extern void func_ov125_0229f74c(void *p, int arg);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);
extern void func_ov002_02209984(void *p, int a, int b, int _x);
extern void func_0206fc4c(int arg);
extern void func_ov002_02207cec(void *p, int a);
extern void func_ov002_02209178(void *);
extern void func_ov124_0229eea0(void *);
extern void func_ov002_0220af74(void *);

int func_ov125_022a0564(void *p);

int func_ov125_022a06f4(void)
{
    return 1;
}

int func_ov125_022a06f0(void)
{
    return 1;
}

int func_ov125_022a06e0(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov125_022a06c4(unsigned int arg)
{
    func_ov125_022a0428();
    func_ov125_022a0418(arg);
    func_ov002_02208090((void *) arg, 1);
}

void func_ov125_022a0664(void *arg0)
{
    void *r4 = arg0;
    func_ov002_022097b8((char *) r4 + 0x180);
    func_ov125_022a0334(r4);
    func_ov002_02207f20(r4, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov125_022a0564(r4);
    func_ov002_0220ab84((char *) r4 + 0x6a8, 0x65);
    func_ov125_0229f75c(r4, 1);
    func_ov002_02208090(r4, 2);
}

int func_ov125_022a063c(int p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov125_0229fe98(p);
    }
    return func_ov125_022a0564((void *) p);
}

void func_ov125_022a05cc(void *p)
{
    int a, b;

    func_ov125_0229faf8(p);
    a = func_020ee45c(p);
    b = func_0206fca4();
    if (func_ov125_0229f76c(p, 0x10) != 0) {
        func_ov092_02299324(a, 0x44, 1);
    } else {
        if (b == 4) {
            func_ov092_02299324(a, 2, 1);
        } else {
            func_ov092_02299324(a, 0x44, 1);
        }
    }
    func_ov002_02207f04(p, 0xa, 0, 0, 0x30);
    func_ov125_022a0564(p);
    func_ov002_02208090(p, 4);
}

void func_ov125_022a0594(void *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov125_0229f74c(p, 1);
        func_ov002_022080a0((int) p, 5);
    } else {
        func_ov125_022a0564(p);
    }
}

int func_ov125_022a0564(void *p)
{
    int valueResult;

    func_ov002_02207e80(p, 6, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0);
    valueResult = func_ov002_02207f60(p);
    *(int *) ((char *) p + 0x874) = valueResult;
    return valueResult;
}

void func_ov125_022a0510(UnkStruct_022a0510 *self)
{
    self->unk_878 = 0;
    func_ov002_02209984(self->sub180, 3, 1, 0);
    self->unk_87A = 9;
    self->unk_87B = 9;
    self->unk_87C = 0;
    func_0206fc4c(0);
    func_ov002_02207cec(self->sub574, 2);
}

void func_ov125_022a04e4(void *self)
{
    func_ov002_02209178((char *) self + 0x180);
    func_ov124_0229eea0((char *) self + 0x94);
    func_ov002_0220af74((char *) self + 0x6a8);
}
