/* func_ov082_02278b64 @ 0x02278b64, 0x288 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x724];
    int unk_724;
} UnkStruct_02278b64;

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    UnkStruct_02278b64 *unk_B0;
    char pad_B4[0xc4 - 0xb4];
    short unk_C4;
    u8 unk_C6;
    char pad_C7[1];
    int unk_C8;
} UnkStruct_02278b64_3;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    int unk_10;
    int unk_14;
} UnkStruct_02278b64_4;
typedef struct {
    int a;
    int b;
} UnkStruct_02278b64_2;

extern void func_020154b4(void *, u16 *, int, int, int);
extern void func_0209a000(u16 *, int);
extern void func_0206844c(int, u8 *, void *);
extern int func_02015094(UnkStruct_02278b64_3 *);
extern int func_020984e8(void);
extern int func_02099670(int);
extern int func_02088b1c(int, int);
extern void func_0208674c(u16 *, void *);
extern int func_02086744(void *);
extern int func_ov082_02278dec(UnkStruct_02278b64_3 *);
extern void func_02086754(void *, void *);
extern void func_02086748(void *, int);
extern int func_02099870(int);
extern void func_020867e4(void *, int);
extern void func_02086834(void *, int);
extern void func_0209f128(void *, int);
extern void func_02063ccc(UnkStruct_02278b64_2 *, int, int);
extern void func_020638d4(u16 *, UnkStruct_02278b64_2 *, int, int, int, int, int);
extern void func_02063cc8(UnkStruct_02278b64_2 *);
extern void func_02015de4(UnkStruct_02278b64_3 *, u16 *, int, int);
extern int func_0202ea80(int, int);
extern void func_020157d4(UnkStruct_02278b64_3 *, void *, int, int);
extern void func_02015828(UnkStruct_02278b64_3 *, int);
extern void func_ov082_022791a0(UnkStruct_02278b64_3 *, int);
extern void func_ov082_02279168(void);

extern char data_ov082_022798c8;
extern char data_ov082_022798d8;
extern char data_021f3aa4;
extern char data_021dc7a8;

void func_ov082_02278b64(UnkStruct_02278b64_3 *p)
{
    UnkStruct_02278b64_4 m;
    int code;
    int n;
    int ok;
    u16 va;
    u16 vb;
    void *q;
    void *tbl;

    tbl = &data_ov082_022798c8;
    code = 0xff;
    if (p->unk_C8 >= 0) {
        if (p->unk_1E == 1 || p->unk_1E == 4) {
            p->unk_C8 = ~1;
        }
        if (p->unk_1E == 2) {
            m.unk_04 = 0x1559;
            func_020154b4(p, &m.unk_04, 0, 5, 0);
            m.unk_06 = 0x1559;
            func_0209a000(&m.unk_06, 0);
            m.unk_00 = 4;
            func_0206844c(p->unk_40, &m.unk_00, &data_ov082_022798d8);
        }
        return;
    }

    if (p->unk_1E == 0xd || p->unk_1E == 0x10 || p->unk_1E == 0x13 || p->unk_1E == 0x16) {
        m.unk_02 = 0xfff1;
        q = &data_021f3aa4;
        switch (p->unk_1E) {
            case 0xd:
                func_02015094(p);
                func_0208674c(&m.unk_08, q);
                ok = 0;
                va = *(volatile u16 *) &m.unk_08;
                vb = *(volatile u16 *) &m.unk_08;
                if (vb >= 0x12b0 && va <= 0x12e7) {
                    ok = 1;
                }
                if (ok == 0) {
                    code = 0x16;
                    break;
                }
                func_02088b1c(func_02099670(func_020984e8()), 1);
                n = func_02086744(q);
                if (p->unk_B0->unk_724 >> 12 > n >> 12) {
                    code = 0x10;
                } else if (func_ov082_02278dec(p) == 0) {
                    code = 0x1d;
                } else if (func_ov082_02278dec(p) > 0) {
                    code = 0xe;
                }
                break;
            case 0x10:
                if (func_ov082_02278dec(p) == 0) {
                    code = 0x11;
                    p->unk_C6 = 1;
                } else if (func_ov082_02278dec(p) > 0) {
                    code = 0x12;
                    p->unk_C6 = 0;
                }
                break;
            case 0x13:
            case 0x16:
                if (p->unk_C6 != 0) {
                    code = 0x14;
                } else {
                    code = 0x15;
                }
                func_02086754(q, &p->unk_C4);
                func_02086748(q, p->unk_B0->unk_724);
                func_020867e4(q, func_02099870(func_020984e8()));
                func_02086834(q, 2);
                func_0209f128(&data_021dc7a8, 0xf);
                func_02063ccc((UnkStruct_02278b64_2 *) &m.unk_10, 0, 0);
                func_020638d4(&m.unk_0A, (UnkStruct_02278b64_2 *) &m.unk_10, 0, 0, 1, 1, 0);
                m.unk_02 = m.unk_0A;
                func_02063cc8((UnkStruct_02278b64_2 *) &m.unk_10);
                func_020154b4(p, &m.unk_02, 0, 5, 0);
                func_02015de4(p, &m.unk_02, 0, 7);
                func_0209a000(&m.unk_02, 0);
                break;
        }
    }

    switch (p->unk_1E) {
        case 1:
            m.unk_0C = 0x1376;
            func_020154b4(p, &m.unk_0C, 0, 5, 0);
            m.unk_0E = 0x1376;
            func_0209a000(&m.unk_0E, 0);
            code = 4;
            func_0202ea80(0x1c, 1);
            break;
        case 0xb:
            func_020157d4(p, (void *) &func_ov082_02279168, 0xd, 1);
            func_02015828(p, 0);
            func_ov082_022791a0(p, 0);
            break;
    }

    if (code != 0xff) {
        m.unk_01 = (u8) code;
        func_0206844c(p->unk_40, &m.unk_01, tbl);
    }
}
