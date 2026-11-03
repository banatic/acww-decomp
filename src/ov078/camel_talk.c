/* camel_talk: 3 functions, module ov078
 * mwccarm 1.2/base -O4,s
 * func_ov078_02278e18 @ 0x02278e18, 0x15c bytes, Thumb
 * func_ov078_02278be0 @ 0x02278be0, 0x238 bytes, Thumb
 * func_ov078_02278b00 @ 0x02278b00, 0xe0 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02278e18_2 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_02278e18_2;

typedef struct UnkStruct_02278e18_3 {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_02278e18_3;

typedef struct UnkStruct_02278e18 {
    int w[9];
} UnkStruct_02278e18;

typedef struct Msg {
    unsigned char code;
    unsigned char pad_01;
    unsigned short a;
    unsigned short b;
    unsigned short c;
    unsigned short d;
} Msg;

typedef struct Fmt {
    int w[2];
} Fmt;

typedef struct UnkStruct_02278be0 {
    int w[9];
} UnkStruct_02278be0;

typedef struct UnkStruct_02278be0_2 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
    unsigned short unk_B8;
    unsigned short unk_BA;
} UnkStruct_02278be0_2;

struct UnkStruct_02278b00 {
    u8 pad_00[0x1e];
    u8 cmd; // 0x1e
    u8 pad_1F[0x40 - 0x1f];
    void *unk_40; // 0x40
    u8 pad_44[0xb4 - 0x44];
    s32 unk_B4; // 0xb4
    u16 unk_B8; // 0xb8
    u16 unk_BA; // 0xba
};

extern int func_020984e8(void);
extern int func_02099640(int);
extern void *func_0209a850(int);
extern void *func_02094fd4(UnkStruct_02278e18 *t);
extern void *func_02094fbc(UnkStruct_02278e18 *t);
extern int func_02099e9c(unsigned short *p);
extern void *func_0209b0f0(void *p);
extern int func_0209bd44(void *p);
extern int func_0209bba0(void *p);
extern void func_0209bb90(void *p, int a);
extern int func_0202ea80(int a, int b);
extern int func_0209b0c4(void *p, UnkStruct_02278e18 *t);
extern void func_02068404(int a, int b, UnkStruct_02278e18 *t);
extern int func_02099fe8(void);
extern int func_0209b044(void *p);
extern void func_0209b0f4(void *o);
extern unsigned short *func_0209bb70(void *o);
extern int func_0204bcdc(void *arg0);
extern int func_0204bc64(unsigned short *p);
extern int func_0209a000(unsigned short *p, int a);
extern int func_020154b4(UnkStruct_02278be0_2 *self, unsigned short *p, int a, int b, int c);
extern void func_02063ccc(Fmt *f, int a, int b);
extern void func_020638d4(unsigned short *p, Fmt *f, int a, int b, int c, int d, int e);
extern void func_02063cc8(Fmt *f);
extern void func_02015de4(UnkStruct_02278be0_2 *self, unsigned short *p, int a, int b);
extern void func_0204093c(int a);
extern int func_020644cc(int a);
extern void func_0206844c(int a, Msg *m, int *t);
extern int func_020160b4(struct UnkStruct_02278b00 *self);
extern int func_020ab504(int arg);
extern void func_0209a050(void *parameter0);
extern int func_02015330(struct UnkStruct_02278b00 *self, u16 *ptr, int a, int b, int c);
extern char data_ov078_02279bd8[];

void func_ov078_02278e18(UnkStruct_02278e18_2 *self, UnkStruct_02278e18_3 *out)
{
    unsigned short id;
    UnkStruct_02278e18 tmp;
    void *obj;

    obj = func_0209a850((int) func_02099640((int) func_020984e8()));
    func_02094fd4(&tmp);
    out->unk_00 = (int) ((int *) data_ov078_02279bd8);
    if (self->unk_B4 == -1) {
        id = 0x13ac;
        self->unk_B4 = func_02099e9c(&id);
    }
    if (self->unk_B4 >= 0) {
        out->unk_04 = 0x14;
        func_02094fbc(&tmp);
        return;
    }
    if (func_0209bd44(func_0209b0f0(obj)) != 0) {
        if (func_0209bba0(func_0209b0f0(obj)) == 3) {
            out->unk_04 = 0;
            func_02094fbc(&tmp);
            return;
        }
    }
    if (func_0202ea80(0xb, 1) == 0) {
        out->unk_04 = 1;
        func_02094fbc(&tmp);
        return;
    }
    if (func_0209bd44(func_0209b0f0(obj)) == 0) {
        out->unk_04 = 4;
        func_02094fbc(&tmp);
        return;
    }
    if (func_0209bd44(func_0209b0f0(obj)) != 0) {
        if (func_0209bba0(func_0209b0f0(obj)) == 0) {
            if (func_0209b0c4(obj, &tmp) != 0) {
                func_02068404(self->unk_40, 0, &tmp);
            }
            out->unk_04 = 9;
            func_02094fbc(&tmp);
            return;
        }
    }
    if (func_02099fe8() < 0) {
        out->unk_04 = 0x12;
        func_02094fbc(&tmp);
        return;
    }
    if (func_0209b044(obj) != 0) {
        if (func_0209b0c4(obj, &tmp) != 0) {
            func_02068404(self->unk_40, 0, &tmp);
        }
        out->unk_04 = 0xa;
    } else if (func_0209bba0(func_0209b0f0(obj)) == 1) {
        func_0209bb90(func_0209b0f0(obj), 2);
        out->unk_04 = 0xc;
    }
    func_02094fbc(&tmp);
}

void func_ov078_02278be0(UnkStruct_02278be0_2 *self)
{
    Msg m;
    Fmt s[2];
    UnkStruct_02278be0 tmp;
    void *obj;
    unsigned short *p;
    int n;
    unsigned int ok;
    int status;
    int *tail;

    m.a = 0xfff1;
    func_02094fd4((UnkStruct_02278e18 *) (&tmp));
    obj = func_0209a850((int) func_02099640((int) func_020984e8()));
    tail = ((int *) data_ov078_02279bd8);
    status = 0;
    switch (self->unk_1E) {
        case 5:
        case 0xa:
            if (func_02099fe8() < 0) {
                status = 0x1d;
                break;
            }
            if (self->unk_1E == 5) {
                func_0209b0f4(obj);
            }
            p = func_0209bb70(func_0209b0f0(obj));
            if (func_0204bcdc((void *) p) != 0) {
                m.d = 0x155f;
                n = func_0204bc64(p);
                ok = (n == func_0204bc64(&m.d));
            } else {
                ok = (*p == 0x155f);
            }
            if (ok > 0) {
                status = 6;
            } else {
                status = 7;
            }
            if (self->unk_1E != 0xa) {
                break;
            }
        case 6:
        case 7:
            func_0209a000(func_0209bb70(func_0209b0f0(obj)), 2);
            func_020154b4(self, func_0209bb70(func_0209b0f0(obj)), 2, 5, 0);
            if (func_0209b0c4(obj, (UnkStruct_02278e18 *) (&tmp)) != 0) {
                func_02068404(self->unk_40, 0, (UnkStruct_02278e18 *) (&tmp));
            }
            if (self->unk_1E != 0xa) {
                status = 8;
            } else {
                status = 0xb;
            }
            break;
        case 0xc:
            func_02063ccc(&s[0], 4, 0x23);
            func_020638d4(&m.b, &s[0], 0, 0, 1, 1, 0);
            self->unk_B8 = m.b;
            func_02063cc8(&s[0]);
            func_02015de4(self, &self->unk_B8, 1, 7);
            func_02063ccc(&s[1], 3, 0x23);
            func_020638d4(&m.c, &s[1], 0, 0, 1, 1, 0);
            self->unk_BA = m.c;
            func_02063cc8(&s[1]);
            func_02015de4(self, &self->unk_BA, 2, 7);
            status = 0xd;
            break;
        case 0xe:
            func_0209bb90(func_0209b0f0(obj), 3);
            func_0204093c(0x3e);
            break;
        case 0x15:
            self->unk_B4 = -2;
            break;
        case 0x16:
            m.a = 0x37e0;
            status = 0x17;
            if (func_020644cc(2) == 0) {
                m.a = 0x34a8;
                status = 0x18;
            }
            self->unk_B4 = -2;
            func_02015de4(self, &m.a, 0, 7);
            func_020154b4(self, &m.a, 0, 5, 0);
            func_0209a000(&m.a, 0);
            break;
    }
    if (status != 0) {
        m.code = (unsigned char) status;
        func_0206844c(self->unk_40, &m, tail);
    }
    func_02094fbc((UnkStruct_02278e18 *) (&tmp));
}

void func_ov078_02278b00(struct UnkStruct_02278b00 *self)
{
    int res;
    int code;
    char *data;
    struct {
        u8 byte0;
        u8 pad;
        u16 a;
        u16 b;
    } loc;

    res = func_020ab504(func_020160b4(self));

    loc.a = 0xfff1;
    data = data_ov078_02279bd8;
    code = 0;

    switch (self->cmd) {
        case 2:
        case 4:
            if (res == 0) {
                if (func_02099fe8() < 0) {
                    code = 0x1d;
                } else {
                    code = 5;
                }
            }
            break;

        case 13:
        case 19:
            if (res == 0) {
                loc.a = self->unk_B8;
            } else {
                loc.a = self->unk_BA;
            }
            func_020154b4((UnkStruct_02278be0_2 *) self, (unsigned short *) (&loc.a), 0, 5, 0);
            func_0209a000((unsigned short *) (&loc.a), 0);
            code = 0xe;
            break;

        case 20:
            if (res == 0) {
                if (self->unk_B4 >= 0) {
                    func_0209a050((void *) (*(
                        int *) ((char *) (((unsigned int) (((unsigned int) (((unsigned int) (self) + (0x0))) + (0x0))) +
                                           (0xb4))) +
                                0)));
                    loc.b = 0x13ac;
                    func_02015330(self, &loc.b, 0, 5, 0);
                }
                code = 0x16;
            }
            break;

        default:
            break;
    }

    if (code != 0) {
        loc.byte0 = (u8) code;
        func_0206844c((int) ((void *) self->unk_40), (Msg *) (&loc), (int *) data);
    }
}
