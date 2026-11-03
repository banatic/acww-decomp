/* speaker_anim: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020164cc @ 0x020164cc, 0x20 bytes, Thumb
 * func_020164a0 @ 0x020164a0, 0x2c bytes, Thumb
 * func_02016448 @ 0x02016448, 0x58 bytes, Thumb
 * func_0201643c @ 0x0201643c, 0xa bytes, Thumb
 * func_02016430 @ 0x02016430, 0xa bytes, Thumb
 * func_02016384 @ 0x02016384, 0xac bytes, Thumb
 * func_0201637c @ 0x0201637c, 0x8 bytes, Thumb
 * func_020161e4 @ 0x020161e4, 0x198 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02016448 {
    char pad_00[8];
    int unk_08;
    char pad1[8];
    int unk_14;
};

struct Other {
    char pad_00[0x98];
    int unk_98;
    char pad1[0x18c - 0x98 - 4];
    int unk_18C;
    char pad_190[0x198 - 0x18c - 4];
    int unk_198;
};

typedef struct {
    u8 pad_00[0xc];
    int c;     // 0xc
    u8 flag10; // 0x10
    u8 pad_11[0x7];
    u8 flag18; // 0x18
} UnkStruct_02016384;

extern int func_02056f94(int);
extern int func_02082fec(int, int);
extern int func_0205cb80(int);
extern void *func_0201af24(void *);
extern int FX_MulFunc(int, int);
extern int func_02016618(void *self);
extern int func_0201a7b4(void *ptr);
extern int func_0201a7bc(void *ptr);
extern int func_02054230(void *ptr);
extern int func_0201a798(void);
extern void func_02016530(void *self, void *arg, unsigned int a, unsigned int b);
extern void func_02016520(void *self, void *arg);
extern void func_02083068(void *);
extern void func_0201a7b8(void *p, int r);

int func_020164cc(int a, int b)
{
    return func_02056f94(b + 0x188) ? 1 : 0;
}

int func_020164a0(int r0, int r1)
{
    int r5;
    int r4;
    int result;

    r5 = r0;
    r4 = r1;
    result = func_02082fec(r5, r4);
    if (result != 0) {
        return func_0205cb80(func_02082fec(r5, r4));
    }
    return 0x144;
}

void func_02016448(struct UnkStruct_02016448 *self, struct Other *other)
{
    int *p = &other->unk_98;
    int f = *p;
    if (f == 0) {
        self->unk_08 = 0x1000;
    } else {
        if (*(int *) func_0201af24((char *) other + 0x350) == 0) {
            self->unk_08 = 0x1000;
        } else {
            self->unk_08 = FX_MulFunc(f, self->unk_14);
        }
    }
    if (self->unk_08 <= other->unk_18C) {
        other->unk_198 = self->unk_08;
    }
}

int func_0201643c(int a, int b)
{
    int r = 0;
    if (b == 1) {
        r = 6;
    }
    return r;
}

int func_02016430(int a, int b)
{
    int r = 7;
    if (b == 1) {
        r = 0xc;
    }
    return r;
}

void func_02016384(UnkStruct_02016384 *self, void *arg)
{
    if (func_02016618(self) == 0) {
        goto out;
    }

    if (func_0201a7b4((char *) arg + 0x418) >= 2) {
        goto L_206;
    }

    if (func_0201a7bc((char *) arg + 0x418) == 0) {
        goto L_3e6;
    }

    if (self->flag10 != 0) {
        if (func_02054230((char *) arg + 0xec) == 0) {
            goto out;
        }
    }

    self->c = func_0201a798();
    {
        unsigned int v1 = (unsigned int) func_0201643c((int) self, self->c);
        unsigned int v2 = (unsigned int) func_02016430((int) self, self->c);
        func_02016530(self, arg, v1, v2);
    }
    self->flag10 = 1;
    goto out;

L_3e6:
    if (self->flag10 == 1) {
        if (func_02054230((char *) arg + 0xec) != 0) {
            func_02016520(self, arg);
            self->flag10 = 0;
        }
    }
    goto out;

L_206:
    if (self->flag10 == 1) {
        func_02016520(self, arg);
        self->flag10 = 0;
    }

out:
    if (self->flag18 == 0) {
        func_02016448((struct UnkStruct_02016448 *) self, (struct Other *) arg);
    }
}

void func_0201637c(void *argument0)
{
    func_02083068((void *) argument0);
}

void func_020161e4(void *a, char *b)
{
    int v, r;

    v = func_020164a0((int) a, 0);
    r = 0;
    switch (v) {
        case 0x45:
        case 0x47:
        case 0x49:
        case 0x4b:
        case 0x4d:
        case 0x4f:
        case 0x51:
        case 0x53:
        case 0x55:
        case 0x57:
        case 0x59:
        case 0x5b:
        case 0x5d:
        case 0x5f:
        case 0x61:
        case 0x63:
        case 0x65:
        case 0x67:
        case 0x69:
        case 0x6e:
        case 0x70:
        case 0x72:
        case 0x75:
        case 0x77:
        case 0x79:
        case 0x7b:
        case 0x7c:
        case 0x7f:
        case 0x80:
        case 0x81:
        case 0x84:
        case 0x86:
        case 0x88:
        case 0x8a:
        case 0x8c:
        case 0x8d:
        case 0x8f:
        case 0x91:
        case 0x93:
        case 0x94:
        case 0x97:
        case 0x98:
        case 0x99:
        case 0x9c:
        case 0x9f:
        case 0xa1:
        case 0xa3:
        case 0xa5:
        case 0xa7:
        case 0x144:
            r = 2;
            break;
        case 0x46:
        case 0x48:
        case 0x4c:
        case 0x4e:
        case 0x50:
        case 0x52:
        case 0x54:
        case 0x56:
        case 0x5a:
        case 0x60:
        case 0x62:
        case 0x64:
        case 0x68:
        case 0x6c:
        case 0x6d:
        case 0x71:
        case 0x76:
        case 0x78:
        case 0x83:
        case 0x85:
        case 0x87:
        case 0x8b:
        case 0x96:
        case 0x9b:
        case 0x9d:
        case 0x9e:
        case 0xa0:
        case 0xa2:
        case 0xa4:
        case 0xa8:
        case 0xe6:
        case 0xea:
            r = 1;
            break;
    }
    func_0201a7b8(b + 0x418, r);
}
