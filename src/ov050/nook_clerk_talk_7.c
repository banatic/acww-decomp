/* nook_clerk_talk_7: 9 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_02263b38 @ 0x02263b38, 0x68 bytes, Thumb
 * func_ov050_022638d4 @ 0x022638d4, 0x264 bytes, Thumb
 * func_ov050_022637e8 @ 0x022637e8, 0xec bytes, Thumb
 * func_ov050_022637c0 @ 0x022637c0, 0x28 bytes, Thumb
 * func_ov050_022636e0 @ 0x022636e0, 0xe0 bytes, Thumb
 * func_ov050_022636c8 @ 0x022636c8, 0x18 bytes, Thumb
 * func_ov050_022636b0 @ 0x022636b0, 0x18 bytes, Thumb
 * func_ov050_02263690 @ 0x02263690, 0x20 bytes, Thumb
 * func_ov050_0226366c @ 0x0226366c, 0x24 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} UnkStruct_02263b38;

typedef struct UnkStruct_02263b38_2 {
    unsigned char pad_00[0xb8];
    UnkStruct_02263b38 v;
} UnkStruct_02263b38_2;

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

typedef struct UnkStruct_022637e8 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    char *unk_B4;
    char pad_B8[0xc4 - 0xb8];
    int unk_C4;
} UnkStruct_022637e8;

typedef struct Msg_022637e8 {
    u8 b;
    u8 pad_01;
    u16 unk_02;
} Msg_022637e8;

typedef struct UnkStruct_022636e0 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_022636e0;

typedef struct Msg_022636e0 {
    u8 b;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
} Msg_022636e0;

typedef struct {
    int a;
    int b;
} Pair;

extern UnkStruct_02263b38 data_ov050_02265718;
extern UnkStruct_02263b38 data_ov050_02265710;
extern UnkStruct_02263b38 data_ov050_02265708;
extern int data_ov050_02265ed4;
extern UnkStruct_02263b38 data_ov050_02265ed8[3];
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
extern int func_0206f680(void);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_0204c7f0(u16 *p);
extern void func_02015de4(UnkStruct_022637e8 *self, u16 *p, int a, int b);
extern void func_0206844c(int h, u8 *p, int k);
extern int func_0202e9fc(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int a);
extern void func_0209a050(int a);
extern int func_02015330(UnkStruct_022636e0 *self, u16 *p, int a, int b, int c);
extern int func_02099640(int t);
extern int func_0209a850(int a);
extern void *func_0209b0f0(void *record);
extern void func_0209bb90(void *a, int b);
extern void *func_0202eb70(void *p);
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *);
extern unsigned char data_ov050_02265b14[];
extern void func_0201612c(void *);
extern Pair __ptmf_null;

void func_ov050_02263b38(UnkStruct_02263b38_2 *self, int idx)
{
    if ((data_ov050_02265ed4 & 1) == 0) {
        data_ov050_02265ed8[0] = data_ov050_02265718;
        data_ov050_02265ed8[1] = data_ov050_02265710;
        data_ov050_02265ed8[2] = data_ov050_02265708;
        data_ov050_02265ed4 |= 1;
    }
    self->v = data_ov050_02265ed8[idx];
}

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
        func_0206844c((int) h, (u8 *) (&msg), (int) data_ov050_02265824);
    } else {
        func_0206844c((int) h, (u8 *) (&msg), (int) data_ov050_02265804);
    }
}

void func_ov050_022637e8(UnkStruct_022637e8 *self)
{
    Msg_022637e8 m;
    int h;
    u16 *p;
    int r;
    unsigned int ok;

    h = self->unk_40;
    m.b = 0x1b;
    if (func_0206fc6c() == 1) {
        *(u16 *) (self->unk_B4 + 0x732) = (u16) func_0206f680();
        p = (u16 *) (self->unk_B4 + 0x732);
        if (func_0204bcdc(p) != 0) {
            m.unk_02 = 0xfff1;
            r = func_0204bc64(p);
            ok = (r == func_0204bc64(&m.unk_02)) ? 1 : 0;
        } else {
            ok = (*p == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            self->unk_C4 = func_0204c7f0((u16 *) (self->unk_B4 + 0x732));
            if (self->unk_C4 != 0) {
                func_02015fb0((UnkStruct_022638d4 *) self, self->unk_C4, 0, 0xa, 0, 0);
                func_02015de4(self, (u16 *) (self->unk_B4 + 0x732), 1, 7);
                m.b = 0x1a;
            }
        }
    }
    if (func_ov050_02260510((void *) self->unk_B4) != 0) {
        func_0206844c(h, &m.b, (int) ((int *) data_ov050_02265824));
    } else {
        func_0206844c(h, &m.b, (int) ((int *) data_ov050_02265804));
    }
}

unsigned short func_ov050_022637c0(unsigned short *r0, int r1)
{
    unsigned short result;
    unsigned short value;

    if (r1 == 2) {
        result = 0;
        value = *r0;
        if (value >= 0x155f && value <= 0x1560) {
            result = 1;
        }
        return result;
    }
    return 0;
}

void func_ov050_022636e0(UnkStruct_022636e0 *self)
{
    Msg_022636e0 m;
    int h;
    int t;
    int r;
    unsigned int ok;

    h = self->unk_40;
    m.b = 4;
    if (func_0206fc6c() != 0) {
        t = func_020984e8();
        if (func_0202e9fc() != 0) {
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
                func_02015330(self, &m.unk_02, 2, 5, 0);
            }
            m.b = 3;
            {
                void *retainedAddress;
                retainedAddress = func_0209b0f0((void *) func_0209a850(func_02099640(t)));
                func_0209bb90(retainedAddress, 1);
            }
        }
    }
    if (func_ov050_02260510((void *) self->unk_B4) != 0) {
        func_0206844c(h, &m.b, (int) ((int *) data_ov050_02265824));
    } else {
        func_0206844c(h, &m.b, (int) ((int *) data_ov050_02265804));
    }
}

void *func_ov050_022636c8(void *p)
{
    func_0202eb70(p);
    *(void **) p = (void *) ((char *) data_ov050_02265b14);
    return p;
}

void *func_ov050_022636b0(void *self)
{
    *(void **) self = (void *) ((char *) data_ov050_02265b14);
    func_0202eb20(self);
    return self;
}

void *func_ov050_02263690(void *p)
{
    *(void **) p = (void *) data_ov050_02265b14;
    func_0202eb20(p);
    func_020edb3c(p);
    return p;
}

void func_ov050_0226366c(void *this)
{
    func_0201612c(this);
    *(Pair *) ((char *) this + 0xb8) = __ptmf_null;
}
