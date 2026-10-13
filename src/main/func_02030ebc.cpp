/* func_02030ebc @ 0x02030ebc, 0x190 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" {

extern void func_020eaca0(void *dst, const void *a, const void *b);
extern void func_01ffd070(void *dst, const void *a, const void *b);
extern int func_02031c50(void);
extern void func_02034310(void *a, int b, int c, int d, int e, int f);
extern void func_02032d8c(void *a, int b, int c, int d, int e, int f, int g);
extern void func_02031ecc(void *a, int *b, int *c, void *d, void *e, int f, int g);
extern void func_02032d48(void *a, void *b);
extern void func_02033118(void *a, void *b, int c, int d, int e, int f, int g);
extern void func_02033a5c(void *a, void *b, int c, int d, int e, int f);

extern int data_021c4a34;
extern struct {
    u8 pad[0x44];
    int f44;
} data_021c3fe8;
extern struct {
    u8 pad[0x48];
    int f48;
} data_021c49e8;

class UnkStruct_02030ebc {
  public:
    virtual void f0(void *arg);
    virtual void f1(void *arg);
    virtual void f2(void *arg);
};

extern unsigned char data_021c31a0[];
extern unsigned char data_021c3bac[];
extern unsigned char data_021c4030[];
extern unsigned char data_021c4c78[];
extern unsigned char data_021c4c7c[];

void func_02030ebc(void *src0, void *src1, void *obj, int flags, u8 arg5, u8 arg6)
{
    int vecA[3];
    int vecB[3];
    int cross1[3];
    int cross2[3];
    int a0, b0, a2, b2;
    int v0;

    v0 = (flags & 4) ? 1 : 0;

    func_020eaca0(vecA, src0, (void *) data_021c31a0);
    func_01ffd070(vecB, src1, (void *) data_021c31a0);

    a0 = vecA[0] >> 13;
    a2 = vecA[2] >> 13;
    b0 = vecB[0] >> 13;
    b2 = vecB[2] >> 13;

    func_01ffd070(cross1, vecA, vecB);
    cross1[0] >>= 1;
    cross1[1] >>= 1;
    cross1[2] >>= 1;
    func_020eaca0(cross2, vecB, vecA);
    cross2[0] >>= 1;
    cross2[1] >>= 1;
    cross2[2] >>= 1;

    data_021c4a34 = 0;
    data_021c3fe8.f44 = 0;
    data_021c49e8.f48 = 0;

    func_02034310((void *) data_021c4c7c, a0, b0, a2, b2, arg6);

    if ((flags & 7) != 0 && (flags & 0x20) == 0) {
        int r = func_02031c50();
        func_02032d8c(&data_021c4a34, r, a0, b0, a2, b2, v0);
    }

    if ((flags & 0x40) == 0) {
        func_02031ecc((void *) data_021c4c78, cross1, cross2, (void *) data_021c3bac, (void *) data_021c4030, flags, 0);
        func_02031ecc((void *) data_021c4c78, cross1, cross2, (void *) data_021c3bac, (void *) data_021c4030, flags, 1);
    }

    if ((flags & 6) != 0) {
        if ((flags & 0x10) == 0) {
            func_02032d48(&data_021c4a34, (void *) data_021c3bac);
        }
        func_02033118((void *) data_021c3bac, (void *) data_021c4c7c, a0, b0, a2, b2, v0);
    }

    if (arg5 != 0 && flags != 0) {
        func_02033a5c((void *) data_021c4030, (void *) data_021c4c7c, a0, b0, a2, b2);
    }

    UnkStruct_02030ebc *o = (UnkStruct_02030ebc *) obj;
    o->f2(&data_021c4a34);
    o->f0((void *) data_021c3bac);
    o->f1((void *) data_021c4030);
}

} // extern "C"