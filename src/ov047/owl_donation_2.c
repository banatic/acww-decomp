/* owl_donation_2: 8 functions, module ov047
 * mwccarm 1.2/base -O4,s
 * func_ov047_02261ea4 @ 0x02261ea4, 0xd0 bytes, Thumb
 * func_ov047_02261c28 @ 0x02261c28, 0x27c bytes, Thumb
 * func_ov047_02261c20 @ 0x02261c20, 0x8 bytes, Thumb
 * func_ov047_02261c00 @ 0x02261c00, 0x20 bytes, Thumb
 * func_ov047_02261b88 @ 0x02261b88, 0x78 bytes, Thumb
 * func_ov047_02261b10 @ 0x02261b10, 0x78 bytes, Thumb
 * func_ov047_02261ae8 @ 0x02261ae8, 0x28 bytes, Thumb
 * func_ov047_02261a24 @ 0x02261a24, 0xc4 bytes, Thumb
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

typedef struct UnkStruct_02261b88 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xc8 - 0x44];
    int unk_C8;
    char pad_CC[0xce - 0xcc];
    u16 unk_CE;
} UnkStruct_02261b88;

struct UnkStruct_02261b10 {
    char pad_00[0x40];
    void *unk_40;
};

typedef struct UnkStruct_02261a24 {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02261a24;

typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
} Msg;

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
extern int func_02070dc0(void *);
extern int func_02070fa0(void *);
extern int func_020984e8(void);
extern int func_0202e9fc(void);
extern void func_0209a050(int a);
extern int func_02099640(int t);
extern int func_0209a850(int a);
extern void *func_0209b0f0(void *record);
extern void func_0209bb90(void *a, int b);

int func_ov047_02261ea4(u16 *p, int flag)
{
    // DECLS
    unsigned int a;
    u16 v;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    unsigned int e;
    unsigned int g;
    unsigned int h;
    // ENDDECLS

    if (flag == 0) {
        a = 0;
        v = *p;
        if (v >= 0x450c && v <= 0x45db) {
            a = 1;
        }
        b = (v >= 0x3934 && v <= 0x3983) ? 1 : 0;
        c = (v >= 0x38e4 && v <= 0x3933) ? 1 : 0;
        d = (v >= 0x12e8 && v <= 0x131f) ? 1 : 0;
        e = (v >= 0x12b0 && v <= 0x12e7) ? 1 : 0;
        g = (v >= 0x3894 && v <= 0x38e3) ? 1 : 0;
        h = (v >= 0x1549 && v <= 0x1549) ? 1 : 0;
        return h | a | g | e | d | c | b;
    }
    return 0;
}

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

void func_ov047_02261c20(int argument0)
{
    func_020155cc((UnkStruct_02261c28 *) argument0);
}

int func_ov047_02261c00(unsigned short *r0, int r1)
{
    int result;
    unsigned short val;

    if (r1 == 0) {
        result = 0;
        val = *r0;
        if (val >= 0x1549 && val <= 0x1549) {
            result = 1;
        }
        return result;
    } else {
        return 0;
    }
}

void func_ov047_02261b88(UnkStruct_02261b88 *self)
{
    int h;
    u8 code;

    h = self->unk_40;
    code = 0x22;
    if (func_0206fc6c() != 0) {
        self->unk_C8 = func_0206fc8c();
        self->unk_CE = (u16) func_0209a034(self->unk_C8);
        func_02015330((UnkStruct_02261c28 *) self, &self->unk_CE, 0, 0xa, 0);
        code = 0x19;
    } else {
        self->unk_CE = 0xfff1;
        func_020155cc((UnkStruct_02261c28 *) self);
    }
    func_ov047_02261f74((UnkStruct_02261c28 *) self, 4);
    func_0206844c(h, &code, (int) &data_ov047_02262fc0);
}

void func_ov047_02261b10(struct UnkStruct_02261b10 *param)
{
    void *field40;
    void *addr;
    char byte;
    int ret;

    field40 = param->unk_40;
    if (func_0206fc6c() != 0) {
        byte = 0x13;
        addr = ((int *) data_021f38f8);
        ret = func_02070dc0(addr);
        if (ret == 0) {
            byte = 0x10;
        } else if (ret <= 0x0001e000) {
            byte = 0x11;
        } else if (ret <= 0x00046000) {
            byte = 0x12;
        } else if (func_02070fa0(addr) != 0) {
            byte = 0x49;
        }
        func_0206844c((int) field40, (u8 *) (&byte), (int) (((char *) &data_ov047_02262fc0)));
    }
}

unsigned short func_ov047_02261ae8(void *r0, int r1)
{
    unsigned short result;
    unsigned short value;

    if (r1 == 2) {
        result = 0;
        value = *(unsigned short *) r0;
        if (value >= 0x155f && value <= 0x1560) {
            result = 1;
        }
        return result;
    }
    return 0;
}

void func_ov047_02261a24(UnkStruct_02261a24 *self)
{
    Msg m;
    int h;
    int t;
    int r;
    unsigned int ok;

    h = self->unk_40;
    m.b = 0xe8;
    t = func_020984e8();
    if (func_0206fc6c() != 0 && func_0202e9fc() != 0) {
        r = func_0206fc8c();
        m.unk_02 = (u16) func_0209a034(r);
        if (r >= 0) {
            func_0209a050(r);
        }
        if (func_0204bcdc(&m.unk_02) != 0) {
            m.unk_04 = 0xfff1;
            r = func_0204bc64(&m.unk_02);
            ok = (r == func_0204bc64(&m.unk_04)) ? 1 : 0;
        } else {
            ok = (m.unk_02 == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            func_02015330((UnkStruct_02261c28 *) self, &m.unk_02, 2, 5, 0);
        }
        {
            void *retainedAddress;
            retainedAddress = func_0209b0f0((void *) func_0209a850(func_02099640(t)));
            func_0209bb90(retainedAddress, 1);
        }
        m.b = 0xe7;
    }
    func_0206844c(h, &m.b, (int) &data_ov047_02262fc0);
}
