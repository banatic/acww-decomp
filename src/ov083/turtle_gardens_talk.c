/* turtle_gardens_talk: 3 functions, module ov083
 * mwccarm 1.2/base -O4,s
 * func_ov083_02278c60 @ 0x02278c60, 0xc0 bytes, Thumb
 * func_ov083_02278b64 @ 0x02278b64, 0xfc bytes, Thumb
 * func_ov083_02278ab8 @ 0x02278ab8, 0xac bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02278c60 {
    void *ptr;
    unsigned char type;
};

struct UnkStruct_02278c60_2 {
    unsigned char pad[0xb0];
    void *ptr;
    int unk_B4;
};

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} UnkStruct_02278b64_2;

typedef struct UnkStruct_02278b64 {
    u8 pad_00[0x1e];
    u8 mode;
    u8 pad_1F[0x40 - 0x1f];
    void *callback;
    u8 pad_44[0xb4 - 0x44];
    int value;
    u16 result;
} UnkStruct_02278b64;

typedef struct UnkStruct_02278ab8 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_02278ab8;

typedef struct Msg {
    u8 unk_00;
    u8 unk_01;
    u16 h;
} Msg;

extern int func_020984e8(void);
extern int func_02099640(int argument0);
extern int func_02099e9c(u16 *p);
extern void func_0209e474(int *p);
extern void *func_0208602c(void);
extern int func_02086108(void *ctx, int a);
extern void func_020860f0(void *ctx, int a);
extern int func_020154b4(void *, void *, int, int, int);
extern int func_0209a000(void *, int);
extern void func_0206844c(void *, void *, void *);
extern int func_0202ea80(int, int);
extern int func_02099670(int argument0);
extern void func_02088aac(void *argument0);
extern int func_02099fe8(void);
extern void func_020ad7c8(void *);
extern void func_02015de4(void *, void *, int, int);
extern u8 data_ov083_02279338[];
extern u8 data_ov083_02279348[];
extern int func_020160b4(UnkStruct_02278ab8 *self);
extern int func_020ab504(int a);
extern void func_0209a050(int a);
extern int func_02015330(UnkStruct_02278ab8 *self, u16 *p, int a, int b, int c);
extern int func_020644cc(int a);

void func_ov083_02278c60(struct UnkStruct_02278c60_2 *self, struct UnkStruct_02278c60 *out)
{
    struct {
        u16 h;
        u8 pad[2];
        int arr[2];
    } local;
    u8 v;

    func_02099640(func_020984e8());
    out->ptr = ((char *) data_ov083_02279338);

    if (self->unk_B4 == -1) {
        local.h = 0x37e0;
        self->unk_B4 = func_02099e9c(&local.h);
        if (self->unk_B4 >= 0) {
            out->ptr = ((char *) data_ov083_02279348);
            out->type = 0;
            return;
        }
    }

    local.arr[0] = 0;
    local.arr[1] = 0;
    func_0209e474(local.arr);

    v = ((unsigned char *) &local)[6];
    if (v < 6 || v >= 0x12) {
        out->type = 0;
        return;
    }

    if (func_02086108(func_0208602c(), 1) == 0) {
        func_020860f0(func_0208602c(), 1);
        v = ((unsigned char *) self->ptr)[0x718];
        if (v == 0) {
            out->type = 1;
            return;
        } else if (v >= 1 && v <= 5) {
            out->type = 2;
            return;
        } else {
            out->type = 3;
            return;
        }
    } else {
        out->type = 0xa;
        return;
    }
}

void func_ov083_02278b64(UnkStruct_02278b64 *self)
{
    u8 *p = data_ov083_02279338;
    int r4 = 0xff;
    UnkStruct_02278b64_2 buf;

    if (self->value >= 0) {
        if (self->mode == 1 || self->mode == 4) {
            self->value = -2;
        }
        if (self->mode == 2) {
            buf.unk_02 = 0x1559;
            func_020154b4(self, &buf.unk_02, 0, 5, 0);
            buf.unk_04 = 0x1559;
            func_0209a000(&buf.unk_04, 0);
            buf.unk_00 = 4;
            func_0206844c(self->callback, &buf.unk_00, data_ov083_02279348);
        }
    } else {
        if (self->mode == 5 || self->mode == 6 || self->mode == 9) {
            if (func_0202ea80(0x1d, 1) == 0) {

                func_02088aac((void *) func_02099670(func_020984e8()));
                if (func_02099fe8() >= 0) {
                    r4 = 7;
                    func_020ad7c8(&buf.unk_06);
                    self->result = buf.unk_06;
                }
            }
        }
        if (self->mode == 7) {
            func_020154b4(self, &self->result, 0, 5, 0);
            func_0209a000(&self->result, 0);
            func_02015de4(self, &self->result, 0, 7);
            r4 = 8;
        }
        if (r4 != 0xff) {
            buf.unk_01 = (u8) r4;
            func_0206844c(self->callback, &buf.unk_01, p);
        }
    }
}

void func_ov083_02278ab8(UnkStruct_02278ab8 *self)
{
    Msg m;
    int a;
    int k;
    int code;
    int v;

    a = func_020ab504(func_020160b4(self));
    k = (int) ((int *) data_ov083_02279338);
    code = 0xff;
    v = self->unk_B4;
    if (v >= 0) {
        k = (int) ((int *) data_ov083_02279348);
        if (self->unk_1E == 0 && a == 0) {
            if (v >= 0) {
                func_0209a050(v);
                m.h = 0x37e0;
                func_02015330(self, &m.h, 0, 5, 0);
            }
            code = 2;
        }
        if (code != 0xff) {
            m.unk_00 = (u8) code;
            func_0206844c((void *) self->unk_40, (void *) (&m.unk_00), (void *) k);
        }
    } else {
        if (self->unk_1E == 0xa && a == 0) {
            if (func_020644cc(3) == 0) {
                code = 0xc;
            } else {
                code = (u8) (func_020644cc(0xb) + 0x1c);
            }
        }
        if (code != 0xff) {
            m.unk_01 = (u8) code;
            func_0206844c((void *) self->unk_40, (void *) (&m.unk_01), (void *) k);
        }
    }
}
