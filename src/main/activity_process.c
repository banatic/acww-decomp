/* activity_process: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a4d84 @ 0x020a4d84, 0x40 bytes, Thumb
 * func_020a4c9c @ 0x020a4c9c, 0xe8 bytes, Thumb
 * func_020a4c5c @ 0x020a4c5c, 0x40 bytes, Thumb
 * func_020a4b74 @ 0x020a4b74, 0xe8 bytes, Thumb
 * func_020a4b54 @ 0x020a4b54, 0x20 bytes, Thumb
 * func_020a4aa8 @ 0x020a4aa8, 0xac bytes, Thumb
 * func_020a4aa0 @ 0x020a4aa0, 0x8 bytes, Thumb
 * func_020a49bc @ 0x020a49bc, 0xe4 bytes, Thumb
 * func_020a49a0 @ 0x020a49a0, 0x1c bytes, Thumb
 * func_020a48cc @ 0x020a48cc, 0xd2 bytes, Thumb
 */

#include "types.h"

typedef struct SomeObj {
    u8 pad_00[0x64];
    u32 unk_64;
} SomeObj;

typedef struct UnkStruct_020a4c9c {
    u8 pad_00[0xA1];
    u8 mode;
    u8 pad_A2[0x6C];
    struct {
        u8 lo : 4;
        u8 hi : 4;
    } flags;
} UnkStruct_020a4c9c;

typedef struct UnkStruct_020a4b74 {
    u8 pad_00[0xA1];
    u8 mode;
    u8 pad_A2[0x6C];
    struct {
        u8 lo : 4;
        u8 hi : 4;
    } flags;
} UnkStruct_020a4b74;

typedef struct {
    unsigned char pad_00[0xa1];
    unsigned char state;
    unsigned char pad_A2[0x10e - 0xa1 - 1];
    union {
        struct {
            unsigned char low : 4;
            unsigned char high : 4;
        } bits;
        unsigned char byte;
    } flags;
} Func_020a49bc_Struct;

typedef struct {
    unsigned char pad_00[0xa1];
    unsigned char state;
} StateStruct;

extern void *func_020984e8(void);
extern void func_0206f74c(void);
extern void func_02098fd0(void *, int);
extern void func_0204cdc8(void *);
extern int data_020e3c40;
extern int data_021f39fc;
extern int func_020a259c(void *, int);
extern int func_02073dd4(void *, unsigned int);
extern void func_0207428c(void);
extern int func_0209ffb0(void *receiver);
extern int func_020a0174(void);
extern int func_020a238c(void *);
extern int func_020a2120(void *, int);
extern void func_020a261c(void *object);
extern void func_020a25cc(void *receiver);
extern void func_020a4e94(void *, int);
extern SomeObj *data_020ccf94;
extern int data_020e3c2c;
extern int func_020a1954(void *dst, const void *src, unsigned int size);
extern void func_0203d394(void);
extern unsigned char data_020e3c54[];
extern int data_021e5a2c;
extern int data_021dc7a8;
extern void func_0209dfc0(void);
extern void func_0207bddc(int *p, int);
extern void func_0209e6ec(int *p, int);
extern void func_02042458(void);
extern void func_0209e604(int *p);
extern int func_02042324(void);
extern int func_020422f8(void);
extern int func_020a1628(void);
extern int func_020a1cec(StateStruct *self, int a);

void func_020a4d84(char *self)
{
    void *r = func_020984e8();
    func_020a1954((void *) self, (const void *) (&data_020e3c40), 1);
    func_0206f74c();
    func_02098fd0(r, 2);
    func_0204cdc8(&data_021f39fc);
    self[0xa1] = 0;
}

void func_020a4c9c(UnkStruct_020a4c9c *self)
{
    switch (self->mode) {
        case 0: {
            SomeObj *p;
            if (func_020a259c(self, 0) != 0) {
                p = data_020ccf94;
                if (func_02073dd4(p, p->unk_64) != 0) {
                    func_0207428c();
                    if (func_0209ffb0(self) != 0) {
                        func_020a0174();
                    }
                }
                self->mode = 1;
            }
            break;
        }

        case 1: {
            int r;
            r = func_020a238c(self);
            if (r == 1) {
                self->mode = 4;
            } else if (r == 3) {
            } else {
                self->mode = 2;
            }
            break;
        }

        case 2: {
            int r;
            r = func_020a2120(self, self->flags.hi);
            if (r == 1) {
                self->mode = 4;
            } else if (r == 0) {
                self->mode = 3;
            }
            break;
        }

        case 3: {
            int r;
            r = func_020a2120(self, self->flags.lo);
            if (r == 1) {
                self->mode = 4;
            } else if (r == 0) {
                self->mode = 6;
            }
            break;
        }

        case 4:
            func_020a261c(self);
            self->mode = 5;
            break;

        case 5:
            break;

        default:
            func_020a25cc(self);
            func_020a4e94(self, 0xc);
            break;
    }
}

