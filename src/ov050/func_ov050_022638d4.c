/* func_ov050_022638d4 @ 0x022638d4, 0x264 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 kind;
    u8 pad_01;
    volatile u16 id;
    u16 id2;
} Msg;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x70];
    void *unk_B4;
    char pad_B8[8];
    int unk_C0;
    int unk_C4;
} UnkStruct_022638d4;

extern char data_021f3b0c[];
extern char data_ov050_02265824[];
extern char data_ov050_02265804[];

extern int func_0206fc6c(void);
extern u16 *func_0206faf0(void);
extern int func_0204c878(u16 *p);
extern int func_020984e8(void);
extern int func_0209ded0(void);
extern int func_020874c4(char *p);
extern void func_02015fb0(UnkStruct_022638d4 *self, int a, int b, int c, int d, int e);
extern int func_ov050_02260510(void *h);
extern void func_0206844c(void *a, Msg *m, char *t);

void func_ov050_022638d4(UnkStruct_022638d4 *self)
{
    Msg msg;
    u16 *list;
    int flagA;
    int flagB;
    int flagC;
    int i;
    unsigned int ok;
    u16 hi;
    u16 lo;
    unsigned int idx;
    void *h;
    int mul;

    h = self->unk_40;
    msg.kind = 8;
    self->unk_C4 = 0;
    self->unk_C0 = 0;
    if (func_0206fc6c() != 0) {
        list = func_0206faf0();
        flagA = 0;
        flagB = 0;
        flagC = 0;
        msg.id = 0xfff1;
        for (i = flagA; i < 0xf; i++) {
            if (list[i] == 0xfff1) {
                break;
            }
            msg.id = list[i];
            ok = 0;
            hi = msg.id;
            lo = msg.id;
            if (lo >= 0x136a && hi <= 0x136a) {
                ok = 1;
            }
            if (ok > 0 || (hi >= 0x1373 && hi <= 0x1373) || (hi >= 0x1375 && hi <= 0x1375) || (hi >= 0x1377 && hi <= 0x1377) ||
                (hi >= 0x1379 && hi <= 0x1379) || (hi >= 0x137b && hi <= 0x137b)) {
                flagA = 1;
            }
            if (hi >= 0x38e4 && hi <= 0x3933) {
                flagC = 1;
                idx = (hi >= 0x38e4 && hi <= 0x3933) ? ((hi - 0x38e4) >> 2) : -1;
                msg.id2 = (u16) ((idx < 0x14) ? (idx * 4 + 0x3934) : 0x3934);
                self->unk_C4 = self->unk_C4 + func_0204c878(&msg.id2) / 4;
            } else if (func_020984e8() != 0) {
                ok = 0;
                hi = msg.id;
                lo = msg.id;
                if (lo >= 0x1531 && hi <= 0x153a) {
                    ok = 1;
                }
                if (ok > 0) {
                    if (func_0209ded0() == 0) {
                        flagB = 1;
                    } else {
                        mul = func_020874c4(data_021f3b0c);
                        self->unk_C4 = self->unk_C4 + func_0204c878((u16 *) &msg.id) * mul;
                    }
                } else {
                    self->unk_C4 = self->unk_C4 + func_0204c878((u16 *) &msg.id) / 4;
                }
            }
        }
        if (flagB == 1) {
            msg.kind = 0xd;
        } else if (flagA == 1) {
            func_02015fb0(self, self->unk_C4, 0, 0xa, 0, 0);
            msg.kind = 0x11;
        } else if (flagC == 1) {
            msg.kind = 0x40;
            func_02015fb0(self, self->unk_C4, 0, 0xa, 0, 0);
        } else if (self->unk_C4 == 0) {
            msg.kind = 0xa;
        } else {
            msg.kind = 0xe;
            func_02015fb0(self, self->unk_C4, 0, 0xa, 0, 0);
        }
    } else {
        msg.kind = 8;
    }
    if (func_ov050_02260510(self->unk_B4) != 0) {
        func_0206844c(h, &msg, data_ov050_02265824);
    } else {
        func_0206844c(h, &msg, data_ov050_02265804);
    }
}
