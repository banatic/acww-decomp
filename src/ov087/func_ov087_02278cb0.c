/* func_ov087_02278cb0 @ 0x02278cb0, 0x254 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 kind;
    u8 pad;
    volatile u16 h[6];
} Msg;

typedef struct {
    u16 a;
    u8 b;
    u8 pad;
} UnkStruct_02278cb0;

typedef struct {
    u8 pad_00[0x1e];
    u8 unk_1E;
    u8 pad_1F[0x40 - 0x1f];
    void *unk_40;
} UnkStruct_02278cb0_2;

extern UnkStruct_02278cb0 data_ov087_02279324[];
extern char data_ov087_02279598;
extern int func_ov087_02278f04(unsigned short *r0, int r1);

extern int func_020984e8(void);
extern void *func_02099670(int);
extern unsigned short func_0206f9d8(int (*cb)(unsigned short *, int));
extern u16 func_0209a034(int);
extern void func_02015fb0(UnkStruct_02278cb0_2 *, int, int, int, int, int);
extern unsigned int func_02088b94(void *);
extern unsigned int func_02088ba8(void *);
extern void func_02088b80(void *);
extern void func_02015de4(UnkStruct_02278cb0_2 *, u16 *, int, int);
extern int func_020154b4(UnkStruct_02278cb0_2 *, u16 *, int, int, int);
extern int func_0209a000(u16 *, int);
extern void func_0206844c(void *, Msg *, void *);

void func_ov087_02278cb0(UnkStruct_02278cb0_2 *self)
{
    void *ctx = func_02099670(func_020984e8());
    Msg m;
    u8 message;

    m.h[0] = 0xfff1;
    message = 0xff;

    switch (self->unk_1E) {
        case 2:
        case 3:
            if (func_0206f9d8(func_ov087_02278f04) != 0) {
                int i = 0;
                int count = 0;
                int ok;
                u16 lo, hi;
                do {
                    m.h[0] = func_0209a034(i);
                    ok = 0;
                    lo = m.h[0];
                    hi = m.h[0];
                    if (hi >= 0x1542 && lo <= 0x1546) {
                        ok = 1;
                    }
                    if (ok != 0) {
                        count++;
                    }
                    i++;
                } while (i < 15);
                func_02015fb0(self, count, 2, 3, 0, 0);
                message = 5;
            } else if (func_02088b94(ctx) >= 0xc) {
                message = 0x17;
            } else {
                int d = data_ov087_02279324[func_02088b94(ctx)].b - func_02088ba8(ctx);
                if (d > 0) {
                    func_02015fb0(self, d, 1, 3, 0, 0);
                    message = 4;
                } else {
                    message = 0x16;
                }
            }
            break;
        case 7:
        case 8:
        case 9:
            func_02015fb0(self, func_02088ba8(ctx), 0, 3, 0, 0);
            if (func_02088b94(ctx) >= 0xc) {
                message = 0x16;
            } else {
                message = 0xa;
            }
            break;
        case 10:
            if (func_02088ba8(ctx) >= data_ov087_02279324[func_02088b94(ctx)].b) {
                m.h[1] = data_ov087_02279324[func_02088b94(ctx)].a;
                func_02015de4(self, (u16 *) &m.h[1], 0, 7);
                message = 0xb;
            } else {
                int d = data_ov087_02279324[func_02088b94(ctx)].b - func_02088ba8(ctx);
                func_02015fb0(self, d, 1, 3, 0, 0);
                message = 0xf;
            }
            break;
        case 11:
        case 13:
            m.h[2] = data_ov087_02279324[func_02088b94(ctx)].a;
            {
                int ok;
                if (func_0209a000((u16 *) &m.h[2], 0) == 0) {
                    ok = 1;
                } else {
                    ok = 0;
                }
                if (ok != 0) {
                    message = 0xc;
                    break;
                }
            }
            func_02088b80(ctx);
            m.h[3] = data_ov087_02279324[func_02088b94(ctx)].a;
            func_020154b4(self, (u16 *) &m.h[3], 0, 5, 0);
            if (func_02088b94(ctx) < 0xc && func_02088ba8(ctx) >= data_ov087_02279324[func_02088b94(ctx)].b) {
                m.h[4] = data_ov087_02279324[func_02088b94(ctx)].a;
                func_02015de4(self, (u16 *) &m.h[4], 0, 7);
                message = 0xd;
            } else {
                message = 0xe;
            }
            break;
        case 20:
            m.h[5] = 0x1565;
            func_020154b4(self, (u16 *) &m.h[5], 0, 5, 0);
            message = 0x15;
            break;
    }

    if (message != 0xff) {
        m.kind = message;
        func_0206844c(self->unk_40, &m, &data_ov087_02279598);
    }
}
