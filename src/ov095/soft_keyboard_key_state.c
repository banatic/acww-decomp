/* soft_keyboard_key_state: 10 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_0229cf64 @ 0x0229cf64, 0x12 bytes, Thumb
 * func_ov095_0229cef4 @ 0x0229cef4, 0x70 bytes, Thumb
 * func_ov095_0229ce84 @ 0x0229ce84, 0x70 bytes, Thumb
 * func_ov095_0229ce08 @ 0x0229ce08, 0x7c bytes, Thumb
 * func_ov095_0229cdf0 @ 0x0229cdf0, 0x18 bytes, Thumb
 * func_ov095_0229cddc @ 0x0229cddc, 0x14 bytes, Thumb
 * func_ov095_0229cda4 @ 0x0229cda4, 0x38 bytes, Thumb
 * func_ov095_0229cd30 @ 0x0229cd30, 0x74 bytes, Thumb
 * func_ov095_0229cce0 @ 0x0229cce0, 0x4e bytes, Thumb
 * func_ov095_0229cc9c @ 0x0229cc9c, 0x42 bytes, Thumb
 */

typedef struct {
    char pad_00[0x16];
    unsigned char switch_val;
    char pad_17[9];
    unsigned int flags;
} UnkStruct_0229cef4;

typedef struct {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[9];
    unsigned int unk_20;
} UnkStruct_0229ce84;

struct UnkStruct_0229ce08 {
    char pad_00[0x16];
    unsigned char type;
};

struct UnkStruct_0229cda4 {
    char pad_00[0x28];
    int unk_28;
};

typedef union {
    struct {
        unsigned int f0;
        unsigned int f4;
    } word;
    struct {
        unsigned int f0;
        unsigned short f4_low;
        unsigned short f4_high;
    } half;
} Entry;

typedef struct UnkStruct_0229cc9c {
    char pad_00[0x1b];
    unsigned char unk_1B;
} UnkStruct_0229cc9c;

extern void func_ov095_0229cb5c(void *, int, int);
extern void func_ov095_0229ca64(void *, int, int);
extern void func_ov095_0229c974(void *, int, int);
extern void func_ov095_022999a8(void *, int);
extern int data_ov095_0229d050[];
extern int data_ov095_0229d088[];
extern int data_ov095_0229d0c0[];
extern void *func_ov095_0229b16c(int);
extern void func_ov095_0229c8f0(void *, int, int);
extern void func_ov095_022999a0(UnkStruct_0229cc9c *param, int n);
extern int func_ov095_022999b0(UnkStruct_0229cc9c *param, int n);

void func_ov095_0229cc9c(UnkStruct_0229cc9c *param);

int func_ov095_0229cf64(int *a, int b)
{
    int result;
    int mask;

    mask = 1 << b;
    result = (a[8] & mask) != 0;
    return result;
}

void func_ov095_0229cef4(UnkStruct_0229cef4 *obj, int bit)
{
    obj->flags |= (1 << bit);
    switch (obj->switch_val) {
        case 0:
        case 3:
            break;
        case 1:
            func_ov095_0229cb5c(obj, data_ov095_0229d050[bit], 14);
            break;
        case 2:
            func_ov095_0229ca64(obj, data_ov095_0229d088[bit], 14);
            break;
        case 4:
            func_ov095_0229c974(obj, data_ov095_0229d0c0[bit], 14);
            break;
    }
    func_ov095_022999a8(obj, 1);
}

void func_ov095_0229ce84(void *obj, int idx)
{
    UnkStruct_0229ce84 *self = (UnkStruct_0229ce84 *) obj;
    self->unk_20 &= ~(1 << idx);
    switch (self->unk_16) {
        case 0:
            break;
        case 1:
            func_ov095_0229cb5c(obj, ((unsigned int *) data_ov095_0229d050)[idx], 12);
            break;
        case 2:
            func_ov095_0229ca64(obj, ((unsigned int *) data_ov095_0229d088)[idx], 12);
            break;
        case 3:
            break;
        case 4:
            func_ov095_0229c974(obj, ((unsigned int *) data_ov095_0229d0c0)[idx], 12);
            break;
        default:
            break;
    }
    func_ov095_022999a8(obj, 1);
}

int func_ov095_0229ce08(struct UnkStruct_0229ce08 *obj, int id)
{
    int i;
    const int *table;

    if (id == -1) {
        return 0;
    }

    switch (obj->type) {
        case 0:
            return 0;
        case 1:
            table = ((const int *) data_ov095_0229d050);
            break;
        case 2:
            table = ((const int *) data_ov095_0229d088);
            break;
        case 3:
            return 0;
        case 4:
            table = ((const int *) data_ov095_0229d0c0);
            break;
        default:
            return 0;
    }

    for (i = 0; i < 14; i++) {
        if (id == table[i]) {
            return func_ov095_0229cf64((int *) obj, i) != 0;
        }
    }

    return 0;
}

int func_ov095_0229cdf0(int r0, int r1)
{
    if (r1 >= 0xfb && r1 <= 0x102) {
        return 1;
    }
    return 0;
}

int func_ov095_0229cddc(void *a, int b)
{
    if (b == -1) {
        b = *(int *) ((char *) a + 0x28);
    }
    return func_ov095_0229cdf0((int) a, b);
}

int func_ov095_0229cda4(struct UnkStruct_0229cda4 *p, int id)
{
    if (id == -1) {
        id = p->unk_28;
    }
    switch (id - 0x104) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            return 1;
        default:
            return 0;
    }
}

void func_ov095_0229cd30(int param)
{
    Entry *arr;
    int i;

    arr = (Entry *) func_ov095_0229b16c(param);
    if (arr != 0) {
        for (i = 0; i < 100; i++) {
            arr[i].word.f4 = (arr[i].word.f4 & 0xffff0fff) | 0x0000c000;
            if (arr[i].half.f4_high == 0xffff) {
                i = 100;
            }
        }
    }
    for (i = 0; i < 14; i++) {
        if (func_ov095_0229cf64((int *) param, i)) {
            func_ov095_0229cef4((UnkStruct_0229cef4 *) param, i);
        }
    }
    func_ov095_0229cc9c((UnkStruct_0229cc9c *) param);
    func_ov095_022999a8((void *) param, 1);
}

void func_ov095_0229cce0(void *p)
{
    int i;
    if (((int *) p)[0x9] != -1) {
        func_ov095_0229c8f0(p, ((int *) p)[0x9], 0xc);
        ((int *) p)[0x9] = -1;
    }
    for (i = 0; i < 0xe; i++) {
        if (func_ov095_0229cf64((int *) p, i)) {
            func_ov095_0229cef4((UnkStruct_0229cef4 *) p, i);
        }
    }
    func_ov095_0229cc9c((UnkStruct_0229cc9c *) p);
    func_ov095_022999a8(p, 1);
}

void func_ov095_0229cc9c(UnkStruct_0229cc9c *param)
{
    if (param->unk_1B != 3) {
        func_ov095_022999a0(param, 0x20);
    }
    if (param->unk_1B == 2) {
    } else if (param->unk_1B == 3) {
        if (func_ov095_022999b0(param, 0x20)) {
            func_ov095_0229cb5c((void *) param, 0x5d, 0xd);
        } else {
            func_ov095_0229cb5c((void *) param, 0x52, 0xd);
        }
    }
}
