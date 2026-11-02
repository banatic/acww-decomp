/* soft_keyboard_places: 8 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_0229ae5c @ 0x0229ae5c, 0x28 bytes, Thumb
 * func_ov095_0229adc4 @ 0x0229adc4, 0x98 bytes, Thumb
 * func_ov095_0229ad90 @ 0x0229ad90, 0x34 bytes, Thumb
 * func_ov095_0229ad18 @ 0x0229ad18, 0x78 bytes, Thumb
 * func_ov095_0229acc0 @ 0x0229acc0, 0x58 bytes, Thumb
 * func_ov095_0229ac8c @ 0x0229ac8c, 0x34 bytes, Thumb
 * func_ov095_0229ac2c @ 0x0229ac2c, 0x5e bytes, Thumb
 * func_ov095_0229ab68 @ 0x0229ab68, 0xc2 bytes, Thumb
 */

typedef struct {
    int a;
    int b;
} Elem;

typedef struct {
    char pad_00[0x44];
    Elem *arr;
} UnkStruct_0229ae5c;

typedef struct {
    int a;
    int b;
} Entry8;

typedef struct {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
    char pad_34[0x44 - 0x34];
    Entry8 *arr;
} UnkStruct_0229adc4;

typedef struct {
    int word[2];
} Entry8_0229ad90;

struct UnkStruct_0229ad18 {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
};

typedef struct {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
} UnkStruct_0229acc0;

struct UnkStruct_0229ac8c {
    unsigned char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
};

struct func_ov095_0229ac2c_s {
    unsigned char pad_00[0x42];
    unsigned char kind;
};

typedef struct {
    unsigned char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
} UnkStruct_0229ab68;

extern int func_02088d9c(void *ptr);
extern int func_02088d94(Entry8 *ptr);
extern int func_ov095_022999b0(UnkStruct_0229adc4 *p, int a);
extern Entry8_0229ad90 data_ov095_0229e814[];
extern int func_ov095_0229cdf0(const void *, int code);
extern int func_ov090_022990b8(int);
extern int data_ov095_0229e380;

int func_ov095_0229ae5c(UnkStruct_0229ae5c *p, int key)
{
    if (key == 0xF8) {
        goto common;
    }
    if (key == 0xF9) {
        goto common;
    }
    if (key != 0xFA) {
        goto not_common;
    }
common:
    return func_02088d9c(&p->arr[key - 0xF8]) + 0x88;
not_common:
    return 0x80;
}

int func_ov095_0229adc4(UnkStruct_0229adc4 *self)
{
    int v = self->unk_28;
    if (v > 0x109) {
        goto big;
    }
    if (v >= 0x109) {
        goto med;
    }
    if (v > 0xfa) {
        goto fail;
    }
    if (v < 0xf8) {
        goto fail;
    }
    if (v == 0xf8) {
        goto common;
    }
    if (v == 0xf9) {
        goto common;
    }
    if (v != 0xfa) {
        goto fail;
    }
    goto common;
big:
    if (v != 0x10a) {
        goto fail;
    }
    goto big2;
common:
    self->unk_2C = func_ov095_0229ae5c((UnkStruct_0229ae5c *) self, v);
    self->unk_30 = func_02088d94(&self->arr[v - 0xf8]) + 0x68;
    return 1;
med:
    self->unk_2C = 0x18;
    self->unk_30 = 0x54;
    if (func_ov095_022999b0(self, 4) == 0) {
        self->unk_30 -= 8;
    }
    return 1;
big2:
    self->unk_2C = 0xe8;
    self->unk_30 = 0x54;
    if (func_ov095_022999b0(self, 4) == 0) {
        self->unk_30 -= 8;
    }
    return 1;
fail:
    return 0;
}

int func_ov095_0229ad90(int unused, int id)
{
    if (id >= 0x10c && id <= 0x10f) {
        return func_02088d9c((void *) (&data_ov095_0229e814[id - 0x10c])) + 0x88;
    } else {
        return 0x80;
    }
}

