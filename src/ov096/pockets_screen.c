/* pockets_screen: 27 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229cdec @ 0x0229cdec, 0x60 bytes, Thumb
 * func_ov096_0229cd8c @ 0x0229cd8c, 0x60 bytes, Thumb
 * func_ov096_0229cc74 @ 0x0229cc74, 0x118 bytes, Thumb
 * func_ov096_0229cc24 @ 0x0229cc24, 0x50 bytes, Thumb
 * func_ov096_0229cc10 @ 0x0229cc10, 0x14 bytes, Thumb
 * func_ov096_0229cbe0 @ 0x0229cbe0, 0x30 bytes, Thumb
 * func_ov096_0229cbbc @ 0x0229cbbc, 0x24 bytes, Thumb
 * func_ov096_0229ca78 @ 0x0229ca78, 0x144 bytes, Thumb
 * func_ov096_0229c888 @ 0x0229c888, 0x1f0 bytes, Thumb
 * func_ov096_0229c7e0 @ 0x0229c7e0, 0xa8 bytes, Thumb
 * func_ov096_0229c63c @ 0x0229c63c, 0x1a4 bytes, Thumb
 * func_ov096_0229c560 @ 0x0229c560, 0xdc bytes, Thumb
 * func_ov096_0229c538 @ 0x0229c538, 0x26 bytes, Thumb
 * func_ov096_0229c514 @ 0x0229c514, 0x24 bytes, Thumb
 * func_ov096_0229c4ec @ 0x0229c4ec, 0x28 bytes, Thumb
 * func_ov096_0229c4dc @ 0x0229c4dc, 0x10 bytes, Thumb
 * func_ov096_0229c454 @ 0x0229c454, 0x88 bytes, Thumb
 * func_ov096_0229c434 @ 0x0229c434, 0x20 bytes, Thumb
 * func_ov096_0229c414 @ 0x0229c414, 0x20 bytes, Thumb
 * func_ov096_0229c3c4 @ 0x0229c3c4, 0x50 bytes, Thumb
 * func_ov096_0229c348 @ 0x0229c348, 0x7c bytes, Thumb
 * func_ov096_0229c310 @ 0x0229c310, 0x38 bytes, Thumb
 * func_ov096_0229c2fc @ 0x0229c2fc, 0x12 bytes, Thumb
 * func_ov096_0229c2ec @ 0x0229c2ec, 0xe bytes, Thumb
 * func_ov096_0229c2dc @ 0x0229c2dc, 0xe bytes, Thumb
 * func_ov096_0229c22c @ 0x0229c22c, 0xb0 bytes, Thumb
 * func_ov096_0229c180 @ 0x0229c180, 0xac bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229cc74 {
    unsigned char pad_00[0xb6];
    unsigned char unk_B6;
    unsigned char pad_B7[0x2361];
    char unk_2418;
    unsigned char pad_2419[0x533];
    char unk_294C;
};

typedef struct {
    char pad_00[0xbd];
    char flag;
} UnkStruct_0229cc10;

typedef struct UnkStruct_0229cbbc {
    char pad_00[0x64];
    unsigned int unk_64;
} UnkStruct_0229cbbc;

typedef struct {
    u8 pad_00[0xb5];
    u8 byte;
} UnkStruct_0229c560;

struct UnkStruct_0229c4dc {
    char pad_00[0xb6];
    unsigned char b6;
};

typedef struct UnkStruct_0229c348 {
    u8 pad_00[0xac];
    u16 unk_AC;
} UnkStruct_0229c348;

typedef struct {
    unsigned char pad_00[0x94];
    unsigned int flag;
} Struct_ov096_0229c2fc;

typedef struct {
    char pad_00[0x94];
    unsigned int flags;
} UnkStruct_0229c2ec;

typedef struct {
    char pad_00[0x94];
    unsigned int unk_94;
} Struct_ov096_0229c2dc;

struct Big {
    void *vtable;
};

extern int func_ov096_0229e158(void *receiver);
extern int func_ov096_0229e4a4(int param1, int param2);
extern void func_ov002_02208d30(void *, int);
extern int func_ov096_0229f830(void *, int);
extern int func_ov096_0229f820(void *, int);
extern void func_ov096_0229cf84(void *, int);
extern void func_ov096_0229ce4c(void *, int);
extern int func_ov002_02208d18(void *);
extern int func_ov002_02208d4c(void *, int, int);
extern void func_ov096_0229ddd8(void *);
extern int func_ov002_02207d24(void *, int);
extern void func_ov096_0229d1d4(void *, int);
extern void func_ov002_02209740(void *dst, unsigned char c, void *d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_02073dd4(void *arg0, int arg1);
extern UnkStruct_0229cbbc *data_020ccf94;
extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088bc(void *p);
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern void func_ov002_0220a254(void *);
extern int func_ov096_0229ee38(unsigned char *, int);
extern int func_ov096_0229ee50(unsigned char *, int);
extern int func_ov096_0229ee10(unsigned char *, int);
extern void func_ov096_0229f7e0(unsigned char *);
extern void func_ov002_0220a2b4(unsigned char *);
extern int func_ov096_0229f800(UnkStruct_0229c560 *self, int arg);
extern int func_ov096_0229f810(UnkStruct_0229c560 *self, int arg);
extern void func_ov002_02208090(int param1, int param2);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov096_022a1540(int param1);
extern void func_0208f0c4(void *ptr, int val);
extern void func_0200467c(int cmd);
extern int func_020ee45c(int);
extern void func_ov090_022993cc(int, int);
extern int func_ov096_0229f054(void *p, unsigned char b);
extern unsigned short func_ov096_0229f0dc(void *, unsigned char);
extern int func_0204bd5c(short *);
extern void func_020665f0(int, unsigned char);
extern int func_ov002_02208a24(void *, int, unsigned char);
extern void func_0206fcb0(int);
extern int func_ov096_022a18dc(void *, int);
extern unsigned int func_0204bd40(short *);
extern int func_0204bd20(int, int);
extern void func_ov096_0229f5e0(void *, unsigned char, int, int);
extern int func_0203ac5c(void);
extern int func_0203ac2c(void);
extern int func_0203ac44(void);
extern int func_020984e8(void);
extern u16 *func_020993a8(unsigned int argument0);
extern void func_0206f190(volatile u16 *out, void *a, void *b, void *c);
extern void func_ov096_0229e82c(UnkStruct_0229c348 *self, int a);
extern void func_ov096_0229e6a0(UnkStruct_0229c348 *self);
extern int data_ov096_022a23e8;
extern void func_02066688(void *);
extern void *func_ov002_0220b464(void *);
extern void *func_0206e35c(void *);
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_02209ac8(void *);
extern void *func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void *func_ov002_02207e28(void *);
extern void *func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void *func_ov094_0229afe0(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern void func_ov128_0229bc30(void *);

unsigned char *func_ov096_0229cbe0(void *a, void *b);
void func_ov096_0229c414(int a);
int func_ov096_0229c310(char *self);
int func_ov096_0229c2fc(Struct_ov096_0229c2fc *p, unsigned int mask);
void func_ov096_0229c2ec(UnkStruct_0229c2ec *self, unsigned int bits);
void func_ov096_0229c2dc(Struct_ov096_0229c2dc *s, unsigned int mask);

void func_ov096_0229cdec(unsigned char *arg)
{
    int n = func_ov096_0229e158(arg);
    if (n >= 100) {
        func_ov002_02208d4c((void *) (arg + 0x294c), 0x6e, 0x0b);
        func_ov002_02208d4c((void *) (arg + 0x294c), 0x6f, 0x0c);
    }
    if (n >= 1000) {
        func_ov002_02208d4c((void *) (arg + 0x294c), 0x70, 0x0d);
    }
    if (n >= 10000) {
        func_ov002_02208d4c((void *) (arg + 0x294c), 0x71, 0x0e);
    }
}

void func_ov096_0229cd8c(int param1)
{
    if (func_ov096_0229e4a4(param1, 5) != 0xfff1) {
        func_ov002_02208d4c((void *) (param1 + 0x294c), 0x75, 0x11);
    }
    if (func_ov096_0229e4a4(param1, 4) != 0xfff1) {
        func_ov002_02208d4c((void *) (param1 + 0x294c), 0x76, 0x10);
    }
    if (func_ov096_0229e4a4(param1, 3) != 0xfff1) {
        func_ov002_02208d4c((void *) (param1 + 0x294c), 0x77, 0xf);
    }
}

void func_ov096_0229cc74(struct UnkStruct_0229cc74 *self, int kind, int flag)
{
    func_ov096_0229c2dc((Struct_ov096_0229c2dc *) self, 0x00040000);
    self->unk_B6 = (char) kind;
    func_ov002_02208d30(&self->unk_294C, 0x22);

    if (func_ov096_0229f830(self, kind)) {
        func_ov096_0229cf84(self, kind);
        goto common;
    } else if (func_ov096_0229f820(self, kind)) {
        func_ov096_0229ce4c(self, kind);
        goto common;
    } else if (kind == 0x25) {
        func_ov096_0229cdec((unsigned char *) self);
        goto common;
    } else if (kind == 0x24) {
        func_ov096_0229cd8c((int) self);
        goto common;
    } else if (kind != 0x27) {
        return;
    }

common:
    if (func_ov002_02208d18(&self->unk_294C) == 0) {
        if (func_ov096_0229f830(self, kind) || func_ov096_0229f820(self, kind)) {
            func_ov002_02208d4c(&self->unk_294C, 0x7c, 0x22);
        } else {
            if (kind == 0x25 || kind == 0x27) {
                func_ov002_02208d4c(&self->unk_294C, 0x7b, 0x22);
                self->unk_B6 = 0x25;
            } else if (kind == 0x24) {
                func_ov002_02208d4c(&self->unk_294C, 0x7a, 0x22);
            }
        }
    } else {
        func_ov002_02208d4c(&self->unk_294C, 2, 0x22);
    }

    func_ov096_0229ddd8(self);
    if (flag == 0) {
        func_ov002_02207d24(&self->unk_2418, 1);
    }
    func_ov096_0229d1d4(self, flag);
    if (func_ov096_0229f830(self, kind) == 0 && kind != 0x24) {
        func_ov096_0229c414((int) self);
    }
}

void func_ov096_0229cc24(unsigned int arg)
{
    func_ov096_0229c2ec((UnkStruct_0229c2ec *) ((void *) arg), 0x40000);
    func_ov002_02208d30((void *) (arg + 0x294c), 0x22);
    func_ov002_02208d4c((void *) (arg + 0x294c), 0x1a, 0x22);
    func_ov002_02208d4c((void *) (arg + 0x294c), 0x15, 9);
    func_ov002_02208d4c((void *) (arg + 0x294c), 0x19, 0x22);
    func_ov096_0229d1d4((void *) arg, 0);
}

int func_ov096_0229cc10(UnkStruct_0229cc10 *s)
{
    s->flag = 0;
    return (int) func_ov096_0229cbe0(s, (void *) 1);
}

unsigned char *func_ov096_0229cbe0(void *a, void *b)
{
    func_ov096_0229ddd8(a);
    func_ov002_02209740((char *) a + 0x2564, *(unsigned char *) ((char *) a + 0xbd), b);
    return func_ov002_02208098((void *) (a), 0x22);
}

unsigned char func_ov096_0229cbbc(void *self)
{
    unsigned int field = data_020ccf94->unk_64;
    if (func_02073dd4(data_020ccf94, field) != 0) {
        return (unsigned char) field;
    }
    return 0;
}

void func_ov096_0229ca78(unsigned char *self, void *other, unsigned int arg2)
{
    int v = self[0xb5];
    int n = 0;

    while (v >= 5) {
        v -= 5;
        n++;
    }

    if (func_ov002_022088ac((int) other) != 0) {
        if (func_ov002_022088cc(other) != 0 && n != 0) {
            goto tail;
        }
        if (v == 0) {
            if (n == 2) {
                if (func_ov096_0229c310((char *) self) != 0) {
                    self[0xb5] = 0x21;
                    return;
                }
            }
            self[0xb5] = (n + 2) * 2 + 0x10;
            func_ov096_0229c2ec((UnkStruct_0229c2ec *) self, 0x10);
        } else {
            self[0xb5] = self[0xb5] - 1;
            v--;
        }
    } else {
        if (func_ov002_0220889c((int) other) == 0) {
            goto tail;
        }
        if (func_ov002_022088bc(other) != 0) {
            goto tail;
        }
        if (v == 4) {
            self[0xb5] = (n + 2) * 2 + 0xf;
        } else {
            self[0xb5] = self[0xb5] + 1;
            v++;
        }
    }

tail:
    if (func_ov096_0229f830(self, (unsigned char) self[0xb5]) == 0) {
        return;
    }
    if (func_ov096_0229c2fc((Struct_ov096_0229c2fc *) self, 0x30) != 0) {
        return;
    }

    if (func_ov002_022088cc(other) != 0) {
        if (n > 0) {
            self[0xb5] -= 5;
            return;
        }
        if (v <= 2) {
            if (func_ov096_0229ee10((unsigned char *) self, arg2) != 0) {
                self[0xb5] = 0x25;
                return;
            }
        }
        if (func_ov096_0229ee38((unsigned char *) self, arg2) != 0) {
            self[0xb5] = 0x22;
            return;
        }
        if (func_ov096_0229ee50((unsigned char *) self, arg2) != 0) {
            self[0xb5] = 0x24;
        }
    } else {
        if (func_ov002_022088bc(other) != 0 && n < 2) {
            self[0xb5] += 5;
        }
    }
    return;
}

void func_ov096_0229c888(unsigned char *self, int param1, int param2)
{
    int v7 = (int) self[0xb5] - 15;
    int r4 = v7 >> 1;

    if (func_ov002_022088ac(param1) == 0) {
        goto L_c944;
    }

    if ((v7 & 1) <= 0) {
        goto L_c8bc;
    }
    self[0xb5] -= 1;
    goto exit_block;

L_c8bc:
    if (param2 != 2) {
        goto L_c8c2;
    }
    goto exit_block;

L_c8c2:
    if (r4 < 2) {
        goto L_c8d6;
    }
    self[0xb5] = (r4 - 2) * 5 + 4;
    goto exit_block;

L_c8d6: {
    int f1 = func_ov096_0229ee38(self, param2);
    int f2 = func_ov096_0229ee50(self, param2);
    if ((f1 & f2) != 0) {
        if (r4 == 0) {
            self[0xb5] = 0x24;
        } else {
            self[0xb5] = 0x22;
        }
        goto exit_block;
    } else {
        if (f1 != 0) {
            self[0xb5] = 0x22;
            goto exit_block;
        } else {
            if (f2 != 0) {
                self[0xb5] = 0x24;
                goto exit_block;
            } else {
                if (func_ov096_0229ee10(self, param2) != 0) {
                    self[0xb5] = 0x25;
                    goto exit_block;
                } else {
                    self[0xb5] = 4;
                    goto exit_block;
                }
            }
        }
    }
}

L_c944:
    if (func_ov002_0220889c(param1) == 0) {
        goto exit_block;
    }
    if ((v7 & 1) >= 1) {
        goto L_c966;
    }
    self[0xb5] += 1;
    goto exit_block;

L_c966:
    if (param2 == 2) {
        goto exit_block;
    }
    func_ov096_0229c2ec((UnkStruct_0229c2ec *) self, 0x20);
    if (r4 >= 2) {
        goto L_c9e4;
    }

    if (func_ov096_0229ee10(self, param2) != 0) {
        self[0xb5] = 0x25;
        goto exit_block;
    } else {
        int f1 = func_ov096_0229ee38(self, param2);
        int f2 = func_ov096_0229ee50(self, param2);
        if ((f1 & f2) != 0) {
            if (r4 == 0) {
                self[0xb5] = 0x24;
            } else {
                self[0xb5] = 0x22;
            }
            goto exit_block;
        } else {
            if (f1 != 0) {
                self[0xb5] = 0x22;
                goto exit_block;
            } else {
                if (f2 != 0) {
                    self[0xb5] = 0x24;
                    goto exit_block;
                } else {
                    self[0xb5] = 0;
                    goto exit_block;
                }
            }
        }
    }

L_c9e4:
    if (r4 == 4) {
        if (func_ov096_0229c310((char *) self) != 0) {
            self[0xb5] = 0x21;
            goto end;
        }
    }
    self[0xb5] = (r4 - 2) * 5;
    // fall through to exit_block

exit_block:
    if (func_ov096_0229f820((void *) self, self[0xb5]) == 0) {
        goto end;
    }
    if (func_ov096_0229c2fc((Struct_ov096_0229c2fc *) self, 0x30) != 0) {
        goto end;
    }
    if (func_ov002_022088cc((void *) param1) != 0) {
        if (r4 > 0) {
            self[0xb5] -= 2;
            goto end;
        } else {
            if (param2 != 0) {
                goto end;
            }
            func_ov096_0229f7e0(self);
            func_ov002_0220a254(self + 0x2500);
            goto end;
        }
    } else {
        if (func_ov002_022088bc((void *) param1) == 0) {
            goto end;
        }
        if (r4 >= 4) {
            goto end;
        }
        self[0xb5] += 2;
        // fall through to end
    }
end:
    return;
}

void func_ov096_0229c7e0(volatile unsigned char *self, int param, int b)
{
    if (func_ov002_022088ac(param)) {
        if (self[0xb5] > 0x19) {
            self[0xb5] = self[0xb5] - 1;
        }
    } else {
        if (func_ov002_0220889c(param)) {
            if (self[0xb5] < 0x20) {
                self[0xb5] = self[0xb5] + 1;
            }
        }
    }

    if (func_ov002_022088bc((void *) param)) {
        int d = self[0xb5] - 0x19;
        if (d == 7) {
            self[0xb5] = 0x10;
        } else if (d == 6) {
            self[0xb5] = 0x0f;
        } else if (d == 0) {
            self[0xb5] = 0x25;
        } else {
            self[0xb5] = 0x24;
        }

        func_ov002_0220a2b4((unsigned char *) (self + 0x2500));
    }
}

void func_ov096_0229c63c(unsigned char *self, void *param, int param2)
{
    unsigned char opcode = self[0xb5];

    if (opcode == 0x24) {
        if (func_ov002_022088ac((int) param)) {
            if (func_ov096_0229ee10(self, param2)) {
                self[0xb5] = 0x25;
            } else {
                func_ov096_0229c2ec((UnkStruct_0229c2ec *) self, 0x10);
                self[0xb5] = 0x10;
            }
        } else if (func_ov002_0220889c((int) param)) {
            self[0xb5] = 0x0f;
        } else if (func_ov002_022088cc(param)) {
            if (param2 == 0) {
                func_ov096_0229f7e0(self);
                func_ov002_0220a254(self + 0x2500);
            }
        } else if (func_ov002_022088bc(param)) {
            if (func_ov096_0229ee38(self, param2)) {
                self[0xb5] = 0x22;
            } else {
                self[0xb5] = 0x04;
            }
        }
    } else if ((unsigned char) (opcode + 0xde) <= 1) {
        if (func_ov002_022088ac((int) param)) {
            if (func_ov096_0229ee10(self, param2)) {
                self[0xb5] = 0x25;
            } else {
                func_ov096_0229c2ec((UnkStruct_0229c2ec *) self, 0x10);
                self[0xb5] = 0x12;
            }
        } else if (func_ov002_0220889c((int) param)) {
            self[0xb5] = 0x11;
        } else if (func_ov002_022088cc(param)) {
            if (func_ov096_0229ee50(self, param2)) {
                self[0xb5] = 0x24;
            }
        } else if (func_ov002_022088bc(param)) {
            self[0xb5] = 0x04;
        }
    } else if (opcode == 0x25) {
        if (func_ov002_022088ac((int) param)) {
            func_ov096_0229c2ec((UnkStruct_0229c2ec *) self, 0x10);
            self[0xb5] = 0x12;
        } else if (func_ov002_0220889c((int) param)) {
            if (func_ov096_0229ee38(self, param2)) {
                self[0xb5] = 0x22;
            } else {
                if (func_ov096_0229ee50(self, param2)) {
                    self[0xb5] = 0x24;
                } else {
                    self[0xb5] = 0x11;
                }
            }
        } else if (func_ov002_022088cc(param)) {
            if (param2 == 0) {
                func_ov096_0229f7e0(self);
                func_ov002_0220a254(self + 0x2500);
            }
        } else if (func_ov002_022088bc(param)) {
            self[0xb5] = 0x01;
        }
    }
}

int func_ov096_0229c560(UnkStruct_0229c560 *self, int param2, int param3)
{
    u8 old = self->byte;
    func_ov096_0229c2dc((Struct_ov096_0229c2dc *) self, 0x30);
    if (param2 == 0) {
        return 0;
    }

    if (func_ov096_0229f830((void *) self, self->byte)) {
        func_ov096_0229ca78((unsigned char *) self, (void *) param2, param3);
    } else if (func_ov096_0229f820((void *) self, self->byte)) {
        func_ov096_0229c888((unsigned char *) self, param2, param3);
    } else if (func_ov096_0229f810(self, self->byte)) {
        func_ov096_0229c7e0((volatile unsigned char *) self, param2, param3);
    } else if (func_ov096_0229f800(self, self->byte)) {
        func_ov096_0229c63c((unsigned char *) self, (void *) param2, param3);
    } else if (self->byte == 0x21) {
        if (func_ov002_0220889c(param2)) {
            self->byte = 0xa;
        } else if (func_ov002_022088ac(param2)) {
            self->byte = 0x18;
            func_ov096_0229c2ec((UnkStruct_0229c2ec *) self, 0x10);
        }
    }

    if (old == self->byte) {
        return 0;
    } else {
        return 1;
    }
}

void func_ov096_0229c538(int param1)
{
    func_ov002_02208090(param1, 5);
    func_ov002_022080a0((void *) (param1), 1);
    func_ov096_0229c2ec((UnkStruct_0229c2ec *) param1, 0x80);
    func_ov096_022a1540(param1);
}

void func_ov096_0229c514(void *self)
{
    func_ov002_02208098((void *) (self), 0x21);
    func_0208f0c4((char *) self + 0x2d9c, 2);
    func_0200467c(0x29);
}

void func_ov096_0229c4ec(int arg)
{
    func_ov096_0229c514((void *) arg);
    func_ov090_022993cc(func_020ee45c(arg), 7);
    func_ov096_0229c2ec((UnkStruct_0229c2ec *) arg, 0x00020000);
}

int func_ov096_0229c4dc(struct UnkStruct_0229c4dc *p)
{
    return func_ov096_0229f054(p, p->b6);
}

void func_ov096_0229c454(void *p)
{
    int r4;
    short s;
    int r6;
    unsigned int cond;
    int r2;

    r4 = func_ov096_0229c4dc((struct UnkStruct_0229c4dc *) p);
    s = func_ov096_0229f0dc(p, *(unsigned char *) ((char *) p + 0xB8));
    r6 = func_0204bd5c(&s);
    func_020665f0(r4, (unsigned char) r6);
    func_ov002_02208a24((char *) p + 0x2564, r4, *(unsigned char *) ((char *) p + 0xBE));
    func_0206fcb0(r4);
    func_ov096_022a18dc(p, 8);
    func_ov096_022a1540((int) p);
    cond = func_0204bd40(&s);
    if (cond <= 1) {
        r2 = 0xFFF1;
    } else {
        r2 = func_0204bd20(r6, cond - 1);
    }
    func_ov096_0229f5e0(p, *(unsigned char *) ((char *) p + 0xB8), r2, 0);
}

void func_ov096_0229c434(int param)
{
    func_ov096_0229c2ec((UnkStruct_0229c2ec *) param, 0x400);
    func_ov096_0229c2ec((UnkStruct_0229c2ec *) param, 0x800);
}

void func_ov096_0229c414(int a)
{
    func_ov096_0229c2dc((Struct_ov096_0229c2dc *) a, 0x400);
    func_ov096_0229c2ec((UnkStruct_0229c2ec *) a, 0x800);
}

void func_ov096_0229c3c4(int param)
{
    if (func_ov096_0229c2fc((Struct_ov096_0229c2fc *) param, 0x800) == 0) {
        return;
    }

    if (func_0203ac5c()) {
        if (func_ov096_0229c2fc((Struct_ov096_0229c2fc *) param, 0x400) == 0) {
            func_0203ac2c();
        }
    } else {
        if (func_ov096_0229c2fc((Struct_ov096_0229c2fc *) param, 0x400) != 0) {
            func_0203ac44();
        }
    }

    func_ov096_0229c2dc((Struct_ov096_0229c2dc *) param, 0x800);
}

void func_ov096_0229c348(UnkStruct_0229c348 *self)
{
    volatile u16 t[2];
    int ok;
    u16 lo;
    u16 hi;

    t[0] = *func_020993a8((unsigned int) func_020984e8());
    t[1] = self->unk_AC;
    func_0206f190(&t[1], (char *) self + 0x320, (char *) self + 0xe8, (char *) self + 0xc8);

    ok = 0;
    lo = t[0];
    hi = t[0];
    if (hi >= 0x11a8 && lo <= 0x12a7) {
        ok = 1;
    }

    if (ok != 0) {
        self->unk_AC = lo;
        func_ov096_0229e82c(self, 1);
    } else {
        func_ov096_0229e6a0(self);
    }
    func_0200467c(0x6b);
}

int func_ov096_0229c310(char *self)
{
    volatile long long unused;
    (void) &unused;
    if (*(unsigned char *) (self + 0xb1) == 2 && *(unsigned char *) (self + 0xb0) == 0 &&
        *(unsigned short *) (self + 0xac) >= 0x11a8 && *(unsigned short *) (self + 0xac) <= 0x12a7) {
        return 1;
    }
    return 0;
}

int func_ov096_0229c2fc(Struct_ov096_0229c2fc *p, unsigned int mask)
{
    if (p->flag & mask) {
        return 1;
    }
    return 0;
}

void func_ov096_0229c2ec(UnkStruct_0229c2ec *self, unsigned int bits)
{
    self->flags |= bits;
}

void func_ov096_0229c2dc(Struct_ov096_0229c2dc *s, unsigned int mask)
{
    s->unk_94 &= ~mask;
}

struct Big *func_ov096_0229c22c(struct Big *self)
{
    self->vtable = &data_ov096_022a23e8;
    func_02066688((char *) self + 0x2f28);
    func_02066688((char *) self + 0x2e28);
    func_ov002_0220b464((char *) self + 0x2d9c);
    func_0206e35c((char *) self + 0x2a74);
    func_ov002_0220ba0c((char *) self + 0x2958);
    func_ov002_02209ac8((char *) self + 0x2564);
    func_ov002_02209cb4((char *) self + 0x2500);
    func_ov002_02209e38((char *) self + 0x24e8);
    func_ov002_02207e28((char *) self + 0x2418);
    func_ov094_0229a2d0((char *) self + 0x0de0);
    func_ov094_0229bc30((char *) self + 0x0db8);
    func_ov094_0229afe0((char *) self + 0x0358);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov096_0229c180(void *self)
{
    *(int *) self = (int) ((char *) &data_ov096_022a23e8);
    func_02066688((char *) self + 0x2f28);
    func_02066688((char *) self + 0x2e28);
    func_ov002_0220b464((char *) self + 0x2d9c);
    func_0206e35c((char *) self + 0x2a74);
    func_ov002_0220ba0c((char *) self + 0x2958);
    func_ov002_02209ac8((char *) self + 0x2564);
    func_ov002_02209cb4((char *) self + 0x2500);
    func_ov002_02209e38((char *) self + 0x24e8);
    func_ov002_02207e28((char *) self + 0x2418);
    func_ov094_0229a2d0((char *) self + 0x0de0);
    func_ov128_0229bc30((char *) self + 0x0db8);
    func_ov094_0229afe0((char *) self + 0x0358);
    func_ov002_0220826c(self);
    return self;
}
