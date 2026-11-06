/* missing_npc1: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c1b28 @ 0x020c1b28, 0x6 bytes, Thumb
 * func_020c1b20 @ 0x020c1b20, 0x6 bytes, Thumb
 * func_020c1ae4 @ 0x020c1ae4, 0x3c bytes, Thumb
 * func_020c1a34 @ 0x020c1a34, 0xb0 bytes, Thumb
 * func_020c19fc @ 0x020c19fc, 0x36 bytes, Thumb
 * func_020c19ec @ 0x020c19ec, 0xe bytes, Thumb
 * func_020c1904 @ 0x020c1904, 0xe8 bytes, Thumb
 * func_020c18c4 @ 0x020c18c4, 0x40 bytes, Thumb
 * func_020c189c @ 0x020c189c, 0x28 bytes, Thumb
 * func_020c1874 @ 0x020c1874, 0x28 bytes, Thumb
 * func_020c1848 @ 0x020c1848, 0x2c bytes, Thumb
 * func_020c1820 @ 0x020c1820, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[180];
    unsigned long unk_B4;
} UnkStruct_020c1b28;

typedef struct {
    unsigned char pad_00[180];
    unsigned long unk_B4;
} UnkStruct_020c1b20;

struct UnkStruct_020c1a34 {
    u8 pad_00[0xb0];
    u8 *data;
};

struct UnkStruct_020c1a34_2 {
    u32 a;
    u8 b;
};

struct UnkStruct_020c19ec {
    char pad_00[0x14];
    int value;
};

struct UnkStruct_020c19ec_2 {
    char pad_00[0x1e];
    unsigned char flag;
    char pad_1F[0x21];
    struct UnkStruct_020c19ec *inner;
};

typedef struct {
    char pad_00[0x1e];
    unsigned char state;
    char pad_1F[0x40 - 0x1f];
    int something;
    char pad_44[0xb0 - 0x44];
    unsigned char *unk_B0;
} UnkStruct_020c1904;

typedef struct GStruct GStruct;

struct GStruct {
    char pad_00[0x2ac];
    unsigned char unk_2AC;
    char pad_2AD[0x3a7];
    int unk_654;
};

struct UnkStruct_020c189c {
    char pad_00[0x654];
    void *unk_654;
};

struct System {
    char pad_00[0x654];
    int unk_654;
};

typedef struct {
    void *unk_00;
    char pad_04[0x654];
    char sub;
} UnkStruct_020c1820;

extern void func_0201b38c(int, int);
extern void func_0201b388(int, int);
extern int func_02016014(void *, void *);
extern u32 data_020e7ad8;
extern u32 func_020984e8(void);
extern void func_02098ff8(u32 a, u32 b);
extern u32 func_020644cc(u32 a);
extern int func_0202ea80(u32 a, u32 b);
extern void *func_02099688(void *);
extern int func_020882ec(void *);
extern int func_02015e70(void *, int, int);
extern int func_0206837c(int);
extern int func_020ab504(int);
extern void func_0206844c(int, char *, int);
extern int func_0208602c(void);
extern int func_020860c4(int);
extern void func_02087f28(void *);
extern void func_02087f20(void *);
extern int func_020b65c4(void);
extern GStruct *data_021fbbe0;
extern int func_0201a3e4(void *p);
extern void func_020c26b4(struct UnkStruct_020c189c *p, int arg);
extern void *func_020c1b6c(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);
extern char data_020e7c60[];

void func_020c1b28(UnkStruct_020c1b28 *p, unsigned long v)
{
    p->unk_B4 = v;
}

unsigned long func_020c1b20(UnkStruct_020c1b20 *p)
{
    return p->unk_B4;
}

void func_020c1ae4(void *self, void *arg)
{
    int *p = (int *) ((char *) self + 0xb0);
    func_0201b38c(*p + 0x2a0, 0);
    func_0201b388(*p + 0x2a0, 1);
    func_02016014(self, arg);
}

void func_020c1a34(struct UnkStruct_020c1a34 *self, struct UnkStruct_020c1a34_2 *out)
{
    u32 r;
    u32 idx;

    r = func_020984e8();
    out->a = data_020e7ad8;
    idx = (u32) func_020c1b20((UnkStruct_020c1b20 *) self);

    switch (idx) {
        case 0:
            func_02098ff8(r, 0x33);
            out->b = 0;
            break;
        case 1:
            func_02098ff8(r, 0x33);
            out->b = func_020644cc(3) + 1;
            break;
        case 2:
            out->b = func_020644cc(3) + 4;
            func_0202ea80(0x29, 1);
            break;
        case 3:
            out->b = func_020644cc(3) + 7;
            break;
        case 4:
            out->b = func_020644cc(3) + 0x19;
            break;
        case 5:
            out->b = func_020644cc(3) + 0x22;
            break;
        case 6:
            out->b = 0x14;
            break;
    }

    self->data[0x711] = 0;
}

int func_020c19fc(void *param)
{
    void *a = func_02099688((void *) func_020984e8());
    func_02015e70(param, func_020882ec(a), 0);
    return func_02015e70(param, func_020882ec(a), 1);
}

void func_020c19ec(struct UnkStruct_020c19ec_2 *arg0)
{
    if (arg0->flag == 0x14) {
        arg0->inner->value = 0;
    }
}

void func_020c1904(UnkStruct_020c1904 *self)
{
    char arr[2];
    int r;
    switch (self->state) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 25:
        case 26:
        case 27:
        case 34:
        case 35:
        case 36:
            r = func_020ab504(func_0206837c(self->something));
            switch (r) {
                case 0:
                    arr[0] = (char) ((int) func_020644cc(3) + 0x1c);
                    func_0206844c(self->something, arr, (*(int *) &data_020e7ad8));
                    func_02087f28((void *) func_020860c4((int) func_0208602c()));
                    break;
                case 1:
                    arr[1] = (char) ((int) func_020644cc(3) + 0x1f);
                    func_0206844c(self->something, &arr[1], (*(int *) &data_020e7ad8));
                    if (func_020b65c4() == 0) {
                        func_02087f20((void *) func_020860c4((int) func_0208602c()));
                    }
                    self->unk_B0[0x711] = 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

int func_020c18c4(void)
{
    if (data_021fbbe0 != 0) {
        if (func_0201a3e4(&data_021fbbe0->unk_2AC) == 0xba && data_021fbbe0->unk_654 == 0) {
            return 1;
        }
        return 0;
    }
    return 1;
}

void func_020c189c(void)
{
    struct UnkStruct_020c189c *p;
    p = (*(struct UnkStruct_020c189c **) &data_021fbbe0);
    if (p != 0) {
        if (p->unk_654 != 0) {
            func_020c26b4(p, 0);
        }
    }
}

void func_020c1874(void)
{
    if ((*(struct System **) &data_021fbbe0) != 0 && (*(struct System **) &data_021fbbe0)->unk_654 != 5) {
        func_020c26b4((struct UnkStruct_020c189c *) ((*(struct System **) &data_021fbbe0)), 5);
    }
}

void *func_020c1848(void *s)
{
    *(void **) s = &data_020e7c60;
    func_020c1b6c((char *) s + 0x658);
    func_0202ee5c(s);
    func_020edf54(s);
    return s;
}

void *func_020c1820(UnkStruct_020c1820 *param)
{
    param->unk_00 = ((char *) data_020e7c60);
    func_020c1b6c(&param->sub);
    func_0202ee5c(param);
    return param;
}
