/* func_ov084_02278ab8 @ 0x02278ab8, 0x160 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off

typedef struct UnkStruct_02278ab8 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_02278ab8;

typedef struct Msg {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u16 unk_06;
    u16 unk_08;
} Msg;

typedef struct UnkStruct_02278ab8_2 {
    int a;
    int b;
} UnkStruct_02278ab8_2;

extern int func_020160b4(void *arg0);
extern int func_020ab504(int);
extern void func_0209a050(int);
extern int func_02015330(UnkStruct_02278ab8 *, u16 *, int, int, int);
extern void func_0206844c(void *, u8 *, const void *);
extern int func_0209a1e8(void);
extern int func_0209a1d0(void);
extern int func_020984e8(void);
extern void *func_020a8228(int *);
extern void *func_020a8210(int *);
extern int func_020644cc(int);
extern int func_020b4a20(int *, u8 *, int);
extern int func_0203d7c4(int, int *);
extern int func_02099870(int);
extern void func_02066024(int, u8 *, const void *, const void *, const void *, int);
extern u16 func_0204bd20(int, int);
extern int func_020996ac(int);
extern int OS_UnlockByWord_IrqAndFiq(int object, u16 *item, int mode);
extern int func_0208602c(void);
extern void func_020860f0(int, int);
extern UnkStruct_02278ab8_2 data_ov084_022792fc[];
extern const int data_ov084_02279568;
extern const int data_ov084_02279380;
extern const int data_ov084_02279578;
extern const int data_ov084_02279384;
extern const int data_ov084_02279558;

void func_ov084_02278ab8(UnkStruct_02278ab8 *this)
{
    Msg m;
    int blk2[0x17];
    int ok = func_020ab504(func_020160b4((void *) this));
    int code = 0xff;
    int v = this->unk_B4;
    int q;
    int a;
    int w;
    int t;
    int n;
    int i;
    UnkStruct_02278ab8_2 *e;

    if (v >= 0) {
        const void *tag = (const void *) &data_ov084_02279568;
        if (this->unk_1E == 0 && ok == 0) {
            if (v >= 0) {
                func_0209a050(v);
                m.unk_06 = 0x37e0;
                func_02015330(this, &m.unk_06, 0, 5, 0);
            }
            code = 2;
        }
        if (code != 0xff) {
            m.unk_01 = (u8) code;
            func_0206844c(this->unk_40, &m.unk_01, tag);
        }
        return;
    }

    if (this->unk_1E == 7 && ok == 0) {
        code = 0xc;
        if (func_0209a1e8() != -1) {
            q = func_0209a1d0();
            if (q != 0) {
                code = 9;
                a = func_020984e8();
                m.unk_00 = 2;
                func_020a8228(blk2);
                t = func_020644cc(4);
                w = t + 8;
                i = 0;
                n = w;
                for (; i < 4; i++) {
                    m.unk_00 = (u8) n;
                    e = &data_ov084_022792fc[i];
                    func_020b4a20(blk2, &m.unk_00, e->a);
                    func_0203d7c4(e->b, blk2);
                    n = (w - 8) * 4;
                    n += func_020644cc(4);
                    n += i * 16;
                }
                m.unk_00 = 1;
                func_02066024(q, &m.unk_00, (const void *) &data_ov084_02279578, (const void *) &data_ov084_02279384,
                              (const void *) &data_ov084_02279380, func_02099870(a));
                if (a != 0) {
                    m.unk_08 = func_0204bd20(0x1d, 4);
                    OS_UnlockByWord_IrqAndFiq(func_020996ac(a), &m.unk_08, 0);
                }
                func_020860f0(func_0208602c(), 3);
                func_020a8210(blk2);
            }
        }
    }

    if (code != 0xff) {
        m.unk_04 = (u8) code;
        func_0206844c(this->unk_40, &m.unk_04, (const void *) &data_ov084_02279558);
    }
}
