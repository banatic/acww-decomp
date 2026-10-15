/* func_ov049_02261d4c @ 0x02261d4c, 0x338 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Connection screen handler: fills the out parameter {text, code}.
// The fields at sp+8 are 2:3:3 bitfields indexing a u8[][7] table.

typedef struct {
    u8 pad_00[0x40];
    int unk_40; // 0x40
    u8 pad_44[0xb0 - 0x44];
    u8 *d;      // 0xb0
    int unk_B4; // 0xb4
    int unk_B8; // 0xb8
    int unk_BC; // 0xbc
} UnkStruct_02261d4c;

typedef struct {
    const char *text;
    u8 code;
} UnkStruct_02261d4c_2;

typedef struct {
    u16 v[6];
} Arr6;

typedef struct {
    u16 unk_00;
    Arr6 unk_02;
    u16 unk_0E;
    Arr6 unk_10;
    signed char unk_1C;
    u8 unk_1D;
} RecA; // 0x1e

typedef struct {
    u16 unk_00;
    Arr6 unk_02;
} RecC; // 0x0e

typedef struct {
    u8 b0 : 2;
    u8 b2 : 3;
    u8 b5 : 3;
    u8 pad[3];
} Buf;

typedef struct {
    u8 pad[0x28];
} UnkStruct_02261d4c_3;

extern const char *data_ov049_02263298[];
extern u8 data_ov049_02262dc8[];
extern u8 data_ov049_02262dd0[][7];
extern u8 data_021dc7a8[];

extern int func_020984e8(void);
extern int func_02099640(int argument0);
extern int func_0209a850(int a);
extern int func_020a12e8(void);
extern int func_ov049_02262084(UnkStruct_02261d4c *self);
extern int func_0209af80(int a, u8 *b);
extern int func_0202ea40(u8 *d, Buf *b, int n);
extern int func_0204c878(u16 *p);
extern void func_02015fb0(UnkStruct_02261d4c *self, int a, int b, int c, int d, int e);
extern void func_02015de4(UnkStruct_02261d4c *self, u16 *p, int a, int b);
extern int func_02072a48(u8 *p, int i);
extern void *func_02062fbc(UnkStruct_02261d4c_3 *o);
extern int func_02072d4c(int a);
extern void func_02072eb8(int a, UnkStruct_02261d4c_3 *o);
extern void func_020683b4(int a, int b, UnkStruct_02261d4c_3 *o, int c);
extern RecA *func_02072ee8(void *record);
extern RecA *func_02099870(int a);
extern RecC *func_02095040(RecA *p);
extern int memcmp(void *a, void *b, int n);
extern int func_0209518c(RecA *a, RecA *b);
extern void func_02015e40(UnkStruct_02261d4c *self, RecA *p, int a);
extern void *func_02015e70(UnkStruct_02261d4c *self, RecC *p, int a);
extern void func_020642f8(RecC *p);
extern int func_0209526c(RecA *p);
extern void *func_02062f4c(UnkStruct_02261d4c_3 *o);

void func_ov049_02261d4c(UnkStruct_02261d4c *self, UnkStruct_02261d4c_2 *out)
{
    Buf buf;
    UnkStruct_02261d4c_3 obj;
    RecA a;
    RecA b;
    RecC c;
    RecC d;
    int t;
    int g;
    RecA *p;
    RecA *q;
    int h;
    unsigned int ok;
    int idx;
    u16 v;
    u8 *dd;
    u8 *base;

    t = func_020984e8();
    g = func_0209a850(func_02099640(t));

    if (func_020a12e8() != 0 && func_ov049_02262084(self) == 2) {
        out->text = data_ov049_02263298[2];
        out->code = 6;
        return;
    }

    if (func_ov049_02262084(self) == 2 && func_0209af80(g, self->d + 0xea) != 0) {
        out->code = 0x2e;
        out->text = data_ov049_02263298[0];
        return;
    }

    if (func_ov049_02262084(self) == 2 && func_0202ea40(self->d, &buf, 2) != 0) {
        self->d[0x975] = 1;
        out->code = data_ov049_02262dd0[buf.b2][buf.b5];
        out->text = data_ov049_02263298[1];
        return;
    }

    out->code = data_ov049_02262dc8[self->unk_B4];
    out->text = data_ov049_02263298[0];

    if (func_ov049_02262084(self) == 4) {
        self->unk_BC = func_0204c878((u16 *) (self->d + 0x738));
        func_02015fb0(self, self->unk_BC, 0, 10, 0, 0);
        func_02015de4(self, (u16 *) (self->d + 0x738), 0, 7);
        if (func_020a12e8() != 0) {
            out->text = data_ov049_02263298[2];
            out->code = 0x1e;
        }
    } else if (func_ov049_02262084(self) == 5) {
        base = data_021dc7a8;
        dd = self->d;
        ok = 0;
        v = *(u16 *) (dd + 0x738);
        if (v >= 0x3e04 && v <= 0x3e23) {
            ok = 1;
        }
        if (ok > 0) {
            idx = (v - 0x3e04) >> 2;
        } else {
            idx = -1;
        }
        dd[0x976] = (u8) idx;

        h = func_02072a48(base + 0x10ad0, self->d[0x976]);
        func_02062fbc(&obj);
        func_02072eb8(func_02072d4c(h), &obj);
        func_020683b4(self->unk_40, 2, &obj, 7);
        p = func_02072ee8((void *) func_02072d4c(h));
        a.unk_00 = p->unk_00;
        a.unk_02 = p->unk_02;
        a.unk_0E = p->unk_0E;
        a.unk_10 = p->unk_10;
        a.unk_1C = p->unk_1C;
        a.unk_1D = p->unk_1D;

        q = func_02099870(t);
        b.unk_00 = q->unk_00;
        b.unk_02 = q->unk_02;
        b.unk_0E = q->unk_0E;
        b.unk_10 = q->unk_10;
        b.unk_1C = q->unk_1C;
        b.unk_1D = q->unk_1D;

        {
            RecC *r;
            r = func_02095040(&a);
            c.unk_00 = r->unk_00;
            c.unk_02 = r->unk_02;
            r = func_02095040(&b);
            d.unk_00 = r->unk_00;
            d.unk_02 = r->unk_02;
        }

        if (func_020a12e8() != 0) {
            out->text = data_ov049_02263298[2];
            out->code = 0x1d;
        } else {
            if (c.unk_00 != d.unk_00 || memcmp(&c.unk_02, &d.unk_02, 12) != 0) {
                func_02015e40(self, &a, 2);
                func_02015e70(self, &c, 3);
                out->code = 0x33;
            } else if (a.unk_00 != b.unk_00 || memcmp(&a.unk_02, &b.unk_02, 12) != 0 || func_0209518c(&a, &b) == 0) {
                func_02015e40(self, &a, 2);
                out->code = 0x32;
            }
        }

        func_020642f8(&d);
        func_020642f8(&c);
        func_0209526c(&b);
        func_0209526c(&a);
        func_02062f4c(&obj);
    }
}
