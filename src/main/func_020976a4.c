/* func_020976a4 @ 0x020976a4, 0x188 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020976a4 {
    u8 unk_00, unk_01, unk_02, unk_03;
} UnkStruct_020976a4;
typedef struct UnkStruct_020976a4_2 {
    int unk_00, unk_04, unk_08, unk_0C, unk_10, unk_14;
} UnkStruct_020976a4_2;

extern void *data_020ccf94;
extern int data_021f20fc;
extern int data_021dc7bc;

extern int func_02073d90(void *);
extern UnkStruct_020976a4 *func_02097f98(void *);
extern void func_0209e474(UnkStruct_020976a4_2 *);
extern int func_02097f70(void *, int);
extern void func_02097f88(void *, int);
extern void MI_CpuCopy8(int *, int *, int);
extern void func_0209e29c(int *, int);
extern int func_0209e3ac(UnkStruct_020976a4_2 *, int *, int);
extern void func_02097b24(void);
extern int func_020988a4(int *, int);
extern void *func_02098844(int *, int);
extern void *func_02098a18(void *);
extern UnkStruct_020976a4 *func_02097e08(void *);
extern void *func_02097e14(void *);
extern int func_02065ec0(void);
extern int func_02097a74(void *, int, int);
extern void func_02097dd4(void *);

void func_020976a4(void)
{
    void *x;
    void *y;
    UnkStruct_020976a4_2 s;
    UnkStruct_020976a4 *r;
    UnkStruct_020976a4 *e;
    int i;
    unsigned int v;
    void *g;

    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    g = &data_021f20fc;
    r = func_02097f98(g);
    s.unk_00 = 0;
    s.unk_04 = 0;
    func_0209e474(&s);
    s.unk_08 = 0;
    s.unk_0C = 0;
    s.unk_10 = 0;
    s.unk_14 = 0;
    if (func_02097f70(g, 1) != 0) {
        s.unk_08 = 0;
        s.unk_0C = 0;
        ((u8 *) &s)[0xd] = r->unk_02;
        ((u8 *) &s)[0xc] = r->unk_01;
        ((u8 *) &s)[0xb] = r->unk_00;
        MI_CpuCopy8(&s.unk_08, &s.unk_10, 8);
        v = r->unk_03;
        if (v < 9) {
            r->unk_03 = 9;
            ((u8 *) &s)[0x12] = 0x11;
        } else if (v < 0x11) {
            r->unk_03 = 0x11;
            ((u8 *) &s)[0x12] = 9;
            func_0209e29c(&s.unk_10, 1);
        } else {
            r->unk_03 = 9;
            func_0209e29c(&s.unk_08, 1);
            ((u8 *) &s)[0x12] = 0x11;
            func_0209e29c(&s.unk_10, 1);
        }
        ((u8 *) &s)[0xa] = r->unk_03;
        if (func_0209e3ac(&s, &s.unk_08, 0x3c) != -1) {
            func_02097b24();
            if (func_0209e3ac(&s, &s.unk_10, 0x3c) != -1) {
                func_02097b24();
            }
        }
    } else {
        func_02097f88(g, 1);
    }
    for (i = 0; i < 4; i++) {
        if (func_020988a4(&data_021dc7bc, i) == 0) {
            continue;
        }
        x = func_02098844(&data_021dc7bc, i);
        e = func_02097e08(func_02098a18(x));
        y = func_02097e14(func_02098a18(x));
        if (func_02065ec0() == 0) {
            continue;
        }
        s.unk_08 = 0;
        s.unk_0C = 0;
        ((u8 *) &s)[0xd] = e->unk_02;
        ((u8 *) &s)[0xc] = e->unk_01;
        ((u8 *) &s)[0xb] = e->unk_00;
        ((u8 *) &s)[0xa] = 9;
        if (func_0209e3ac(&s, &s.unk_08, 0x3c) == -1) {
            continue;
        }
        if (func_02097a74(y, i, 0) == 0) {
            continue;
        }
        func_02097dd4(func_02098a18(x));
    }
    r->unk_02 = ((u8 *) &s)[5];
    r->unk_01 = ((u8 *) &s)[4];
    r->unk_00 = ((u8 *) &s)[3];
    r->unk_03 = ((u8 *) &s)[2];
}
