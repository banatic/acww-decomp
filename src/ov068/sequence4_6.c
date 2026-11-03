/* sequence4_6: 16 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02272e28 @ 0x02272e28, 0x4 bytes, Thumb
 * func_ov068_02272df0 @ 0x02272df0, 0x38 bytes, Thumb
 * func_ov068_02272dd0 @ 0x02272dd0, 0x20 bytes, Thumb
 * func_ov068_02272dc8 @ 0x02272dc8, 0x8 bytes, Thumb
 * func_ov068_02272db4 @ 0x02272db4, 0x14 bytes, Thumb
 * func_ov068_02272d64 @ 0x02272d64, 0x50 bytes, Thumb
 * func_ov068_02272d60 @ 0x02272d60, 0x4 bytes, Thumb
 * func_ov068_02272d5c @ 0x02272d5c, 0x2 bytes, Thumb
 * func_ov068_02272d1c @ 0x02272d1c, 0x40 bytes, Thumb
 * func_ov068_02272cd4 @ 0x02272cd4, 0x48 bytes, Thumb
 * func_ov068_02272cb0 @ 0x02272cb0, 0x24 bytes, Thumb
 * func_ov068_02272c64 @ 0x02272c64, 0x4c bytes, Thumb
 * func_ov068_02272c54 @ 0x02272c54, 0x10 bytes, Thumb
 * func_ov068_02272c30 @ 0x02272c30, 0x24 bytes, Thumb
 * func_ov068_02272be4 @ 0x02272be4, 0x4c bytes, Thumb
 * func_ov068_02272bd4 @ 0x02272bd4, 0x10 bytes, Thumb
 */

typedef struct {
    char pad_00[0x2cc];
    int unk_2CC;
    int unk_2D0;
    int unk_2D4;
} InputStruct;

struct Triple {
    int a;
    int b;
    int c;
};

struct Res {
    int unk_00;
    int pad_04;
    int v1;
};

struct Params {
    int unk_00;
    int p1;
    int p2;
    int p3;
};

struct UnkStruct_02272c64 {
    unsigned char pad_00[0x1e0];
    unsigned int unk_1E0;
    unsigned char pad_1E4[0x2cc - 0x1e4];
    unsigned int unk_2CC;
    unsigned char pad_2D0[0x2e0 - 0x2d0];
    unsigned int unk_2E0;
};

typedef struct {
    char pad_00[0x2e0];
    int unk_2E0;
} UnkStruct_02272c54;

typedef struct {
    char pad_00[0x2cc];
    char array[0x18];
    int result;
} UnkStruct_02272c30;

extern void func_0203e328(void);
extern void func_020b22c4(void);
extern void func_020b22e8(void);
extern int func_ov009_02264d18(void *argument0);
extern void func_01ffd070(void *, void *, void *);
extern int FX_Div(int, int);
extern struct Triple *func_02095794(int);
extern void func_020eaca0(void *, void *, void *);
extern int func_020e8ed8(int, int);
extern int func_020912d4(int, void *, int, int);
extern void func_02091278(unsigned int, void *, int, int);
extern void func_0209129c(int);

void func_ov068_02272c54(UnkStruct_02272c54 *self);
void func_ov068_02272bd4(unsigned int *arg);

int func_ov068_02272e28(void)
{
    return 1;
}

int func_ov068_02272df0(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x2b4) != 0) {
        func_0203e328();
    }
    if (*(unsigned char *) ((char *) arg0 + 0x2de) != 0) {
        *(unsigned char *) ((char *) arg0 + 0x2de) = 0;
        func_020b22c4();
        func_020b22e8();
    }
    return 1;
}

void func_ov068_02272dd0(unsigned int *dst, unsigned char *src)
{
    dst[0] = *(unsigned int *) (src + 0x2cc);
    dst[1] = *(unsigned int *) (src + 0x2d0);
    dst[2] = *(unsigned int *) (src + 0x2d4);
}

int func_ov068_02272dc8(void *argument0)
{
    return func_ov009_02264d18(argument0);
}

int func_ov068_02272db4(void *self)
{
    if (*(int *) ((char *) self + 0x2b4) != 0) {
        return 1;
    }
    return 0;
}

void func_ov068_02272d64(void *dst, int cond, void *src)
{
    unsigned int tmp[3];
    unsigned int out[3];
    unsigned char *p;
    unsigned char *q;

    if (cond != 0) {
        return;
    }

    p = *(unsigned char **) ((char *) src + 0xb4);
    q = p + 0x4c;
    tmp[0] = *(unsigned int *) q;
    tmp[1] = *(unsigned int *) (q + 4);
    tmp[2] = *(unsigned int *) (q + 8);

    func_01ffd070(out, (char *) dst + 0x5c, tmp);

    *(unsigned int *) ((char *) dst + 0x2cc) = out[0];
    *(unsigned int *) ((char *) dst + 0x2d0) = out[1];
    *(unsigned int *) ((char *) dst + 0x2d4) = out[2];
}

int func_ov068_02272d60(void *object)
{
    return 0;
}

void func_ov068_02272d5c(void *object) {}

void func_ov068_02272d1c(int *out, InputStruct *in)
{
    out[0] = in->unk_2CC;
    out[1] = in->unk_2D0;
    out[2] = in->unk_2D4;
    out[0] += FX_Div(0x19000, 0x64000) - 0xf6;
}

int func_ov068_02272cd4(int arg0)
{
    if (func_02095794(4) != 0) {
        struct Triple *p = func_02095794(4);
        struct Triple src;
        struct Res res;
        struct Params params;
        src.a = p->a;
        src.b = p->b;
        src.c = p->c;
        func_ov068_02272d1c((int *) (&params), (InputStruct *) arg0);
        func_020eaca0(&res, &params, &src);
        return func_020e8ed8(res.unk_00, res.v1);
    } else {
        return 0;
    }
}

void func_ov068_02272cb0(char *base)
{
    int ret = func_020912d4(0x41, base + 0x2cc, 0, 0);
    *(int *) (base + 0x2e0) = ret;
}

void func_ov068_02272c64(struct UnkStruct_02272c64 *self)
{
    unsigned int val;
    val = (self->unk_1E0 << 4) >> 16;
    if (val < 0x2d || val > 0x31) {
        return;
    }
    if (val == 0x2d) {
        func_ov068_02272cb0((char *) self);
    }
    func_02091278(self->unk_2E0, &self->unk_2CC, 0, 0);
    if (val == 0x31) {
        func_ov068_02272c54((UnkStruct_02272c54 *) self);
    }
}

void func_ov068_02272c54(UnkStruct_02272c54 *self)
{
    func_0209129c(self->unk_2E0);
}

void func_ov068_02272c30(UnkStruct_02272c30 *obj)
{
    int zero = 0;
    obj->result = func_020912d4(0x42, obj->array, zero, zero);
}

void func_ov068_02272be4(unsigned int *self)
{
    unsigned int state = (self[0x78] << 4) >> 16;

    if (state < 0x25 || state > 0x32) {
        return;
    }
    if (state == 0x25) {
        func_ov068_02272c30((UnkStruct_02272c30 *) self);
    }
    func_02091278((unsigned int) (*(void **) (self + 0xb9)), (char *) self + 0x2cc, 0, 0);
    if (state == 0x32) {
        func_ov068_02272bd4((unsigned int *) self);
    }
}

void func_ov068_02272bd4(unsigned int *arg)
{
    func_0209129c(arg[185]);
}
