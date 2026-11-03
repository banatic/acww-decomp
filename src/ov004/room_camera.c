/* room_camera: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02246c7c @ 0x02246c7c, 0x78 bytes, Thumb
 * func_ov004_02246b6c @ 0x02246b6c, 0x110 bytes, Thumb
 * func_ov004_02246a84 @ 0x02246a84, 0xe8 bytes, Thumb
 * func_ov004_02246a74 @ 0x02246a74, 0x10 bytes, Thumb
 */

#define S32(o) (*(int *) ((char *) self + (o)))
#define S16(o) (*(short *) ((char *) self + (o)))
#define WORD(o) (*(int *) ((char *) self + (o)))
#define HALF(o) (*(short *) ((char *) self + (o)))

typedef struct UnkStruct_02246c7c {
    short unk_00;
    short unk_02;
    int w0, w1, w2, w3, w4, w5, w6;
} UnkStruct_02246c7c;

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    Vec pos;
    int pad_0C, pad_10, value, pad_18;
    short first, second;
    int pad_20;
} Entry;

typedef struct {
    short unk_00, unk_02, unk_04, previous[2], unk_0A, unk_0C;
    unsigned char unk_0E;
} State;

typedef struct {
    short a, b;
    int c, d, e, unk_10, g, h, i;
} Settings;

typedef struct {
    char pad_00[0xfc];
    Settings first;
    char pad_11C[0x2c];
    Settings second;
    char pad_168[0xb4];
    short state[3];
} Object;

extern void func_0203c97c(void *self, void *p);
extern void func_0203ad58(void);
extern unsigned char data_ov004_0225697c[];
extern unsigned char data_ov004_022569cc[];
extern int func_020644cc(int);
extern void VEC_Subtract(const void *, const void *, void *);
extern void func_0203ad68(void);
extern Settings data_ov004_022569ac;
extern Settings data_ov004_0225698c;
extern char data_ov004_0225695c[];
extern int func_ov004_022473a8(int arg);
extern int data_021c67a4;

void func_ov004_02246c7c(void *self)
{
    UnkStruct_02246c7c *g;

    g = (UnkStruct_02246c7c *) data_ov004_022569cc;
    S16(0xfc) = g->unk_00;
    S16(0xfe) = g->unk_02;
    S32(0x100) = g->w0;
    S32(0x104) = g->w1;
    S32(0x108) = g->w2;
    S32(0x10c) = g->w3;
    S32(0x110) = g->w4;
    S32(0x114) = g->w5;
    S32(0x118) = g->w6;
    func_0203c97c(self, (void *) data_ov004_0225697c);
    func_0203ad58();
}

Entry data_ov004_022569ec[];

void func_ov004_02246b6c(void *self)
{
    State *b = (State *) ((char *) self + 0x21c);
    int excluded[2];
    int i;
    Entry *entry;
    b->unk_00 = 0;
    if (func_020644cc(2) == 1) {
        b->unk_02 = func_020644cc(b->unk_0C - 2);
    } else {
        b->unk_02 = func_020644cc(b->unk_0C);
    }
    if (b->previous[0] > b->previous[1]) {
        excluded[0] = b->previous[1];
        excluded[1] = b->previous[0];
    } else {
        excluded[0] = b->previous[0];
        excluded[1] = b->previous[1];
    }
    for (i = 0; i < 2; ++i) {
        if (excluded[i] != -1 && (b->unk_02 >> 1) >= (excluded[i] >> 1)) {
            b->unk_02 += 2;
        }
    }
    if (b->previous[b->unk_0A] == -1) {
        b->unk_0C -= 2;
    }
    b->previous[b->unk_0A] = b->unk_02;
    b->unk_0A ^= 1;
    b->unk_04 = 1;
    entry = &data_ov004_022569ec[b->unk_02];
    WORD(0x110) = entry->pos.x;
    WORD(0x114) = entry->pos.y;
    WORD(0x118) = entry->pos.z;
    VEC_Subtract((char *) self + 0x110, (char *) self + 0x104, (char *) self + 0x110);
    HALF(0xfe) = entry->second;
    HALF(0xfc) = entry->first;
    WORD(0x100) = entry->value;
    func_0203ad68();
}

void func_ov004_02246a84(Object *self)
{
    short *s = self->state;
    s[0] = 0;
    s[1] = 0;
    s[2] = 2;
    self->first.a = data_ov004_022569ac.a;
    self->first.b = data_ov004_022569ac.b;
    self->first.c = data_ov004_022569ac.c;
    self->first.d = data_ov004_022569ac.d;
    self->first.e = data_ov004_022569ac.e;
    self->first.unk_10 = data_ov004_022569ac.unk_10;
    self->first.g = data_ov004_022569ac.g;
    self->first.h = data_ov004_022569ac.h;
    self->first.i = data_ov004_022569ac.i;
    self->second.a = data_ov004_0225698c.a;
    self->second.b = data_ov004_0225698c.b;
    self->second.c = data_ov004_0225698c.c;
    self->second.d = data_ov004_0225698c.d;
    self->second.e = data_ov004_0225698c.e;
    self->second.unk_10 = data_ov004_0225698c.unk_10;
    self->second.g = data_ov004_0225698c.g;
    self->second.h = data_ov004_0225698c.h;
    self->second.i = data_ov004_0225698c.i;
    func_0203c97c(self, data_ov004_0225695c);
    func_0203ad58();
}

int func_ov004_02246a74(void)
{
    return func_ov004_022473a8(data_021c67a4);
}
