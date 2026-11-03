/* otter_talk: 3 functions, module ov076
 * mwccarm 1.2/base -O4,s
 * func_ov076_02278d94 @ 0x02278d94, 0x70 bytes, Thumb
 * func_ov076_02278b78 @ 0x02278b78, 0x21c bytes, Thumb
 * func_ov076_02278af0 @ 0x02278af0, 0x88 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02278d94 {
    char pad_00[0xb0];
    int unk_B0;
};

struct UnkStruct_02278d94_2 {
    unsigned int unk_00;
    unsigned char unk_04;
};

typedef struct {
    unsigned int a;
    unsigned int b;
} Obj8;

typedef struct {
    u8 kind;
    u8 pad_01;
    u16 h[3];
    u16 cmp;
} Msg;

typedef struct {
    u8 pad_00[0x1e];
    u8 unk_1E;
    u8 pad_1F[0x40 - 0x1f];
    void *unk_40;
    u8 pad_44[0xb4 - 0x44];
    unsigned char *unk_B4;
    u16 unk_B8;
} UnkStruct_02278b78;

struct UnkStruct_ov076_02278af0 {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x40 - 0x1f];
    void *unk_40;
};

extern unsigned short func_0206f9d8(int (*predicate)(unsigned short *, int));
extern int func_020644cc(int);
extern int func_ov076_02278f0c(unsigned short *, int);
extern const unsigned char data_ov076_02279598[][8];
extern const unsigned int data_ov076_02279594[][2];
extern char data_ov076_022796e0;
extern void func_ov076_02278f5c(UnkStruct_02278b78 *, int);
extern void func_020157d4(void *self, int (*predicate)(unsigned short *, int), unsigned char kind, unsigned char flag);
extern int func_02015828(UnkStruct_02278b78 *, int);
extern int func_020154b4(UnkStruct_02278b78 *, u16 *, int, int, int);
extern int func_0209a000(u16 *, int);
extern int func_0202ea80(int, int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern int func_02099fe8(void);
extern void func_02063ccc(Obj8 *, int, int);
extern void func_020638d4(u16 *, Obj8 *, int, int, int, int, int);
extern void func_02063cc8(Obj8 *);
extern void func_0204093c(int);
extern void func_0206844c(void *, Msg *, void *);
extern int func_020160b4(void *self);
extern int func_020ab504(int a);

void func_ov076_02278d94(struct UnkStruct_02278d94 *s, struct UnkStruct_02278d94_2 *out)
{
    if (func_0206f9d8(func_ov076_02278f0c) != 0) {
        s->unk_B0 = 0;
    } else {
        if (func_020644cc(2) == 0) {
            s->unk_B0 = 1;
        } else {
            s->unk_B0 = 2;
        }
    }
    if (s->unk_B0 >= 0 && s->unk_B0 < 3) {
        out->unk_04 = data_ov076_02279598[s->unk_B0][0];
        out->unk_00 = data_ov076_02279594[s->unk_B0][0];
    }
}

void func_ov076_02278b78(UnkStruct_02278b78 *self)
{
    void *p = &data_ov076_022796e0;
    u8 message = 0xff;
    Msg m;
    Obj8 o[3];

    {
        int st = self->unk_1E;
        if (st == 0xfd || (st >= 0xf && st <= 0xfc)) {
            message = (u8) (func_020644cc(2) + 0xd);
        }
    }

    switch (self->unk_1E) {
        case 4:
            func_020157d4(self, func_ov076_02278f0c, 0xd, 0);
            func_02015828(self, 0);
            func_ov076_02278f5c(self, 0);
            break;
        case 10:
        case 11:
            if (self->unk_1E == 10) {
                self->unk_B8 = 0x4a38;
            } else {
                self->unk_B8 = 0x1373;
            }
            func_020154b4(self, &self->unk_B8, 0, 5, 0);
            func_0209a000(&self->unk_B8, 0);
            self->unk_B4[0x71c] = 1;
            func_0202ea80(0x18, 1);
            message = 0xc;
            break;
        case 12: {
            int ok;
            if (func_0204bcdc(&self->unk_B8)) {
                m.cmp = 0x4a38;
                ok = (func_0204bc64(&self->unk_B8) == func_0204bc64(&m.cmp));
            } else {
                ok = (self->unk_B8 == 0x4a38);
            }
            if (ok) {
                message = 0x33;
            } else {
                message = 0xfd;
            }
            break;
        }
        case 13:
        case 14:
            if (self->unk_B4[0x71c] == 0) {
                if (func_02099fe8() >= 0) {
                    int k = func_020644cc(9);
                    if (k <= 6) {
                        func_02063ccc(&o[0], 0, 0x15);
                        func_020638d4(&m.h[0], &o[0], 0, 0, 1, 1, 0);
                        self->unk_B8 = m.h[0];
                        func_02063cc8(&o[0]);
                    } else if (k == 7) {
                        func_02063ccc(&o[1], 4, 0x15);
                        func_020638d4(&m.h[1], &o[1], 0, 0, 1, 1, 0);
                        self->unk_B8 = m.h[1];
                        func_02063cc8(&o[1]);
                    } else {
                        func_02063ccc(&o[2], 3, 0x15);
                        func_020638d4(&m.h[2], &o[2], 0, 0, 1, 1, 0);
                        self->unk_B8 = m.h[2];
                        func_02063cc8(&o[2]);
                    }
                    func_020154b4(self, &self->unk_B8, 0, 5, 0);
                    func_0209a000(&self->unk_B8, 0);
                    func_0202ea80(0x18, 1);
                }
                self->unk_B4[0x71c] = 1;
            }
            func_0204093c(0x42);
            break;
    }

    if (message != 0xff) {
        m.kind = message;
        func_0206844c(self->unk_40, &m, p);
    }
}

void func_ov076_02278af0(struct UnkStruct_ov076_02278af0 *self)
{
    int a;
    int b;
    void *p;
    unsigned char message;
    char msg;

    a = func_020160b4(self);
    b = func_020ab504(a);
    p = &data_ov076_022796e0;
    message = 0xff;

    switch (self->unk_1E) {
        case 0:
        case 1:
            if (b == 0) {
                message = (unsigned char) (func_020644cc(0xee) + 0xf);
            } else {
                message = 5;
            }
            break;
        case 2:
            if (b == 2) {
                message = 4;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
        case 8:
            if (b == 0) {
                message = 0xb;
            } else if (b == 1) {
                message = 9;
            } else {
                message = 0xa;
            }
            break;
        default:
            break;
    }

    if (message != 0xff) {
        msg = (char) message;
        func_0206844c(self->unk_40, (Msg *) (&msg), p);
    }
}
