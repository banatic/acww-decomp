/* turtle_fishing_talk: 2 functions, module ov081
 * mwccarm 1.2/base -O4,s
 * func_ov081_02278b68 @ 0x02278b68, 0x240 bytes, Thumb
 * func_ov081_02278ab8 @ 0x02278ab8, 0xb0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x724];
    int unk_724;
} UnkStruct_02278b68;

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    UnkStruct_02278b68 *unk_B0;
    char pad_B4[0xc4 - 0xb4];
    short unk_C4;
    u8 unk_C6;
    char pad_C7[1];
    int unk_C8;
} UnkStruct_02278b68_3;

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
} UnkStruct_02278b68_4;

typedef struct {
    int a;
    int b;
} UnkStruct_02278b68_2;

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x21];
    void *unk_40;
    unsigned char pad_44[0x84];
    int unk_C8;
} UnkStruct_02278ab8;

extern int func_020154b4(void *, u16 *, int, int, int);
extern int func_0209a000(u16 *, int);
extern void func_0206844c(int, u8 *, void *);
extern int func_02015094(UnkStruct_02278b68_3 *);
extern int func_020984e8(void);
extern int func_02099670(int);
extern void func_02088b38(int, int);
extern int func_02086744(void *);
extern int func_ov081_02278da8(UnkStruct_02278b68_3 *);
extern void func_02086754(void *, void *);
extern void func_02086748(void *, int);
extern int func_02099870(int);
extern void func_020867e4(void *, int);
extern void func_02086834(void *, int);
extern void func_0209f128(void *, int);
extern void func_02063ccc(UnkStruct_02278b68_2 *, int, int);
extern void func_020638d4(u16 *, UnkStruct_02278b68_2 *, int, int, int, int, int);
extern void func_02063cc8(UnkStruct_02278b68_2 *);
extern void func_02015de4(UnkStruct_02278b68_3 *, u16 *, int, int);
extern int func_0202ea80(int, int);
extern void func_020157d4(UnkStruct_02278b68_3 *, void *, int, int);
extern int func_02015828(UnkStruct_02278b68_3 *, int);
extern void func_ov081_0227915c(UnkStruct_02278b68_3 *, int);
extern unsigned short func_ov081_02279124(void *argument0, int argument1);
extern char data_021f3aa4;
extern char data_021dc7a8;
extern unsigned char data_ov081_02279868[];
extern unsigned char data_ov081_02279878[];
int func_020160b4(void *self);
int func_020ab504(void *argument0);
void func_0209a050(int val);
int func_02015330(void *self, void *cmd, int a, int b, int c);

void func_ov081_02278b68(UnkStruct_02278b68_3 *p)
{
    UnkStruct_02278b68_4 m;
    int code;
    int n;
    void *q;
    void *tbl;

    tbl = ((char *) data_ov081_02279868);
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
            func_0206844c(p->unk_40, &m.unk_00, ((char *) data_ov081_02279878));
        }
        return;
    }

    if (p->unk_1E == 0xd || p->unk_1E == 0x10 || p->unk_1E == 0x13) {
        m.unk_02 = 0xfff1;
        q = &data_021f3aa4;
        switch (p->unk_1E) {
            case 0xd:
                func_02015094(p);
                func_02088b38(func_02099670(func_020984e8()), 1);
                n = func_02086744(q);
                if ((10 * p->unk_B0->unk_724) >> 12 > (10 * n) >> 12) {
                    code = 0x10;
                } else if (func_ov081_02278da8(p) == 0) {
                    code = 0x16;
                } else if (func_ov081_02278da8(p) > 0) {
                    code = 0xe;
                }
                break;
            case 0x10:
                if (func_ov081_02278da8(p) == 0) {
                    code = 0x11;
                    p->unk_C6 = 1;
                } else if (func_ov081_02278da8(p) > 0) {
                    code = 0x12;
                    p->unk_C6 = 0;
                }
                break;
            case 0x13:
                if (p->unk_C6 != 0) {
                    code = 0x14;
                } else {
                    code = 0x15;
                }
                func_02086754(q, &p->unk_C4);
                func_02086748(q, p->unk_B0->unk_724);
                func_020867e4(q, func_02099870(func_020984e8()));
                func_02086834(q, 1);
                func_0209f128(&data_021dc7a8, 0xf);
                func_02063ccc((UnkStruct_02278b68_2 *) &m.unk_10, 0, 0);
                func_020638d4(&m.unk_08, (UnkStruct_02278b68_2 *) &m.unk_10, 0, 0, 1, 1, 0);
                m.unk_02 = m.unk_08;
                func_02063cc8((UnkStruct_02278b68_2 *) &m.unk_10);
                func_020154b4(p, &m.unk_02, 0, 5, 0);
                func_02015de4(p, &m.unk_02, 0, 7);
                func_0209a000(&m.unk_02, 0);
                break;
        }
    }

    switch (p->unk_1E) {
        case 1:
            m.unk_0A = 0x1374;
            func_020154b4(p, &m.unk_0A, 0, 5, 0);
            m.unk_0C = 0x1374;
            func_0209a000(&m.unk_0C, 0);
            code = 4;
            func_0202ea80(0x1b, 1);
            break;
        case 0xb:
            func_020157d4(p, (void *) &func_ov081_02279124, 0xd, 1);
            func_02015828(p, 0);
            func_ov081_0227915c(p, 0);
            break;
    }

    if (code != 0xff) {
        m.unk_01 = (u8) code;
        func_0206844c(p->unk_40, &m.unk_01, tbl);
    }
}

void func_ov081_02278ab8(UnkStruct_02278ab8 *self)
{
    int t;
    int val;
    unsigned char cmd[4];
    unsigned char *p;
    int r4;

    t = func_020ab504((void *) func_020160b4(self));
    p = data_ov081_02279868;
    r4 = 0xff;
    val = self->unk_C8;

    if (val < 0) {
        goto L16;
    }

    p = data_ov081_02279878;
    if (self->unk_1E != 0) {
        goto L2;
    }
    if (t != 0) {
        goto L2;
    }
    if (val < 0) {
        goto L0;
    }

    func_0209a050(val);
    *(unsigned short *) (cmd + 2) = 0x37e0;
    func_02015330(self, cmd + 2, 0, 5, 0);

L0:
    r4 = 2;
L2:
    if (r4 != 0xff) {
        cmd[0] = (unsigned char) r4;
        func_0206844c((int) self->unk_40, (u8 *) cmd, (void *) p);
    }
    return;

L16:
    if (self->unk_1E == 8) {
        if (t != 0) {
            if (func_ov081_02278da8((UnkStruct_02278b68_3 *) self) == 0) {
                r4 = 9;
            } else if (func_ov081_02278da8((UnkStruct_02278b68_3 *) self) > 0) {
                r4 = 10;
            }
        } else {
            r4 = 11;
        }
    }
    if (r4 != 0xff) {
        cmd[1] = (unsigned char) r4;
        func_0206844c((int) self->unk_40, (u8 *) (cmd + 1), (void *) p);
    }
}
