/* taxi_driver_talk: 9 functions, module ov051
 * mwccarm 1.2/base -O4,s
 * func_ov051_022608b4 @ 0x022608b4, 0x74 bytes, Thumb
 * func_ov051_02260828 @ 0x02260828, 0x8c bytes, Thumb
 * func_ov051_0226079c @ 0x0226079c, 0x8c bytes, Thumb
 * func_ov051_0226076c @ 0x0226076c, 0x30 bytes, Thumb
 * func_ov051_0226072c @ 0x0226072c, 0x40 bytes, Thumb
 * func_ov051_022606c8 @ 0x022606c8, 0x64 bytes, Thumb
 * func_ov051_02260680 @ 0x02260680, 0x48 bytes, Thumb
 * func_ov051_02260608 @ 0x02260608, 0x78 bytes, Thumb
 * func_ov051_022605e8 @ 0x022605e8, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_022608b4 {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_022608b4;

struct UnkStruct_02260828 {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
};

struct UnkStruct_0226079c {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
};

struct func_ov051_0226076c_A;

struct func_ov051_0226076c_A {
    char pad_00[0x40];
    void *unk_40;
};

struct UnkStruct_0226072c {
    char pad_00[0x40];
    unsigned int unk_40;
};

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
    unsigned char pad_44[0xb0 - 0x44];
    int *unk_B0;
} UnkStruct_022606c8;

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
    unsigned char pad_44[0xb0 - 0x44];
    int *unk_B0;
} UnkStruct_02260680;

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
    unsigned char pad_44[0x6c];
    int *unk_B0;
} UnkStruct_02260608;

extern int func_020a12ac(void);
extern int data_ov051_022615c0;
extern int func_020984e8(void);
extern int func_02099870(int argument0);
extern void func_020950c8(int, int);
extern int func_020a12c0(void);
extern void func_0206844c(unsigned int, unsigned char *, int);
extern void func_0209c5a4(void *);
extern unsigned char data_ov051_022614c8[];
extern unsigned char data_ov051_022614c4[];
extern int func_020950c0(void *argument0);
extern unsigned char data_ov051_022614c0[];
extern int func_020a12d4(void);
extern unsigned char data_ov051_022614bc[];

unsigned char func_ov051_022605e8(int a, int b);

void func_ov051_022608b4(UnkStruct_022608b4 *self, int mode)
{
    u8 a;
    u8 b;
    u8 c;

    switch (mode) {
        case 0:
            if (func_020a12ac() != 0) {
                a = (u8) func_ov051_022605e8((int) self, 0x15);
                func_0206844c(self->unk_40, (unsigned char *) (&a), data_ov051_022615c0);
            } else {
                b = (u8) func_ov051_022605e8((int) self, 0x19);
                func_0206844c(self->unk_40, (unsigned char *) (&b), data_ov051_022615c0);
            }
            break;
        case 1:
            c = (u8) func_ov051_022605e8((int) self, 0x13);
            func_0206844c(self->unk_40, (unsigned char *) (&c), data_ov051_022615c0);
            break;
    }
}

void func_ov051_02260828(struct UnkStruct_02260828 *self, int which)
{
    unsigned char buf[3];

    switch (which) {
        case 0:

            func_020950c8(func_02099870((int) func_020984e8()), 0);
            if (func_020a12c0()) {
                buf[0] = func_ov051_022605e8((int) self, 0x19);
                func_0206844c(self->unk_40, buf, data_ov051_022615c0);
            } else {
                buf[1] = func_ov051_022605e8((int) self, 0xf);
                func_0206844c(self->unk_40, &buf[1], data_ov051_022615c0);
            }
            break;
        case 1:

            func_020950c8(func_02099870((int) func_020984e8()), 1);
            buf[2] = 0xe;
            func_0206844c(self->unk_40, &buf[2], data_ov051_022615c0);
            break;
        default:
            break;
    }
}

void func_ov051_0226079c(struct UnkStruct_0226079c *self, int which)
{
    unsigned char buf[3];

    switch (which) {
        case 0:

            func_020950c8(func_02099870((int) func_020984e8()), 1);
            if (func_020a12c0()) {
                buf[0] = func_ov051_022605e8((int) self, 0x19);
                func_0206844c(self->unk_40, buf, data_ov051_022615c0);
            } else {
                buf[1] = func_ov051_022605e8((int) self, 0xf);
                func_0206844c(self->unk_40, &buf[1], data_ov051_022615c0);
            }
            break;
        case 1:

            func_020950c8(func_02099870((int) func_020984e8()), 0);
            buf[2] = 0xd;
            func_0206844c(self->unk_40, &buf[2], data_ov051_022615c0);
            break;
        default:
            break;
    }
}

void func_ov051_0226076c(struct func_ov051_0226076c_A *a, void *b)
{
    unsigned char byte;
    byte = func_ov051_022605e8((int) a, 0x17);
    func_0206844c((unsigned int) a->unk_40, (unsigned char *) (&byte), (int) ((*(void **) &data_ov051_022615c0)));
    func_0209c5a4(b);
}

void func_ov051_0226072c(struct UnkStruct_0226072c *ptr, int val)
{
    char buf[2];
    switch (val) {
        case 0:
            buf[0] = 0x31;
            func_0206844c(ptr->unk_40, (unsigned char *) buf, (int) ((*(void **) &data_ov051_022615c0)));
            break;
        case 1:
            buf[1] = 0x32;
            func_0206844c(ptr->unk_40, (unsigned char *) (&buf[1]), (int) ((*(void **) &data_ov051_022615c0)));
            break;
    }
}

void func_ov051_022606c8(UnkStruct_022606c8 *p, int p1)
{
    unsigned char ch;
    int result;

    if (func_020a12ac() != 0) {

        result = *(unsigned char *) (data_ov051_022614c8 + 2 * p1 + func_020950c0((void *) func_02099870(func_020984e8())));
    } else {
        result = data_ov051_022614c4[p1];
    }
    ch = (unsigned char) result;
    func_0206844c(p->unk_40, &ch, data_ov051_022615c0);

    if (p1 == 1) {
        *(int *) ((char *) p->unk_B0 + 0x714) += 4;
    }
}

void func_ov051_02260680(UnkStruct_02260680 *param1, int param2)
{
    unsigned char ch;

    ch = (unsigned char) func_ov051_022605e8((int) param1, (unsigned char) data_ov051_022614c0[param2]);
    func_0206844c(param1->unk_40, &ch, data_ov051_022615c0);

    if (param2 == 1) {
        *(int *) ((char *) param1->unk_B0 + 0x714) += 2;
    }
}

void func_ov051_02260608(UnkStruct_02260608 *self, int idx)
{
    char local;
    int result;

    if (func_020a12d4()) {
        result = (int) func_ov051_022605e8((int) self, (unsigned char) data_ov051_022614bc[idx]);
    } else if (idx == 0) {

        if (func_020950c0((void *) func_02099870(func_020984e8())) == 0) {
            result = 0x21;
        } else {
            result = 0x2f;
        }
    } else {
        result = (int) func_ov051_022605e8((int) self, (unsigned char) 0x23);
    }

    local = (char) result;
    func_0206844c(self->unk_40, (unsigned char *) (&local), data_ov051_022615c0);

    if (idx == 1) {
        int *ptr = self->unk_B0;
        (*(int *) ((char *) ptr + 0x714))++;
    }
}

unsigned char func_ov051_022605e8(int a, int b)
{
    int t;
    t = func_020984e8();
    t = func_02099870(t);
    t = func_020950c0((void *) t);
    return (unsigned char) (b + (unsigned char) t);
}
