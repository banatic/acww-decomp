/* fortune_teller_talk_3: 4 functions, module ov045
 * mwccarm 1.2/base -O4,s
 * func_ov045_02260c28 @ 0x02260c28, 0x6c bytes, Thumb
 * func_ov045_02260978 @ 0x02260978, 0x2b0 bytes, Thumb
 * func_ov045_02260958 @ 0x02260958, 0x1e bytes, Thumb
 * func_ov045_02260848 @ 0x02260848, 0x110 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Result;

typedef struct {
    char pad_00[0xb4];
    int unk_B4;
} Param;

typedef struct {
    char pad_00[0x744];
    u8 unk_744;
    u8 unk_745;
    char pad1[2];
    int unk_748;
    char pad2[8];
    int unk_754;
} UnkStruct_02260978;

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad1[0x21];
    void *unk_40;
    char pad2[0x70];
    UnkStruct_02260978 *unk_B4;
} UnkStruct_02260978_2;

struct UnkStruct_02260848 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
    char pad_44[0xb4 - 0x44];
    void *unk_B4;
};

extern int data_ov045_02261380;
extern int func_0202ea80(int arg0, int arg1);
extern int func_ov045_02260644(void);
extern char data_021dc7a8[];
extern void *data_020ccf94;
extern int func_020984e8(void);
extern void func_020157c8(UnkStruct_02260978_2 *self, int a, int b);
extern int func_02015828(UnkStruct_02260978_2 *self, int a);
extern void func_ov045_022607ac(UnkStruct_02260978_2 *self, int a);
extern void func_ov045_022605a4(UnkStruct_02260978 *h);
extern int func_0201b43c(UnkStruct_02260978 *h, int a);
extern void func_0201b420(UnkStruct_02260978 *h, int a);
extern void func_ov045_02260e50(UnkStruct_02260978 *h, int a);
extern void func_02099768(int a, int b);
extern int func_ov045_02260524(UnkStruct_02260978 *h);
extern int func_02099870(int a);
extern void func_0207acbc(char *p, int a);
extern void func_0207adf4(char *p);
extern void *func_0207cd84(char *p, int a, int b, int c);
extern void *func_020807dc(void *p, int a);
extern void *func_020807c0(void *p, void *q);
extern unsigned int func_0208150c(void *p);
extern int func_02003704(void *argument0);
extern void *func_0207f270(void *p);
extern int func_02073dd4(void *g, void *h);
extern int func_020794c4(void *p);
extern void func_020794a8(void *p, int a);
extern void func_020794a4(void *p, int a);
extern void func_020794c0(void *p, int a);
extern signed char func_02081cec(void *p, int a);
extern int func_02081d20(void *p);
extern void func_020787d4(void *p, void *q, int x);
extern void func_0206844c(void *a, u8 *p, int c);
extern void func_02035684(int, int, int);
extern int func_020160b4(void *argument0);
extern int func_020ab504(void *argument0);

void func_ov045_02260c28(Param *param, Result *result)
{
    int v1, v2, v3;
    result->unk_00 = data_ov045_02261380;
    v1 = func_0202ea80(4, 0);
    v2 = func_0202ea80(5, 0);
    v3 = func_0202ea80(6, 0);
    if (v2 == 0 || v1 == 0) {
        if (v2 == 0) {
            result->unk_04 = 1;
        } else {
            result->unk_04 = 5;
        }
    } else {
        if (v3 == 0) {
            result->unk_04 = 0x11;
        } else {
            result->unk_04 = 0x19;
        }
    }
    if (((void) *(volatile int *) &param->unk_B4, func_ov045_02260644()) != 0) {
        result->unk_04 = 0x13;
    }
}

void func_ov045_02260978(UnkStruct_02260978_2 *self)
{
    void *a;
    void *b;
    void *c;
    int gid;
    u8 buf[4];
    int sess;
    int code;
    int kind;
    char (*q)[];
    void *obj;

    q = &data_021dc7a8;
    sess = func_020984e8();
    code = 0xff;
    switch (self->unk_1E) {
        case 9:
        case 11:
            func_020157c8(self, 0x13, 0);
            func_02015828(self, 2);
            func_ov045_022607ac(self, 1);
            break;
        case 14:
            func_ov045_022605a4(self->unk_B4);
            code = self->unk_B4->unk_744;
            break;
        case 16:
            if (func_0201b43c(self->unk_B4, 0x64) != 0) {
                func_0201b420(self->unk_B4, 0x64);
            }
            code = 0x16;
            break;
        case 19:
            func_ov045_02260e50(self->unk_B4, 3);
            break;
        case 24:
            if (func_0201b43c(self->unk_B4, 0x2710) != 0) {
                func_0201b420(self->unk_B4, 0x2710);
            }
            func_02099768(sess, 0);
            func_0202ea80(6, 1);
            code = 0x16;
            break;
        case 20:
        case 21:
        case 22:
        case 23:
        default:
            break;
    }
    if (self->unk_B4->unk_745 != 0xff) {
        if (self->unk_B4->unk_745 == self->unk_1E) {
            code = 0x10;
            kind = func_ov045_02260524(self->unk_B4);
            gid = func_02099870(func_020984e8());
            switch (self->unk_B4->unk_748) {
                case 0:
                    func_02099768(sess, kind);
                    if (kind == 1) {
                        func_0207acbc((char *) ((int) (*q) + 0x9284), gid);
                    } else if (kind == 2) {
                        func_0207adf4((char *) ((int) (*q) + 0x9284));
                    }
                    break;
                case 1:
                    a = func_0207cd84((char *) ((int) (*q) + 0x9284), self->unk_B4->unk_754, 0xa, func_02099870(sess));
                    if (a != 0) {
                        b = func_020807dc(a, gid);
                        c = func_020807c0(a, b);

                        if (func_02003704((void *) func_0208150c(a)) != 0) {
                            obj = func_0207f270(a);
                        } else {
                            obj = 0;
                        }
                        if (c != 0) {
                            switch (kind) {
                                case 1:
                                    if (func_02073dd4(data_020ccf94, ((void **) data_020ccf94)[0x19]) == 0) {
                                        if (obj != 0) {
                                            if (func_020794c4(obj) == 1) {
                                                func_020794a8(obj, 0xe10);
                                            } else {
                                                func_020794a4(obj, 0xe10);
                                            }
                                            func_020794c0(obj, 1);
                                        }
                                    }
                                    func_02081cec(c, 0xa);
                                    func_020787d4(a, b, func_02081d20(c));
                                    break;
                                case 2:
                                    if (func_02073dd4(data_020ccf94, ((void **) data_020ccf94)[0x19]) == 0) {
                                        if (obj != 0) {
                                            if (func_020794c4(obj) == 4) {
                                                func_020794a8(obj, 0x4b0);
                                            } else {
                                                func_020794a4(obj, 0x4b0);
                                            }
                                            func_020794c0(obj, 4);
                                        }
                                    }
                                    func_02081cec(c, ~2);
                                    func_020787d4(a, b, func_02081d20(c));
                                    break;
                            }
                        }
                    }
                    break;
            }
            self->unk_B4->unk_745 = 0xff;
            self->unk_B4->unk_744 = 0xff;
        }
        if (self->unk_B4->unk_744 == self->unk_1E) {
            code = self->unk_B4->unk_745;
        }
    }
    if (code != 0xff) {
        buf[0] = (u8) code;
        func_0206844c(self->unk_40, buf, data_ov045_02261380);
    }
}

void func_ov045_02260958(unsigned char *p)
{
    unsigned char v = p[0x1e];
    if (v == 0xe || v == 0x17) {
        func_02035684(0x10, 0, 0);
    }
}

void func_ov045_02260848(struct UnkStruct_02260848 *self)
{
    int val;
    int r4;
    u8 c;

    val = func_020ab504((void *) func_020160b4(self));
    r4 = 0xff;

    switch (self->unk_1E) {
        case 1:
        case 3:
        case 5:
            if (val == 0) {
                if (func_0201b43c((UnkStruct_02260978 *) self->unk_B4, 100) == 0) {
                    r4 = 6;
                } else {
                    r4 = 7;
                }
            } else if (self->unk_1E == 5 && val == 1) {
                r4 = 0x14;
            }
            break;

        case 7:
        case 8:
            if (val == 0) {
                if (func_0202ea80(5, 0) != 0) {
                    r4 = 8;
                } else {
                    r4 = 0xd;
                    *(int *) ((char *) self->unk_B4 + 0x748) = 0;
                    func_0202ea80(5, 1);
                }
            } else if (val == 1) {
                if (func_0202ea80(4, 0) != 0) {
                    r4 = 8;
                } else {
                    r4 = 9;
                }
            }
            break;

        case 10:
            if (val == 0) {
                r4 = 0xc;
                *(int *) ((char *) self->unk_B4 + 0x748) = 1;
                func_0202ea80(4, 1);
            } else {
                r4 = 0xb;
            }
            break;

        case 20:
            if (val == 0) {
                if (func_0201b43c((UnkStruct_02260978 *) self->unk_B4, 10000) == 0) {
                    r4 = 0x15;
                } else {
                    r4 = 0x17;
                }
            }
            break;
    }

    if (r4 != 0xff) {
        c = (u8) r4;
        func_0206844c(self->unk_40, (u8 *) (&c), (int) ((*(void **) &data_ov045_02261380)));
    }
}
