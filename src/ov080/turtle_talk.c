/* turtle_talk: 3 functions, module ov080
 * mwccarm 1.2/base -O4,s
 * func_ov080_02278c88 @ 0x02278c88, 0x164 bytes, Thumb
 * func_ov080_02278b30 @ 0x02278b30, 0x158 bytes, Thumb
 * func_ov080_02278ab8 @ 0x02278ab8, 0x78 bytes, Thumb
 */

#include "types.h"

typedef struct {
    void *ptr;
    unsigned char status;
} OutputType;

typedef struct {
    unsigned char pad_00[0xb4];
    int unk_B4;
} InputType;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned short unk_02;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
    unsigned short unk_0E;
    unsigned short unk_10;
    unsigned short unk_12;
    unsigned short unk_14;
} Buf;

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x40 - 0x1f];
    void *unk_40;
    unsigned char pad_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_02278b30;

typedef struct UnkStruct_02278ab8 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_02278ab8;

typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 h;
} Msg;

extern void func_02098ff8(void *handle, int kind);
extern int func_020644cc(int val);
extern int func_02099e9c(unsigned short *ptr);
extern int func_0203cc38(void);
extern int func_02099fe8(void);
extern void *func_02098844(void *table, int index);
extern int func_02099a28(unsigned int object);
extern int func_0203cc1c(void);
extern char data_ov080_022793a8;
extern char data_ov080_02279398;
extern char data_ov080_022793bc;
extern char data_021dc7bc;
extern int func_020984e8(void);
extern int func_02099020(int, int);
extern int func_0209a000(void *, int);
extern int func_020154b4(void *, void *, int, int, int);
extern void func_02015de4(void *, void *, int, int);
extern void func_0206844c(void *, void *, void *);
extern int func_020160b4(UnkStruct_02278ab8 *self);
extern int func_020ab504(int a);
extern void func_0209a050(int a);
extern int func_02015330(UnkStruct_02278ab8 *self, u16 *p, int a, int b, int c);

void func_ov080_02278c88(InputType *self, OutputType *out)
{
    void *handle;
    int i;

    handle = (void *) func_020984e8();

    if (func_02099020((int) handle, 1) != 0) {
        out->ptr = &data_ov080_022793a8;
        if (func_02099020((int) handle, 0xd) == 0) {
            out->status = 0;
            func_02098ff8(handle, 0xd);
        } else {
            out->status = (unsigned char) (func_020644cc(4) + 3);
        }
        func_02098ff8(handle, 0xa);
        return;
    }

    if (self->unk_B4 == -1) {
        unsigned short val = 0x37e0;
        self->unk_B4 = func_02099e9c(&val);
        if (self->unk_B4 < 0) {
            // fall through
        } else {
            out->ptr = &data_ov080_02279398;
            out->status = 0;
            return;
        }
    }

    out->ptr = &data_ov080_022793bc;

    if (func_02099020((int) handle, 0x21) == 0) {
        if (func_0203cc38() != 0) {
            out->status = 0;
            if (func_02099fe8() < 0) {
                out->status = 9;
                return;
            } else {
                for (i = 0; i < 4; i++) {
                    void *p = func_02098844(&data_021dc7bc, i);
                    if (p != 0 && func_02099a28((unsigned int) p) != 0 && p != handle && func_02099020((int) p, 0x21) != 0) {
                        out->status = 2;
                        return;
                    }
                }
                return;
            }
        }
    }

    if (func_02099020((int) handle, 0x22) == 0) {
        if (func_0203cc1c() != 0) {
            out->status = 3;
            if (func_02099fe8() < 0) {
                out->status = 0xa;
                return;
            } else {
                for (i = 0; i < 4; i++) {
                    void *p = func_02098844(&data_021dc7bc, i);
                    if (p != 0 && func_02099a28((unsigned int) p) != 0 && p != handle && func_02099020((int) p, 0x22) != 0) {
                        out->status = 5;
                        return;
                    }
                }
                return;
            }
        }
    }

    out->status = (unsigned char) (func_020644cc(3) + 6);
}

void func_ov080_02278b30(UnkStruct_02278b30 *self)
{
    Buf buf;
    int idx = 0xff;
    int r7;
    void *dataptr;

    if (self->unk_B4 >= 0) {
        if (self->unk_1E == 1 || self->unk_1E == 4) {
            self->unk_B4 = -2;
        }
        if (self->unk_1E != 2) {
            return;
        }
        buf.unk_02 = 0x1559;
        func_020154b4(self, &buf.unk_02, 0, 5, 0);
        buf.unk_04 = 0x1559;
        func_0209a000(&buf.unk_04, 0);
        buf.unk_00 = 4;
        func_0206844c(self->unk_40, &buf, ((unsigned char *) &data_ov080_02279398));
    } else {
        r7 = func_020984e8();
        if (func_02099020(r7, 1) != 0) {
            dataptr = ((unsigned char *) &data_ov080_022793a8);
        } else {
            dataptr = ((unsigned char *) &data_ov080_022793bc);
            switch (self->unk_1E) {
                case 0:
                case 2:
                    buf.unk_06 = 0x1375;
                    if (func_0209a000(&buf.unk_06, 0) != 0) {
                        buf.unk_08 = 0x1375;
                        func_020154b4(self, &buf.unk_08, 0, 5, 0);
                        func_02098ff8((void *) r7, 0x21);
                        buf.unk_0A = 0x1375;
                        func_02015de4(self, &buf.unk_0A, 0, 7);
                        idx = 1;
                    }
                    break;
                case 3:
                case 5:
                    buf.unk_0C = 0x1377;
                    if (func_0209a000(&buf.unk_0C, 0) != 0) {
                        buf.unk_0E = 0x1377;
                        func_020154b4(self, &buf.unk_0E, 0, 5, 0);
                        func_02098ff8((void *) r7, 0x22);
                        buf.unk_10 = 0x1377;
                        func_02015de4(self, &buf.unk_10, 0, 7);
                        idx = 4;
                    }
                    break;
                default:
                    break;
            }
        }
        if (idx != 0xff) {
            buf.unk_01 = idx;
            func_0206844c(self->unk_40, &buf.unk_01, dataptr);
        }
    }
}

void func_ov080_02278ab8(UnkStruct_02278ab8 *self)
{
    Msg m;
    int t;
    int a;
    int k;
    int v;
    int code;

    a = func_020ab504(func_020160b4(self));
    t = func_020984e8();
    code = 0xff;
    v = self->unk_B4;
    if (v >= 0) {
        k = (int) ((int *) &data_ov080_02279398);
        if (self->unk_1E == 0 && a == 0) {
            if (v >= 0) {
                func_0209a050(v);
                m.h = 0x37e0;
                func_02015330(self, &m.h, 0, 5, 0);
            }
            code = 2;
        }
        if (code != 0xff) {
            m.b = (u8) code;
            func_0206844c((void *) self->unk_40, (void *) (&m.b), (void *) k);
        }
    } else {
        func_02099020(t, 1);
    }
}
