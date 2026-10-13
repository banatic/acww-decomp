/* func_0202bdb4 @ 0x0202bdb4, 0x47c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a;
    int b;
    int pad[3];
} UnkStruct_0202bdb4;

typedef struct {
    u8 pad[0x830];
    void *unk_830;
} UnkStruct_0202bdb4_2;

typedef struct {
    u8 pad_00[0x40];
    int unk_40;
    u8 pad_44[0x100 - 0x44];
    UnkStruct_0202bdb4_2 *unk_100;
    char unk_104[0x1e];
    u8 unk_122;
    u8 pad_123[0x12c - 0x123];
    int unk_12C;
    u8 pad_130[0x13c - 0x130];
    u8 unk_13C;
    u8 pad_13D[0x19c - 0x13d];
    u16 unk_19C;
    u8 unk_19E;
} UnkStruct_0202bdb4_3;

typedef struct {
    void *p;
    u8 b;
} UnkStruct_0202bdb4_4;

typedef struct {
    int a;
    u8 b;
} ErrData;

typedef struct {
    u8 pad[0x1d];
    u8 unk_1D;
} UnkStruct_0202bdb4_5;

extern ErrData data_020c89f8;
extern ErrData data_020c8b28;
extern ErrData data_020c8dd8;
extern ErrData data_020c8ca0;
extern ErrData data_020c8d10;
extern ErrData data_020c89d0;
extern ErrData data_020c8a38;
extern ErrData data_020c8970;
extern ErrData data_020c8c88;
extern ErrData data_020c8ac8;
extern ErrData data_020c8c70;
extern ErrData data_020c8c38;
extern ErrData data_020c8c90;
extern ErrData data_020c8a80;
extern ErrData data_020c8a78;
extern ErrData data_020c8cf0;
extern ErrData data_020c8a18;
extern ErrData data_020c8b78;
extern ErrData data_020c8a00;
extern ErrData data_020c8b90;
extern ErrData data_020c8b60;
extern ErrData data_020c8bc8;
extern ErrData data_020c8d80;
extern ErrData data_020c8c58;
extern u8 data_020e54a8;
extern void *data_020ccf94;

extern UnkStruct_0202bdb4_5 *func_0207f270(void *a);
extern int func_0208150c(void *a);
extern int func_020036e8(int a);
extern int func_0202c424(UnkStruct_0202bdb4_3 *self, int *out);
extern void *func_020794c4(UnkStruct_0202bdb4_5 *a);
extern int func_020ba4e4(void);
extern int func_020984e8(void);
extern void func_0202bcd4(UnkStruct_0202bdb4_3 *self);
extern int func_0202c420(UnkStruct_0202bdb4_3 *self);
extern int func_0202c3f0(UnkStruct_0202bdb4_3 *self);
extern int func_0202c3e4(UnkStruct_0202bdb4_3 *self, int r6);
extern ErrData *func_0202c388(UnkStruct_0202bdb4_3 *self, int *a, void *b);
extern int func_0202c31c(UnkStruct_0202bdb4_3 *self, int *a, void *b);
extern ErrData *func_0202c2c4(UnkStruct_0202bdb4_3 *self, int a);
extern int func_0202c2a8(UnkStruct_0202bdb4_3 *self);
extern int func_0202c37c(UnkStruct_0202bdb4_3 *self, int r6);
extern ErrData *func_0202c350(UnkStruct_0202bdb4_3 *self);
extern int func_0202c27c(UnkStruct_0202bdb4_3 *self, UnkStruct_0202bdb4_5 *o);
extern ErrData *func_0202c254(UnkStruct_0202bdb4_3 *self, int *a, UnkStruct_0202bdb4_5 *o);
extern int func_0202c248(UnkStruct_0202bdb4_3 *self, void *a);
extern int func_0202c23c(UnkStruct_0202bdb4_3 *self, void *a);
extern int func_0202c230(UnkStruct_0202bdb4_3 *self, void *a);
extern int func_0207dd1c(void *a);
extern int func_020ae32c(void);
extern int func_020ae2c4(void);
extern void func_020ae774(void *a);
extern int func_020ae3b8(unsigned int a);
extern int func_020ae5bc(int a, void *b);
extern void func_02068404(int a, int b, void *c);
extern void func_020ae75c(void *a);
extern int func_02073d90(void *a);
extern int func_02081864(void);
extern int func_02099fe8(void);
extern void func_02063ccc(UnkStruct_0202bdb4 *o, int a, int b);
extern void func_020638d4(u16 *out, UnkStruct_0202bdb4 *o, int a, int b, int c, int d, int e);
extern void func_02063cc8(UnkStruct_0202bdb4 *o);
extern void func_02015de4(UnkStruct_0202bdb4_3 *self, void *b, int c, int d);
extern void func_02081878(int a);
extern int func_020b6730(void);
extern void *func_0207f1c8(void *a);
extern void *func_0209b5ec(void *a);
extern int func_0209c330(void *a);
extern int func_020b65c4(void);
extern int func_020b66d8(void);
extern int func_020b671c(int a);
extern int func_020b6680(void);
extern int func_0209dcac(void);
extern void *func_0207944c(UnkStruct_0202bdb4_5 *a);
extern int func_020793c4(void *a);
extern int func_020644cc(int a);
extern void func_0202da38(UnkStruct_0202bdb4_3 *self, char *name, u8 *b, int len, int c, int d, int e, int f, int g);
extern void func_02015fb0(UnkStruct_0202bdb4_3 *self, int a, int b, int c, int d, int e);

extern unsigned char data_021f3b30[];

void func_0202bdb4(UnkStruct_0202bdb4_3 *self, UnkStruct_0202bdb4_4 *out)
{
    void *local18;
    UnkStruct_0202bdb4_5 *obj;
    int local20;
    void *local24;
    int local28;
    u16 h[2];
    int num;
    int code2;
    int val;
    UnkStruct_0202bdb4 o;
    char b0[0x34];
    ErrData *err;
    int mode;
    int r6;
    int code;
    int n;

    local18 = self->unk_100->unk_830;
    obj = func_0207f270(local18);
    local20 = func_020036e8(func_0208150c(local18));
    num = 0;
    r6 = func_0202c424(self, &num);
    local24 = func_020794c4(obj);
    mode = func_020ba4e4();
    code2 = 0;
    func_020984e8();
    local28 = 0;
    code = -1;
    h[0] = 0xfff1;
    val = -1;
    func_0202bcd4(self);

    if (func_0202c420(self) != 0) {
        err = &data_020c89f8;
        if (r6 == 0) {
            self->unk_13C = 1;
        }
    } else if (func_0202c3f0(self) != 0) {
        err = &data_020c8b28;
        if (r6 == 0) {
            self->unk_13C = 1;
        }
    } else if (func_0202c3e4(self, r6) != 0) {
        err = func_0202c388(self, &code2, local18);
    } else if (r6 == 6) {
        err = &data_020c8dd8;
        code2 = 7;
        local28 = 3;
    } else if (func_0202c31c(self, &val, (char *) self->unk_100 + 0x5c) != 0) {
        err = func_0202c2c4(self, val);
    } else if (func_0202c2a8(self) != 0) {
        err = &data_020c8ca0;
    } else if (func_0202c37c(self, r6) != 0) {
        err = func_0202c350(self);
    } else if (r6 == 4) {
        err = &data_020c8d10;
        if (num >= 0x186) {
            code = 1;
            code2 = 5;
            local28 = code;
        }
    } else if (r6 == 3) {
        err = &data_020c89d0;
    } else if (func_0202c27c(self, obj) != 0) {
        err = func_0202c254(self, &code2, obj);
    } else if (func_0202c248(self, local24) != 0) {
        err = &data_020c8a38;
    } else if (func_0202c23c(self, local24) != 0) {
        err = &data_020c8970;
    } else if (func_0202c230(self, local24) != 0) {
        err = &data_020c8c88;
    } else if (func_0207dd1c(local18) != 0 && func_020ae32c() != 0 && func_020ae2c4() == 0) {
        func_020ae774(b0);
        func_020ae5bc(func_020ae3b8((unsigned int) data_021f3b30), b0);
        err = &data_020c8ac8;
        func_02068404(self->unk_40, 4, b0);
        func_020ae75c(b0);
    } else if (func_02073d90(data_020ccf94) == 0 && self->unk_12C != 0 && func_02081864() != 0 && func_02099fe8() != -1) {
        err = &data_020c8c70;
        func_02063ccc(&o, 0, 0);
        func_020638d4(&h[1], &o, 0, 0, 1, 1, 0);
        self->unk_19C = h[1];
        func_02063cc8(&o);
        self->unk_19E = 0;
        func_02015de4(self, &self->unk_19C, 0, 7);
        if (self->unk_12C != 0) {
            func_02081878(self->unk_12C);
        }
    } else if (func_020b6730() != 0) {
        err = &data_020c8c38;
        if (func_0209c330(func_0209b5ec(func_0207f1c8(local18))) != 4) {
            code2 = 1;
        }
    } else if (func_020b65c4() == 0xa) {
        err = &data_020c8c90;
        if (func_0209c330(func_0209b5ec(func_0207f1c8(local18))) != 3) {
            code2 = 1;
        }
    } else if (func_020b66d8() != 0 && func_020b671c(func_020b65c4()) == 1) {
        err = &data_020c8a80;
    } else if (r6 == 1) {
        if (func_020b6680() != 0) {
            err = &data_020c8a78;
        } else if (mode == 1) {
            err = &data_020c8cf0;
        } else if (mode == 2) {
            err = &data_020c8a18;
        } else {
            err = &data_020c8b78;
        }
        code2 = func_0209dcac();
    } else if (func_0209c330(func_0209b5ec(func_0207f1c8(local18))) == 8) {
        err = &data_020c8a00;
    } else if (func_020793c4(func_0207944c(obj)) != 0) {
        err = &data_020c8b90;
        if (func_020793c4(func_0207944c(obj)) == 2) {
            code2 = 1;
        }
    } else if (local24 == (void *) 1) {
        err = &data_020c8b60;
        code2 = func_0209dcac();
    } else {
        unsigned int ok;
        if (data_020e54a8 == 0) {
            ok = 1;
        } else {
            ok = 0;
        }
        if (ok != 0 && mode == 1) {
            err = &data_020c8bc8;
        } else if (ok != 0 && mode == 2) {
            err = &data_020c8d80;
        } else {
            err = &data_020c8c58;
            if (func_020644cc(9) != 0) {
                local28 = (u8) (err->b - 1);
            }
            code2 = func_0209dcac();
        }
    }

    if (err != 0) {
        if (code == -1) {
            code = err->b;
        }
        func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, local20, err->a, (u8) code, code2, local28);
    }

    n = num;
    if (n > 0) {
        int t;
        if (n >= 0x46) {
            t = 9;
        } else {
            t = n / 7;
        }
        if (n >= 0x186) {
            n = 0xc;
        } else {
            n = n / 0x1e;
        }
        func_02015fb0(self, t, 2, 1, 0, 0);
        func_02015fb0(self, n, 3, 2, 0, 0);
    }
    obj->unk_1D |= 4;
    out->p = self->unk_104;
    out->b = self->unk_122;
}
