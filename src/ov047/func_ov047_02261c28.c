/* func_ov047_02261c28 @ 0x02261c28, 0x27c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261c28 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xc8 - 0x44];
    int unk_C8;
    u8 unk_CC;
    char pad_CD[1];
    u16 unk_CE;
} UnkStruct_02261c28;

extern int func_0206fc6c(void);
extern int func_0206fc8c(void);
extern void *func_02094fd4(void *);
extern void *func_02094fbc(void *);
extern int func_0209a034(int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern void func_02015de4(UnkStruct_02261c28 *, u16 *, int, int);
extern int func_02071298(void *, u16 *);
extern int func_020712b0(void *, u16 *);
extern int func_02070fe4(void *, void *, u16 *);
extern void func_02068404(int, int, void *);
extern int func_020644cc(int);
extern void func_0209a088(u16 *, int, int);
extern int func_02015330(UnkStruct_02261c28 *, u16 *, int, int, int);
extern int func_020155cc(UnkStruct_02261c28 *);
extern void func_ov047_02261f74(UnkStruct_02261c28 *, int);
extern void func_0206844c(int, u8 *, int);
extern int data_ov047_02262fc0;
extern char data_021f38f8[];

void func_ov047_02261c28(UnkStruct_02261c28 *self)
{
    struct {
        u8 code;
        u8 pad;
        u16 sent;
    } m;
    char buf[0x20];
    int h;
    int ok;
    int flag;
    int t;
    int w;
    void *tbl;

    h = self->unk_40;
    m.code = 0x22;
    if (func_0206fc6c() != 0) {
        func_02094fd4(buf);
        self->unk_C8 = -1;
        self->unk_C8 = func_0206fc8c();
        self->unk_CE = (u16) func_0209a034(self->unk_C8);
        if (func_0204bcdc(&self->unk_CE) != 0) {
            m.sent = 0xfff1;
            t = func_0204bc64(&self->unk_CE);
            if (t == func_0204bc64(&m.sent)) {
                ok = 1;
            } else {
                ok = 0;
            }
        } else {
            ok = (self->unk_CE == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            func_02015de4(self, &self->unk_CE, 0, 7);
            flag = 0;
            if (self->unk_CE >= 0x1549 && self->unk_CE <= 0x1549) {
                flag = 1;
            }
            if (flag != 0) {
                m.code = 0x21;
            } else {
                tbl = data_021f38f8;
                if (func_02071298(tbl, &self->unk_CE) == 0) {
                    flag = 0;
                    if (self->unk_CE >= 0x450c && self->unk_CE <= 0x45db) {
                        flag = 1;
                    }
                    if (flag != 0) {
                        self->unk_CC = 0;
                        m.code = 0x25;
                    } else if (self->unk_CE >= 0x3894 && self->unk_CE <= 0x38e3) {
                        m.code = (u8) (func_020644cc(3) + 0x2e);
                    } else if (self->unk_CE >= 0x12b0 && self->unk_CE <= 0x12e7) {
                        if (self->unk_CE >= 0x12b0 && self->unk_CE <= 0x12e7) {
                            w = self->unk_CE - 0x12b0;
                        } else {
                            w = -1;
                        }
                        if (w != 0x34) {
                            m.code = 0x32;
                        } else {
                            m.code = 0x33;
                        }
                    } else if (self->unk_CE >= 0x12e8 && self->unk_CE <= 0x131f) {
                        m.code = 0x35;
                    } else if (self->unk_CE >= 0x38e4 && self->unk_CE <= 0x3933) {
                        if (self->unk_CE >= 0x38e4 && self->unk_CE <= 0x3933) {
                            w = (self->unk_CE - 0x38e4) >> 2;
                        } else {
                            w = -1;
                        }
                        if ((unsigned int) w < 0x14) {
                            t = 0x3934 + w * 4;
                        } else {
                            t = 0x3934;
                        }
                        self->unk_CE = (u16) t;
                        if (self->unk_C8 >= 0) {
                            func_0209a088(&self->unk_CE, 0, self->unk_C8);
                        }
                        m.code = 0x42;
                    } else if (self->unk_CE >= 0x3934 && self->unk_CE <= 0x3983) {
                        m.code = 0x43;
                    }
                } else {
                    switch (func_020712b0(tbl, &self->unk_CE)) {
                        case 0:
                            m.code = 0x39;
                            break;
                        case 1:
                            if (func_02070fe4(tbl, buf, &self->unk_CE) != 0) {
                                func_02068404(h, 0, buf);
                            }
                            m.code = 0x38;
                            break;
                        case 2:
                            m.code = 0x37;
                            break;
                    }
                }
            }
            func_02015330(self, &self->unk_CE, 0, 0xa, 0);
            func_ov047_02261f74(self, 4);
        }
        func_02094fbc(buf);
    } else {
        self->unk_CE = 0xfff1;
        func_020155cc(self);
    }
    func_0206844c(h, &m.code, (int) &data_ov047_02262fc0);
}
