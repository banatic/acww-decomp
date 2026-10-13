/* func_ov047_022616b4 @ 0x022616b4, 0x218 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x72c];
    u8 unk_72C;
    char pad_72D[0x736 - 0x72d];
    u8 unk_736;
} UnkStruct_022616b4;

typedef struct {
    char pad_00[0xb0];
    int unk_B0;
    UnkStruct_022616b4 *unk_B4;
} UnkStruct_022616b4_2;

typedef struct {
    void *msg;
    u8 unk_04;
} UnkStruct_022616b4_3;

typedef struct {
    u8 ba : 2;
    u8 bx : 3;
    u8 by : 3;
    u8 pad_01;
    u16 unk_02;
} UnkStruct_022616b4_4;

extern int func_020a12e8(void);
extern int func_020984e8(void);
extern int func_02099640(int);
extern int func_0209a850(int);
extern int func_02073d90(void *);
extern short *func_0209d358(int, int);
extern int func_0209af80(int, u16 *);
extern int func_0202ea40(UnkStruct_022616b4 *, UnkStruct_022616b4_4 *, int);
extern int func_0202e9fc(void);
extern int func_0208602c(void);
extern int func_02086108(int, int);
extern void func_020860f0(int, int);
extern int func_02070fa0(void *);

extern void *data_020ccf94;
extern char data_ov047_02262fcc;
extern char data_ov047_02262fc0;
extern char data_ov047_02262fe0;
extern u8 data_ov047_02262818[][6];
extern char data_021f38f8;

void func_ov047_022616b4(UnkStruct_022616b4_2 *p, UnkStruct_022616b4_3 *out)
{
    UnkStruct_022616b4_4 t;
    int h;
    void *w;

    if (func_020a12e8() != 0) {
        out->msg = &data_ov047_02262fcc;
        out->unk_04 = 8;
        return;
    }
    out->msg = &data_ov047_02262fc0;
    h = func_0209a850(func_02099640(func_020984e8()));
    w = data_020ccf94;
    if (func_02073d90(w) == 0 && *func_0209d358(0, 0x4a) == 0) {
        t.unk_02 = 0xd00c;
        if (func_0209af80(h, &t.unk_02) != 0) {
            if (p->unk_B4->unk_736 == 0) {
                out->unk_04 = 0xe6;
            } else {
                out->unk_04 = 0xe5;
            }
            return;
        }
    }

    if (p->unk_B4->unk_72C == 0 && p->unk_B0 != 1 && func_02073d90(w) == 0 && *func_0209d358(0, 0x4a) == 0 &&
        func_0202ea40(p->unk_B4, &t, 1) != 0) {
        out->msg = &data_ov047_02262fe0;
        out->unk_04 = data_ov047_02262818[t.bx][t.by];
        p->unk_B0 = 1;
        p->unk_B4->unk_72C = 1;
        return;
    }

    p->unk_B0 = 0;
    if (func_0202e9fc() == 0) {
        if (func_02086108(func_0208602c(), 9) == 0) {
            if (p->unk_B4->unk_736 != 0) {
                out->unk_04 = 4;
            } else {
                out->unk_04 = 5;
            }
        } else {
            if (p->unk_B4->unk_736 != 0) {
                out->unk_04 = 6;
            } else {
                out->unk_04 = 7;
            }
        }
        func_020860f0(func_0208602c(), 9);
        return;
    }

    if (func_02086108(func_0208602c(), 9) == 0) {
        if (func_02070fa0(&data_021f38f8) != 0) {
            if (p->unk_B4->unk_736 != 0) {
                out->unk_04 = 0;
            } else {
                out->unk_04 = 1;
            }
        } else {
            if (p->unk_B4->unk_736 != 0) {
                out->unk_04 = 8;
            } else {
                out->unk_04 = 9;
            }
        }
        p->unk_B4->unk_736 = 0;
        func_020860f0(func_0208602c(), 9);
        return;
    }

    if (func_02070fa0(&data_021f38f8) != 0) {
        if (p->unk_B4->unk_736 != 0) {
            out->unk_04 = 3;
            p->unk_B4->unk_736 = 0;
        } else {
            out->unk_04 = 2;
        }
    } else {
        if (p->unk_B4->unk_736 != 0) {
            out->unk_04 = 0xa;
            p->unk_B4->unk_736 = 0;
        } else {
            out->unk_04 = 0xb;
        }
    }
}
