/* camera_grid_2: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208c630 @ 0x0208c630, 0x6 bytes, Thumb
 * func_0208c620 @ 0x0208c620, 0x10 bytes, Thumb
 * func_0208c610 @ 0x0208c610, 0x10 bytes, Thumb
 * func_0208c5f0 @ 0x0208c5f0, 0x20 bytes, Thumb
 * func_0208c5bc @ 0x0208c5bc, 0x32 bytes, Thumb
 * func_0208c56c @ 0x0208c56c, 0x50 bytes, Thumb
 * func_0208c490 @ 0x0208c490, 0xdc bytes, Thumb
 * func_0208c42c @ 0x0208c42c, 0x64 bytes, Thumb
 * func_0208c3ec @ 0x0208c3ec, 0x40 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[212];
    unsigned char unk_D4;
} UnkStruct_0208c630;

struct UnkStruct_0208c490 {
    char pad_00[0xc8];
    int c8;
    int cc;
};

struct Flags {
    char pad_00[2];
    unsigned short flags;
};

struct UnkStruct_0208c42c {
    u8 pad_00[0xc4];
    u32 c4;
    u8 pad_C8[8];
    u32 d0;
};

struct UnkStruct_0208c3ec {
    char pad_00[0xC4];
    int unk_C4;
    int unk_C8;
    int unk_CC;
};

extern int func_020a7e50(void);
extern int func_020a7ffc(void);
extern int func_020a7e44(void);
extern int func_020a812c(void);
extern unsigned char data_020d0a70[];
extern int func_020a80c4(int a, int b, int c, int d);
extern void func_0208c3c0(void *);
extern struct Flags data_021fbe40;
extern unsigned char data_020d0a99[];
extern unsigned char data_020d0a98[];
extern signed char data_020d0a85[];
extern int func_0203aad0(int, int);
extern void func_0200467c(int);
extern const struct Pair {
    signed char lo;
    signed char hi;
} data_020d0a84[9];

void func_0208c3ec(struct UnkStruct_0208c3ec *s);

void func_0208c630(UnkStruct_0208c630 *p, unsigned char v)
{
    p->unk_D4 = v;
}

int func_0208c620(void *arg)
{
    if (*(int *) ((char *) arg + 0xc0) == 0) {
        return 1;
    }
    return 0;
}

int func_0208c610(void *param)
{
    if (*(unsigned int *) ((char *) param + 0xc0) == 2) {
        return 1;
    }
    return 0;
}

int func_0208c5f0(int *param)
{
    int r0;
    int r1;
    int r2;

    r0 = (int) param + 0xc0;
    r1 = *(int *) r0;
    if (r1 == 2) {
        r2 = 1;
    } else {
        r2 = 0;
    }
    r0 = 0;
    if (r1 == 0) {
        r0 = 1;
    } else if (r2 != 0) {
        r0 = 1;
    }
    return r0;
}

int func_0208c5bc(void)
{
    int r4 = 0;
    int r0;

    if (func_020a7e50() != 0) {
        if (func_020a7ffc() != 0) {
            r4 = 1;
        }
    } else {
        if (func_020a7e44() != 0) {
            if (func_020a812c() != 0) {
                r4 = 1;
            }
        }
    }
    return r4;
}

int func_0208c56c(void *arg)
{
    int i;
    int found = 0;
    for (i = 0; i < 9; i++) {
        unsigned char b0 = data_020d0a70[i * 2];
        const unsigned char *p = &data_020d0a70[i * 2];
        unsigned char b1 = p[1];
        int a = b0 + 0x80;
        int c = b1 + 0x60;
        if (func_020a80c4(a, a + 0x10, c, c + 0x10) != 0) {
            found = 1;
            *(int *) ((char *) arg + 0xc4) = i;
            func_0208c3c0(arg);
            break;
        }
    }
    return found;
}

int func_0208c490(struct UnkStruct_0208c490 *self)
{
    int old_c8 = self->c8;
    int old_cc = self->cc;
    unsigned short flags = data_021fbe40.flags;

    if (flags & 0x10) {
        self->c8 += 1;
    } else if (flags & 0x20) {
        self->c8 -= 1;
    } else if (flags & 0x40) {
        self->cc -= 1;
    } else if (flags & 0x80) {
        self->cc += 1;
    }

    {
        int c8 = self->c8;
        if (c8 < -1) {
            c8 = -1;
        } else if (c8 > 1) {
            c8 = 1;
        }
        self->c8 = c8;
    }

    {
        int cc = self->cc;
        if (cc < -1) {
            cc = -1;
        } else if (cc > 1) {
            cc = 1;
        }
        self->cc = cc;
    }

    func_0208c3ec((struct UnkStruct_0208c3ec *) self);

    if (old_c8 != self->c8 || old_cc != self->cc) {
        return 1;
    }
    return 0;
}

void func_0208c42c(struct UnkStruct_0208c42c *self)
{
    int off = self->c4 * 2;
    func_0203aad0(data_020d0a99[off], data_020d0a98[off]);
    if (self->c4 != self->d0) {
        int a = data_020d0a85[self->c4 * 2];
        int b = data_020d0a85[self->d0 * 2];
        int cmd;
        if (a < b) {
            cmd = 0x4d;
        } else if (a > b) {
            cmd = 0x4c;
        } else {
            cmd = 0x4e;
        }
        func_0200467c(cmd);
        self->d0 = self->c4;
    }
}

void func_0208c3ec(struct UnkStruct_0208c3ec *s)
{
    int i;
    for (i = 0; i < 9; i++) {
        if (s->unk_C8 == data_020d0a84[i].lo && s->unk_CC == data_020d0a84[i].hi) {
            break;
        }
    }
    s->unk_C4 = i;
}
