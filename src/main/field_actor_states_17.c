/* field_actor_states_17: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200bb60 @ 0x0200bb60, 0x68 bytes, Thumb
 * func_0200b930 @ 0x0200b930, 0x230 bytes, Thumb
 * func_0200b8b4 @ 0x0200b8b4, 0x7c bytes, Thumb
 * func_0200b894 @ 0x0200b894, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
} UnkStruct_0200bb60;

typedef struct {
    int a;
    int b;
} UnkStruct_0200b930;

typedef union Pay {
    unsigned char b[16];
} Pay;

typedef struct T12c {
    unsigned char pad[4];
    int unk_04;
    int unk_08;
} T12c;

typedef struct UnkStruct_0200b930_2 {
    unsigned char pad_00[0xec];
    unsigned char pad_EC[0x10a - 0xec];
    u8 unk_10A;
    unsigned char pad_10B[0x12c - 0x10a - 1];
    T12c *unk_12C;
    unsigned char pad_130[0x7d4 - 0x12c - 4];
    Pay unk_7D4;
    unsigned char pad_7E4[0x7f0 - 0x7e4];
    int unk_7F0;
    unsigned char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
    unsigned char pad_804[0x814 - 0x804];
    int unk_814;
} UnkStruct_0200b930_2;

typedef struct {
    char pad_00[0x7d4];
    unsigned char sub[0x1c];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
    int unk_800;
} UnkStruct_0200b8b4;

typedef struct {
    int a;
    int b;
} TwoInts;

typedef struct {
    unsigned short unk_00;
    unsigned short pad_02;
    unsigned int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
} UnkStruct_0200b894;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_0200b894_2;

extern void func_02010f5c(void *);
extern int func_0200b83c(void *, unsigned int *, int, int, int, int);
extern void *data_020ccf94;
extern int data_020d83b4;
extern int data_020d83a4;
extern int func_02073908(void *a, int b);
extern int func_0203e1c4(void);
extern void func_0203ee14(void *self, void *b);
extern unsigned int *func_0200f27c(void *self, int code);
extern void func_020a8164(void *p, void *g);
extern unsigned char func_02008258(void *arg0, int index);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern void func_0203ee08(void *self, void *b);
extern void func_0200f268(void *self, int code);
extern int func_0203e19c(void);
extern int func_0200ad24(void *, UnkStruct_0200b930 *, int, int, int);
extern void func_02010d64(void *self);
extern int func_0200f530(void *self, void *loc);

void func_0200bb60(void *p)
{
    UnkStruct_0200bb60 *s = (UnkStruct_0200bb60 *) ((char *) p + 0x7d4);
    int w0 = s->unk_00;
    unsigned char b5 = s->unk_05;
    unsigned char b6 = s->unk_06;
    unsigned char b4 = s->unk_04;

    if (b4 >= 3) {
        func_02010f5c(p);
        return;
    }

    if (w0 >= 0) {
        unsigned int local[2];
        local[0] = b5;
        local[1] = b6;
        func_0200b83c(p, local, w0, 0, 6, -1);
    } else {
        if (b4 == 0) {
            int g = *(int *) ((char *) p + 0x818);
            if (g == 2) {
                s->unk_04 = 2;
            } else if (g == 1) {
                s->unk_04 = 1;
            }
        }
    }

    func_02010f5c(p);
}

void func_0200b930(UnkStruct_0200b930_2 *self)
{
    unsigned char *base = self->unk_7D4.b;
    unsigned char *statep = base + 4;
    void *b;
    int code;
    int flag;
    int hi;
    int lo;
    struct {
        int pad;
        UnkStruct_0200b930 a;
        UnkStruct_0200b930 b;
    } W;

    switch (base[4]) {
        case 0:
            break;
        case 1: {
            hi = base[5];
            lo = base[6];
            if (func_02073908(data_020ccf94, self->unk_800) != 0) {
                code = self->unk_814;
            } else {
                code = base[7];
            }
            flag = 1;
            switch (code) {
                case 3:
                    flag = 0;
                case 4:
                    W.a.a = hi;
                    W.a.b = lo;
                    func_0200b83c(self, (unsigned int *) (&W.a), -1, flag, 6, -1);
                    break;
                case 0x15:
                    flag = 0;
                case 0x16:
                    W.b.a = hi;
                    W.b.b = lo;
                    func_0200ad24(self, &W.b, flag, 6, -1);
                    break;
            }
        } break;
        case 2:
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            break;
        case 3:
            if (func_0203e1c4() != 0) {
                *statep = 4;
                b = self;
                if (self != 0) {
                    b = (char *) self + 0xec;
                }
                func_0203ee14(self, b);
                func_0200f27c(self, 0x11);
                func_020a8164((char *) self + 0xec, &data_020d83b4);
                self->unk_10A = 0;
                self->unk_12C->unk_08 = 1;
            }
            break;
        case 4:
            if (self->unk_12C != 0 && self->unk_12C->unk_04 != 0) {
                *statep = 5;
            }
            break;
        case 5:
            if (self->unk_12C != 0 && self->unk_12C->unk_04 == 0) {
                b = self;
                if (self != 0) {
                    b = (char *) self + 0xec;
                }
                func_0203ee08(self, b);
                func_0200f268(self, 0x11);
                func_0203e19c();
                *statep = 6;
            }
            break;
        case 6:
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            func_0200f268(self, 0xd);
            break;
        case 7:
            if (func_0203e1c4() != 0) {
                *statep = 8;
                b = self;
                if (self != 0) {
                    b = (char *) self + 0xec;
                }
                func_0203ee14(self, b);
                func_0200f27c(self, 0x11);
                func_020a8164((char *) self + 0xec, &data_020d83a4);
                self->unk_10A = 1;
                self->unk_12C->unk_08 = 1;
            }
            break;
        case 8:
            if (self->unk_12C != 0 && self->unk_12C->unk_04 != 0) {
                *statep = 9;
            }
            break;
        case 9:
            if (self->unk_12C != 0 && self->unk_12C->unk_04 == 0) {
                b = self;
                if (self != 0) {
                    b = (char *) self + 0xec;
                }
                func_0203ee08(self, b);
                func_0200f268(self, 0x11);
                func_0203e19c();
                self->unk_7FC = func_02008258(self, self->unk_7F0);
                func_0200d4e8(self, 3, 1, -1);
            }
            break;
    }
}

void func_0200b8b4(UnkStruct_0200b8b4 *self)
{
    unsigned char *sub;
    unsigned char y;
    TwoInts loc;

    if (func_02073908((void *) ((*(int *) &data_020ccf94)), self->unk_800) != 0) {
        func_0200bb60(self);
        func_02010d64(self);
        func_0200b930((UnkStruct_0200b930_2 *) self);
    } else {
        func_02010f5c(self);
        sub = self->sub;
        y = sub[6];
        loc.a = sub[5];
        loc.b = y;
        func_0200f530(self, &loc);
        func_02010d64(self);
        self->unk_7FC = (int) func_02008258(self, self->unk_7F0);
        func_0200b930((UnkStruct_0200b930_2 *) self);
    }
}

void func_0200b894(UnkStruct_0200b894 *out, UnkStruct_0200b894_2 *in, unsigned int v32, unsigned short v16, unsigned char v8)
{
    out->unk_08 = in->unk_00;
    out->unk_09 = in->unk_04;
    out->unk_04 = v32;
    out->unk_00 = v16;
    out->unk_0A = v8;
}
