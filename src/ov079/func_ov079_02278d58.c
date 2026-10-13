/* func_ov079_02278d58 @ 0x02278d58, 0x614 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Twelve item id checks, each choosing a message code, then a range ladder
// and three panel checks.

typedef struct {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad_44[0xc4 - 0x44];
    u16 unk_C4;
} UnkStruct_02278d58;

typedef struct {
    u8 unk_00;
    u8 pad;
    u16 h[17];
} Msg; // 0x24
typedef struct {
    u8 pad[0x28];
} UnkStruct_02278d58_2;

extern char data_ov079_0227a1b0[];

extern int func_0206fc6c(void);
extern int func_020984e8(void);
extern int func_0206fc8c(void);
extern int func_020996b8(int a);
extern int func_02072ba4(int a);
extern int func_02072b64(int a, int b);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_0204c3f0(u16 *p);
extern int func_020644cc(int a);
extern void func_02071d8c(int a, int b, int c, int d, int e);
extern void func_020154b4(UnkStruct_02278d58 *self, u16 *p, int a, int b, int c);
extern u16 *func_02099710(int a);
extern u16 *func_020996f8(int a);
extern u16 *func_02099728(int a);
extern void func_02095b58(u16 *p);
extern void func_02095b40(u16 *p);
extern void func_02095b1c(u16 *p);
extern int func_02072bd0(int a, int b);
extern void func_02062fbc(UnkStruct_02278d58_2 *o);
extern int func_02072d4c(int a);
extern void func_02072eb8(int a, UnkStruct_02278d58_2 *o);
extern void func_020683b4(void *a, int b, UnkStruct_02278d58_2 *o, int c);
extern void func_02062f4c(UnkStruct_02278d58_2 *o);
extern void func_0206844c(void *a, Msg *m, void *t);

void func_ov079_02278d58(UnkStruct_02278d58 *self)
{
    int s4;
    int s8;
    void *saved;
    int s10;
    int s14;
    int s18;
    int t7;
    int a;
    int r6;
    int code;
    int d;
    int z;
    int cond;
    u16 *pp;
    unsigned int ok;
    Msg msg;
    UnkStruct_02278d58_2 obj;

    saved = self->unk_40;
    msg.unk_00 = 0xd;

    if (func_0206fc6c() != 0) {
        t7 = func_020984e8();
        a = func_0206fc8c();
        r6 = func_02072b64(func_02072ba4(func_020996b8(t7)), a);
        code = 0;

        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[4] = 0x131f;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[4])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x131f) ? 1 : 0;
        }
        if (cond != 0) {
            code = 0x15;
            goto tail;
        }

        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[5] = 0x12ff;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[5])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x12ff) ? 1 : 0;
        }
        if (cond != 0) {
            code = 0x16;
            goto tail;
        }

        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[6] = 0x12f6;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[6])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x12f6) ? 1 : 0;
        }
        if (cond != 0) {
            code = 0x17;
            goto tail;
        }

        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[7] = 0x12f8;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[7])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x12f8) ? 1 : 0;
        }
        if (cond != 0) {
            code = 0x18;
            goto tail;
        }

        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[8] = 0x12fc;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[8])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x12fc) ? 1 : 0;
        }
        if (cond != 0) {
            code = 0x19;
            goto tail;
        }

        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[9] = 0x1309;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[9])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x1309) ? 1 : 0;
        }
        if (cond != 0) {
            code = 0x1a;
            goto tail;
        }

        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[10] = 0x1312;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[10])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x1312) ? 1 : 0;
        }
        if (cond != 0) {
            code = 0x1b;
            goto tail;
        }

        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[11] = 0x131c;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[11])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x131c) ? 1 : 0;
        }
        if (cond != 0) {
            goto d1d;
        }
        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[12] = 0x131d;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[12])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x131d) ? 1 : 0;
        }
        if (cond != 0) {
            goto d1d;
        }
        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[13] = 0x131e;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[13])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x131e) ? 1 : 0;
        }
        if (cond != 0) {
        d1d:
            code = 0x1d;
            goto tail;
        }

        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[14] = 0x1302;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[14])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x1302) ? 1 : 0;
        }
        if (cond != 0) {
            code = 0x1e;
            goto tail;
        }

        if (func_0204bcdc(&self->unk_C4) != 0) {
            msg.h[15] = 0x1303;
            cond = (func_0204bc64(&self->unk_C4) == func_0204bc64(&msg.h[15])) ? 1 : 0;
        } else {
            cond = (self->unk_C4 == 0x1303) ? 1 : 0;
        }
        if (cond != 0) {
            code = 0x1f;
            goto tail;
        }

        ok = 0;
        if (self->unk_C4 >= 0x1548 && self->unk_C4 <= 0x1548) {
            ok = 1;
        }
        if (ok > 0) {
            code = 0xb;
            goto tail;
        }
        if (self->unk_C4 >= 0x1542 && self->unk_C4 <= 0x1546) {
            code = 8;
            goto tail;
        }
        if (self->unk_C4 >= 0x1531 && self->unk_C4 <= 0x153a) {
            code = 0xa;
            goto tail;
        }
        if (func_0204c3f0(&self->unk_C4) == 0) {
            code = (u8) func_020644cc(8);
            goto tail;
        }
        if (func_0204c3f0(&self->unk_C4) == 1) {
            code = (u8) (func_020644cc(9) + 0xc);
            goto tail;
        }
        if (func_0204c3f0(&self->unk_C4) == 2) {
            code = 0x1c;
            goto tail;
        }
        ok = 0;
        if (self->unk_C4 >= 0x1518 && self->unk_C4 <= 0x151c) {
            ok = 1;
        }
        if (ok > 0) {
            code = 9;
        }

    tail:
        func_02071d8c(7, code, 9, r6, 1);
        msg.unk_00 = 5;
        msg.h[0] = 0x3530;
        func_020154b4(self, &msg.h[0], 0, 5, 0);

        if ((unsigned int) r6 < 8) {
            s8 = (u16) (0x12a8 + r6);
        } else {
            s8 = 0x12a8;
        }
        if ((unsigned int) r6 < 8) {
            s4 = (u16) (0x1429 + r6);
        } else {
            s4 = 0x1429;
        }
        if ((unsigned int) r6 < 8) {
            d = (u16) (0x13a0 + r6);
        } else {
            d = 0x13a0;
        }

        s10 = *func_02099710(t7);
        s14 = *func_020996f8(t7);
        s18 = *func_02099728(t7);

        if (s8 == s10) {
            pp = func_02099710(t7);
            ok = 0;
            if (*pp >= 0x12a8 && *pp <= 0x12af) {
                ok = 1;
            }
            if (ok != 0) {
                msg.h[1] = (u16) s8;
                func_02095b58(&msg.h[1]);
            }
        }
        if (s4 == s14) {
            pp = func_020996f8(t7);
            ok = 0;
            if (*pp >= 0x1429 && *pp <= 0x1430) {
                ok = 1;
            }
            if (ok != 0) {
                msg.h[2] = (u16) s4;
                func_02095b40(&msg.h[2]);
            }
        }
        if (d == s18) {
            pp = func_02099728(t7);
            ok = 0;
            if (*pp >= 0x13a0 && *pp <= 0x13a7) {
                ok = 1;
            }
            if (ok != 0) {
                msg.h[3] = (u16) d;
                func_02095b1c(&msg.h[3]);
            }
        }

        z = func_02072bd0(func_020996b8(t7), r6);
        func_02062fbc(&obj);
        func_02072eb8(func_02072d4c(z), &obj);
        func_020683b4(self->unk_40, 1, &obj, 7);
        func_02062f4c(&obj);
    }

    func_0206844c(saved, &msg, data_ov079_0227a1b0);
}