int func_ov095_0229ad18(struct UnkStruct_0229ad18 *p)
{
    if (p->unk_28 == 0xf7) {
        p->unk_2C = func_02088d9c((void *) (&data_ov095_0229e380)) + 0x98;
        p->unk_30 = func_02088d94((Entry8 *) (&data_ov095_0229e380)) + 0x70;
        return 1;
    }
    if (p->unk_28 >= 268 && p->unk_28 <= 271) {
        p->unk_2C = func_ov095_0229ad90((int) p, p->unk_28);
        p->unk_30 = func_02088d94((Entry8 *) (((int *) data_ov095_0229e814))) + 0x68;
        return 1;
    }
    if (func_ov095_0229cdf0(p, p->unk_28)) {
        p->unk_2C = func_ov090_022990b8(p->unk_28 - 0xfb);
        p->unk_30 = 8;
        return 1;
    }
    return 0;
}

int func_ov095_0229acc0(UnkStruct_0229acc0 *p)
{
    if (p->unk_28 == 0x103) {
        return 1;
    }
    switch (p->unk_28) {
        case 0x104:
            p->unk_2C = 0xca;
            p->unk_30 = 0xb6;
            return 1;
        case 0x105:
            p->unk_2C = 0x58;
            p->unk_30 = 0xb6;
            return 1;
        case 0x106:
            p->unk_2C = 0x74;
            p->unk_30 = 0xb6;
            return 1;
    }
    return 0;
}

int func_ov095_0229ac8c(struct UnkStruct_0229ac8c *s)
{
    switch (s->unk_28) {
        case 0x107:
            s->unk_2C = 0xc4;
            s->unk_30 = 0xb6;
            return 1;
        case 0x108:
            s->unk_2C = 0x7c;
            s->unk_30 = 0xb6;
            return 1;
        default:
            return 0;
    }
}

int func_ov095_0229ac2c(struct func_ov095_0229ac2c_s *self)
{
    int result = 0;

    if (func_ov095_0229adc4((UnkStruct_0229adc4 *) self) != 0) {
        return 1;
    }

    switch (self->kind) {
        case 0:
            result = func_ov095_0229ad18((struct UnkStruct_0229ad18 *) self);
            break;
        case 1:
        case 2:
            result = func_ov095_0229acc0((UnkStruct_0229acc0 *) self);
            break;
        case 3:
        case 4:
        case 5:
            result = func_ov095_0229ac8c((struct UnkStruct_0229ac8c *) self);
            break;
        default:
            break;
    }

    return result;
}

void func_ov095_0229ab68(UnkStruct_0229ab68 *self)
{
    int v;

    if (func_ov095_0229ac2c((struct func_ov095_0229ac2c_s *) self) != 0) {
        return;
    }

    v = self->unk_28;
    if (v < 0x3b) {
        return;
    }

    if (v <= 0x46) {
        self->unk_30 = 0x68;
        self->unk_2C = (self->unk_28 - 0x3b) * 0x14 + 0xe;
        return;
    }

    if (v <= 0x51) {
        self->unk_30 = 0x78;
        self->unk_2C = (self->unk_28 - 0x47) * 0x14 + 0x16;
        if (self->unk_28 == 0x51) {
            self->unk_2C = self->unk_2C + 0xa;
        }
        return;
    }

    if (v <= 0x5c) {
        self->unk_30 = 0x88;
        self->unk_2C = (self->unk_28 - 0x52) * 0x14 + 0xe;
        if (self->unk_28 == 0x5c) {
            self->unk_2C = self->unk_2C + 0xe;
        }
        return;
    }

    if (v <= 0x67) {
        self->unk_30 = 0x98;
        self->unk_2C = (self->unk_28 - 0x5d) * 0x14 + 0x16;
        if (self->unk_28 == 0x5d) {
            self->unk_2C = self->unk_2C - 3;
        }
        return;
    }

    if (v <= 0x6f) {
        int w;
        self->unk_30 = 0xa8;
        w = self->unk_28;
        if (w < 0x6b) {
            self->unk_2C = (w - 0x68) * 0x14 + 0x22;
        } else if (w == 0x6b) {
            self->unk_2C = 0x86;
        } else {
            self->unk_2C = (w - 0x6c) * 0x14 + 0xae;
        }
    }
}