void func_020a4c5c(void *p)
{
    int v;
    v = (int) func_020984e8();
    func_020a1954(p, (const void *) (&data_020e3c2c), 0x66);
    func_0206f74c();
    func_02098fd0((void *) v, 2);
    func_0204cdc8((void *) (&data_021f39fc));
    *((char *) p + 0xa1) = 0;
}

void func_020a4b74(UnkStruct_020a4b74 *self)
{
    switch (self->mode) {
        case 0: {
            SomeObj *p;
            if (func_020a259c(self, 0) != 0) {
                p = data_020ccf94;
                if (func_02073dd4(p, p->unk_64) != 0) {
                    func_0207428c();
                    if (func_0209ffb0(self) != 0) {
                        func_020a0174();
                    }
                }
                self->mode = 1;
            }
            break;
        }

        case 1: {
            int r;
            r = func_020a238c(self);
            if (r == 1) {
                self->mode = 4;
            } else if (r == 3) {
            } else {
                self->mode = 2;
            }
            break;
        }

        case 2: {
            int r;
            r = func_020a2120(self, self->flags.hi);
            if (r == 1) {
                self->mode = 4;
            } else if (r == 0) {
                self->mode = 3;
            }
            break;
        }

        case 3: {
            int r;
            r = func_020a2120(self, self->flags.lo);
            if (r == 1) {
                self->mode = 4;
            } else if (r == 0) {
                self->mode = 6;
            }
            break;
        }

        case 4:
            func_020a261c(self);
            self->mode = 5;
            break;

        case 5:
            break;

        default:
            func_020a25cc(self);
            func_020a4e94(self, 0xd);
            break;
    }
}

void func_020a4b54(void *param)
{
    unsigned char *p;

    func_020a1954(param, (const void *) data_020e3c54, 0x28);
    func_0203d394();
    p = (unsigned char *) param + 0xa1;
    *p = 0;
}

void func_020a4aa8(unsigned char *self)
{
    switch (self[0xa1]) {
        case 0:
            if (func_020a259c((void *) self, 0) == 0) {
                break;
            }
            func_0209dfc0();
            self[0xa1]++;
            break;
        case 1:
            func_0207bddc(&data_021e5a2c, 0);
            self[0xa1]++;
            break;
        case 2:
            func_0209e6ec(&data_021dc7a8, 2);
            self[0xa1]++;
            break;
        case 3:
            func_02042458();
            self[0xa1]++;
            break;
        case 4:
            func_0209e604(&data_021dc7a8);
            self[0xa1]++;
            break;
        default:
            func_020a4e94((void *) self, 4);
            break;
    }
}

void func_020a4aa0(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (161))) + (0)) = 0;
}

void func_020a49bc(Func_020a49bc_Struct *self)
{
    switch (self->state) {
        case 0:
            self->state = 1;
            break;
        case 1:
            if (func_02042324()) {
                self->state = 2;
            } else {
                self->state = 3;
            }
            break;
        case 2:
            if (func_020422f8()) {
                self->state = 3;
            }
            break;
        case 3: {
            int r = func_020a238c(self);
            if (r == 1) {
                self->state = 6;
            } else if (r != 3) {
                self->state = 4;
            }
            break;
        }
        case 4: {
            int r = func_020a2120((void *) self, self->flags.bits.high);
            if (r == 1) {
                self->state = 6;
            } else if (r == 0) {
                self->state = 5;
            }
            break;
        }
        case 5: {
            int r = func_020a2120((void *) self, self->flags.bits.low);
            if (r == 1) {
                self->state = 6;
            } else if (r == 0) {
                self->state = 8;
            }
            break;
        }
        case 6:
            func_020a261c(self);
            self->state = 7;
            break;
        case 7:
            break;
        default:
            func_020a25cc(self);
            func_020a4e94((void *) self, 0x10);
            break;
    }
}

void func_020a49a0(unsigned char *param0)
{
    unsigned char *p;

    func_020a1954(param0, data_020e3c54, 12);
    p = param0 + 0xa1;
    *p = 0;
}

void func_020a48cc(StateStruct *self)
{
    switch (self->state) {
        case 0:
            if (func_020a259c((void *) self, 0) != 0) {
                self->state = 1;
            }
            break;
        case 1: {
            int r = func_020a1628();
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 2;
            }
            break;
        }
        case 2: {
            int r = func_020a1cec(self, 0);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 3;
            }
            break;
        }
        case 3: {
            int r = func_020a1cec(self, 1);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 4;
            }
            break;
        }
        case 4: {
            int r = func_020a1cec(self, 2);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 7;
            }
            break;
        }
        case 5:
            func_020a261c(self);
            self->state = 6;
            break;
        default:
            func_020a25cc(self);
            func_020a4e94((void *) self, 0xc);
            break;
        case 6:
            break;
    }
}
