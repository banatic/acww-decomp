/* func_ov050_02261ed0 @ 0x02261ed0, 0x748 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Connection screen handler with eight virtual calls (vtable slots 34-41).
// The pragma keeps the byte stores shifting one register in place.

#pragma opt_propagation off

typedef struct {
    const char *text;
    u8 code;
} UnkStruct_02261ed0_4;
typedef struct {
    const char *text;
    u8 code;
} Entry;

typedef struct {
    u8 pad_00[8];
    int unk_08;
    u16 unk_0C;
    u8 pad_0E[0x732 - 0xe];
    u16 unk_732;
} UnkStruct_02261ed0;

typedef struct {
    u8 v[4];
} UnkStruct_02261ed0_2;

typedef struct {
    u8 f0a : 2;
    u8 f0b : 3;
    u8 f0c : 3;
    u8 unk_01;
    u16 h1;
} UnkStruct_02261ed0_5;

typedef struct {
    u16 h2, h3, unk_04, h5, h6, h7, h8, h9;
    UnkStruct_02261ed0_2 c;
    UnkStruct_02261ed0_2 d;
    UnkStruct_02261ed0_2 e;
    UnkStruct_02261ed0_2 unk_1C;
    UnkStruct_02261ed0_2 g;
} Obj2;

extern "C" {
extern int func_020984e8(void);
extern int func_02099640(int a);
extern int func_0209a850(int a);
extern int func_02099020(int a, int b);
extern int func_0209ad9c(int a, int b);
extern int func_0209b4d4(int a);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_0209bd44(int a);
extern int func_0209bc40(int a);
extern int func_ov050_02260510(UnkStruct_02261ed0 *a);
extern int func_02073d90(void *a);
extern short *func_0209d358(int a, int b);
extern int func_02099e9c(u16 *p);
extern int func_0209af80(int a, u16 *p);
extern int func_0202ea40(UnkStruct_02261ed0 *a, UnkStruct_02261ed0_5 *o, int n);
extern void func_ov050_02263640(void *self, int a);
extern u8 *func_020afad4(void *a);
extern void func_0209df64(UnkStruct_02261ed0_2 *p);
extern int func_0209dcdc(UnkStruct_02261ed0_2 *p, u8 *q);
extern int func_020af028(void *a);
extern void func_02098ff8(int a, int b);
extern int func_02099670(int a);
extern u8 *func_02088c04(int a);
extern int func_0209f150(void *a, int b);
extern int func_ov050_022634c8(void *self);
extern void func_0209f128(void *a, int b);
extern int func_0202ea80(int a, int b);
extern int func_020af90c(void *a);
extern int func_020afa48(void *a);
extern void func_02015ed0(void *self, int a, int b);
extern void func_02015ea0(void *self, int a, int b);
extern int func_020afb24(void *a);
extern int func_020afb90(void *a);
extern int func_020afad8(void *a);
extern void func_020683e4(void *a, int b, u8 *c, void *d);
extern int func_0204c788(u16 *p);
extern void func_02015fb0(void *self, int a, int b, int c, int d, int e);
extern void func_02015de4(void *self, u16 *p, int a, int b);
extern int func_ov050_022609d8(UnkStruct_02261ed0 *a);
extern int func_0200338c(int a, int b);
extern void func_ov050_02264834(int a, int b);

extern char data_ov050_02265804[];
extern char data_ov050_02265834[];
extern char data_ov050_02265814[];
extern char data_ov050_02265824[];
extern void *data_020ccf94;
extern char data_021f395c[];
extern char data_021dc7a8[];
extern char data_ov050_02265e9c[];
extern u8 data_ov050_022650c4[][6];
extern Entry data_ov050_02265114[];
}

class UnkStruct_02261ed0_3 {
  public:
    u8 pad_04[0x40 - 4];
    void *unk_40;
    u8 pad_44[0xb0 - 0x44];
    int unk_B0;
    UnkStruct_02261ed0 *unk_B4;
    u8 pad_B8[0xc4 - 0xb8];
    int unk_C4;
    u8 pad_C8[0xcc - 0xc8];
    int unk_CC;
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34(UnkStruct_02261ed0_4 *o);
    virtual void v35(UnkStruct_02261ed0_4 *o);
    virtual void v36(UnkStruct_02261ed0_4 *o);
    virtual void v37(UnkStruct_02261ed0_4 *o);
    virtual void v38(UnkStruct_02261ed0_4 *o);
    virtual void v39(UnkStruct_02261ed0_4 *o);
    virtual void v40(UnkStruct_02261ed0_4 *o);
    virtual void v41(UnkStruct_02261ed0_4 *o);
};

extern "C" void func_ov050_02261ed0(UnkStruct_02261ed0_3 *self, UnkStruct_02261ed0_4 *out);

void func_ov050_02261ed0(UnkStruct_02261ed0_3 *self, UnkStruct_02261ed0_4 *out)
{
    int flag8;
    int s0c;
    UnkStruct_02261ed0_5 obj;
    Obj2 ob2;
    int q;
    int r7;
    int r6;
    int c;
    int v;
    int t;
    unsigned int ok;
    int idx;
    unsigned int uidx;
    unsigned int uv;
    u16 *p;
    u8 *bp;

    q = func_020984e8();
    r7 = func_0209a850(func_02099640(q));
    s0c = func_02099640(q);

    if (func_02099020(q, 1) != 0) {
        r6 = func_0209b4d4(func_0209ad9c(s0c, 0));
        v = self->unk_B4->unk_0C;
        if (((v == 0x75) ? 1 : 0) || ((v == 0x74) ? 1 : 0)) {
            out->text = data_ov050_02265804;
            out->code = 3;
            return;
        }
        out->text = data_ov050_02265834;
        p = &self->unk_B4->unk_732;
        if (func_0204bcdc(p) != 0) {
            ob2.h6 = 0xfff1;
            c = (func_0204bc64(p) == func_0204bc64(&ob2.h6)) ? 1 : 0;
        } else {
            c = (*p == 0xfff1) ? 1 : 0;
        }
        if (c == 0) {
            self->unk_B4->unk_732 = 0xfff1;
            out->code = 0xb;
            return;
        }
        if (self->unk_B0 == 0x1e) {
            out->code = 0xc;
            self->unk_B0 = 5;
            return;
        }
        out->code = 0;
        if (func_0209bd44(r6) == 0) {
            return;
        }
        if (func_0209bc40(r6) == 0x12) {
            self->v41(out);
        }
        if (func_0209bc40(r6) == 0x11) {
            self->v40(out);
        }
        if (func_0209bc40(r6) == 0x10) {
            self->v39(out);
        }
        if (func_0209bc40(r6) == 0x0f) {
            self->v38(out);
        }
        if (func_0209bc40(r6) == 0x0e) {
            self->v37(out);
        }
        if (func_0209bc40(r6) == 0x0d) {
            self->v36(out);
        }
        if (func_0209bc40(r6) == 0x0c) {
            self->v35(out);
        }
        if (func_0209bc40(r6) == 0x0b) {
            self->v34(out);
        }
        return;
    }

    if (func_ov050_02260510(self->unk_B4) != 0 && self->unk_B0 == 5 && func_02073d90(data_020ccf94) == 0 &&
        *func_0209d358(0, 0x4a) == 0) {
        if (self->unk_CC == -1) {
            obj.h1 = 0x36fc;
            self->unk_CC = func_02099e9c(&obj.h1);
        }
        if (self->unk_CC >= 0) {
            self->unk_B0 = 0xe;
            goto L2164;
        }
        ob2.h2 = 0xd019;
        if (func_0209af80(r7, &ob2.h2) != 0) {
            goto err10;
        }
        ob2.h3 = 0xd01a;
        if (func_0209af80(r7, &ob2.h3) != 0) {
            goto err10;
        }
        ob2.unk_04 = 0xd01b;
        if (func_0209af80(r7, &ob2.unk_04) != 0) {
            goto err10;
        }
        ob2.h5 = 0xd01c;
        if (func_0209af80(r7, &ob2.h5) != 0) {
        err10:
            self->unk_B0 = 0x10;
            goto L2164;
        }
        if (func_0202ea40(self->unk_B4, &obj, 3) != 0) {
            out->text = data_ov050_02265814;
            out->code = data_ov050_022650c4[obj.f0b][obj.f0c];
            func_ov050_02263640(self, 0xf);
            return;
        }
    }

L2164:
    if (self->unk_B0 == 0 || self->unk_B0 == 0x11) {
        flag8 = 0;
        if (self->unk_B0 == 0) {
            out->text = data_ov050_02265824;
            if (func_02099020(q, 0x26) == 0) {
                bp = func_020afad4(data_021f395c);
                ob2.d = *(UnkStruct_02261ed0_2 *) bp;
                func_0209df64(&ob2.e);
                out->code = 0;
                if (ob2.d.v[3] == 0) {
                    t = func_0209dcdc(&ob2.e, ob2.d.v);
                    if (self->unk_B4->unk_08 == 0xd01a && func_02099020(q, 0x24) == 0 && t == 0) {
                        out->code = (u8) (func_020af028(data_021f395c) + 0x59);
                    }
                    if (self->unk_B4->unk_08 == 0xd01b && func_020af028(data_021f395c) == 2 && func_02099020(q, 0x25) == 0 &&
                        t == 0) {
                        out->code = (u8) (func_020af028(data_021f395c) + 0x59);
                    }
                    if (self->unk_B4->unk_08 == 0xd01c && func_020af028(data_021f395c) == 3 && func_02099020(q, 0x26) == 0 &&
                        t == 0) {
                        out->code = (u8) (func_020af028(data_021f395c) + 0x59);
                    }
                    switch (func_020af028(data_021f395c)) {
                        case 3:
                            func_02098ff8(q, 0x26);
                        case 2:
                            func_02098ff8(q, 0x25);
                        case 1:
                            func_02098ff8(q, 0x24);
                    }
                    if (out->code != 0) {
                        return;
                    }
                }
            }
            if (func_02099020(q, 3) == 0) {
                bp = func_02088c04(func_02099670(q));
                if (bp[2] != 0 || bp[1] != 0) {
                    func_0209df64(&ob2.unk_1C);
                    if (func_0209dcdc(&ob2.unk_1C, bp) != 0) {
                        out->code = 0x3b;
                        func_02098ff8(q, 3);
                        return;
                    }
                }
            }
            if (func_0209f150(data_021dc7a8, 0x10) == 0) {
                out->code = (u8) func_ov050_022634c8(self);
                if (out->code != 0) {
                    func_0209f128(data_021dc7a8, 0x10);
                    return;
                }
            }
            if (func_0202ea80(0, 0) == 0 && func_020af90c(data_021f395c) != 0) {
                uidx = (unsigned int) func_020afa48(data_021f395c);
                ob2.c.v[0] = (u8) uidx;
                uidx >>= 8;
                ob2.c.v[1] = (u8) uidx;
                uidx >>= 8;
                ob2.c.v[2] = (u8) uidx;
                uidx >>= 8;
                ob2.c.v[3] = (u8) uidx;
                ob2.g = ob2.c;
                func_02015ed0(self, ob2.g.v[1], 7);
                func_02015ea0(self, ob2.g.v[0], 8);
                func_ov050_02263640(self, 7);
                flag8 = 1;
                func_0202ea80(0, flag8);
            }
        }
        if (flag8 == 0) {
            if (func_020afb24(data_021f395c) != 0) {
                if (self->unk_B0 == 0) {
                    func_ov050_02263640(self, 2);
                } else {
                    func_ov050_02263640(self, 0x1a);
                }
            } else if (func_020afb90(data_021f395c) != 0) {
                if (self->unk_B0 == 0) {
                    func_ov050_02263640(self, 3);
                } else {
                    func_ov050_02263640(self, 0x1b);
                }
            } else if (func_020afad8(data_021f395c) != 0) {
                if (self->unk_B0 == 0) {
                    func_ov050_02263640(self, 4);
                } else {
                    func_ov050_02263640(self, 0x1c);
                }
            }
        }
    } else {
        p = &self->unk_B4->unk_732;
        if (func_0204bcdc(p) != 0) {
            ob2.h7 = 0xfff1;
            c = (func_0204bc64(p) == func_0204bc64(&ob2.h7)) ? 1 : 0;
        } else {
            c = (*p == 0xfff1) ? 1 : 0;
        }
        if (c == 0) {
            switch (self->unk_B0) {
                case 0x0c:
                case 0x0d:
                case 0x18:
                case 0x19:
                    p = &self->unk_B4->unk_732;
                    if (func_0204bcdc(p) != 0) {
                        ob2.h8 = 0xfff1;
                        c = (func_0204bc64(p) == func_0204bc64(&ob2.h8)) ? 1 : 0;
                    } else {
                        c = (*p == 0xfff1) ? 1 : 0;
                    }
                    if (c == 0) {
                        ok = 0;
                        uv = self->unk_B4->unk_732;
                        if (uv >= 0x1521 && uv <= 0x1530) {
                            ok = 1;
                        }
                        if (ok > 0) {
                            idx = uv - 0x1521;
                        } else {
                            idx = -1;
                        }
                        obj.unk_01 = (u8) idx;
                        func_020683e4(self->unk_40, 2, &obj.unk_01, data_ov050_02265e9c);
                    }
                case 0x08:
                case 0x09:
                case 0x0a:
                case 0x0b:
                case 0x14:
                case 0x15:
                case 0x16:
                case 0x17:
                    p = &self->unk_B4->unk_732;
                    if (func_0204bcdc(p) != 0) {
                        ob2.h9 = 0xfff1;
                        c = (func_0204bc64(p) == func_0204bc64(&ob2.h9)) ? 1 : 0;
                    } else {
                        c = (*p == 0xfff1) ? 1 : 0;
                    }
                    if (c == 0) {
                        self->unk_C4 = func_0204c788(&self->unk_B4->unk_732);
                        func_02015fb0(self, self->unk_C4, 4, 0xa, 0, 0);
                        func_02015de4(self, &self->unk_B4->unk_732, 1, 7);
                    }
                    break;
            }
        }
    }

    if (self->unk_B0 >= 0 && self->unk_B0 < 0x1f) {
        out->code = data_ov050_02265114[self->unk_B0].code;
        out->text = data_ov050_02265114[self->unk_B0].text;
        if (self->unk_B0 == 0x12) {
            t = func_0200338c(func_ov050_022609d8(self->unk_B4), 0);
            if (t != 0) {
                func_ov050_02264834(t, 0xc);
            }
        }
    }
}
