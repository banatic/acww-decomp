/* star_scope_sky: 30 functions, module ov127
 * mwccarm 1.2/base -O4,s
 * func_ov127_02299d20 @ 0x02299d20, 0x44 bytes, Thumb
 * func_ov127_02299cd8 @ 0x02299cd8, 0x46 bytes, Thumb
 * func_ov127_02299c08 @ 0x02299c08, 0xd0 bytes, Thumb
 * func_ov127_02299bbc @ 0x02299bbc, 0x4c bytes, Thumb
 * func_ov127_02299b78 @ 0x02299b78, 0x44 bytes, Thumb
 * func_ov127_02299b58 @ 0x02299b58, 0x20 bytes, Thumb
 * func_ov127_02299abc @ 0x02299abc, 0x9c bytes, Thumb
 * func_ov127_02299a94 @ 0x02299a94, 0x28 bytes, Thumb
 * func_ov127_02299a50 @ 0x02299a50, 0x44 bytes, Thumb
 * func_ov127_02299a18 @ 0x02299a18, 0x38 bytes, Thumb
 * func_ov127_02299a00 @ 0x02299a00, 0x18 bytes, Thumb
 * func_ov127_022999c0 @ 0x022999c0, 0x40 bytes, Thumb
 * func_ov127_022998b4 @ 0x022998b4, 0x10c bytes, Thumb
 * func_ov127_022998a8 @ 0x022998a8, 0xc bytes, Thumb
 * func_ov127_0229989c @ 0x0229989c, 0xc bytes, Thumb
 * func_ov127_02299890 @ 0x02299890, 0xc bytes, Thumb
 * func_ov127_02299878 @ 0x02299878, 0x18 bytes, Thumb
 * func_ov127_02299868 @ 0x02299868, 0x10 bytes, Thumb
 * func_ov127_02299858 @ 0x02299858, 0x10 bytes, Thumb
 * func_ov127_02299844 @ 0x02299844, 0x12 bytes, Thumb
 * func_ov127_02299818 @ 0x02299818, 0x2c bytes, Thumb
 * func_ov127_02299804 @ 0x02299804, 0x12 bytes, Thumb
 * func_ov127_022997d8 @ 0x022997d8, 0x2c bytes, Thumb
 * func_ov127_022996e4 @ 0x022996e4, 0xf4 bytes, Thumb
 * func_ov127_022996d8 @ 0x022996d8, 0xc bytes, Thumb
 * func_ov127_022996c8 @ 0x022996c8, 0x10 bytes, Thumb
 * func_ov127_022996bc @ 0x022996bc, 0xc bytes, Thumb
 * func_ov127_02299680 @ 0x02299680, 0x3c bytes, Thumb
 * func_ov127_0229960c @ 0x0229960c, 0x74 bytes, Thumb
 * func_ov127_022995a0 @ 0x022995a0, 0x6c bytes, Thumb
 */

#include "types.h"

struct Entry {
    unsigned int unk_00;
    unsigned int unk_04;
};

struct UnkStruct_02299c08 {
    char pad_00[0x2824];
    short unk_2824;
    short unk_2826;
    short unk_2828;
    char pad_282A[0x2834 - 0x282A];
    unsigned char unk_2834;
};

typedef struct UnkStruct_02299b58 {
    char pad_00[0x2824];
    short unk_2824;
} UnkStruct_02299b58;

typedef struct {
    unsigned char pad_00[0x2826];
    short unk_2826;
    short unk_2828;
} UnkStruct_02299abc;

typedef struct {
    unsigned char pad_00[0x2824];
    unsigned short unk_2824;
    unsigned short unk_2826;
} unk_struct;

struct UnkStruct_02299a50 {
    unsigned char pad_00[0x2824];
    short unk_2824;
    short unk_2826;
};

struct UnkStruct_022999c0 {
    char pad_00[0x282a];
    unsigned short unk_282A;
    short unk_282C;
};

struct UnkStruct_022998b4 {
    char pad_00[0x2824];
    short unk_2824;
    short unk_2826;
    char pad_2828[2];
    short unk_282A;
    short unk_282C;
};

typedef struct {
    char pad_00[0x2824];
    short unk_2824;
} UnkStruct_0229989c;

typedef struct {
    char pad_00[0x2830];
    unsigned short flags;
} Struct_ov127_02299878;

typedef struct {
    char pad_00[0x2a];
    u16 ids[16];
} UnkStruct_0229960c;

extern struct Entry data_ov127_0229b614[];
extern int func_02088d34(struct Entry *, int, int, int, int);
extern void func_02004658(int a);
extern void func_02004644(int a, int b);
extern void func_020041bc(int a);
extern unsigned char data_ov127_0229b5e0[];
extern void *data_ov127_0229a0fc[];
extern void func_020b0ffc(void *ptr, int argument1, int argument2);
extern void func_020eaca0(int *out, int *a, int *b);
extern int func_020ea9c8(int *vec);
extern int FX_MulFunc(int a, int b);
extern int FX_Div(int a, int b);
extern void func_01ffd070(int *out, int *a, int *b);
extern int func_020b1050(int argument0, int argument1);
extern unsigned short data_ov127_0229a5d8[];
extern unsigned char data_ov127_0229a104[];
extern unsigned short data_ov127_0229a24c[];
extern int func_020b1530(int);
extern unsigned char data_ov127_0229b6e0[0x11];
extern unsigned char data_ov127_0229b6f4[0x11];
extern int func_020b1498(int i);

void func_ov127_02299b58(UnkStruct_02299b58 *base, int delta);
int func_ov127_02299abc(UnkStruct_02299abc *s, int value, int flag);
int func_ov127_02299878(Struct_ov127_02299878 *s, unsigned int mask);
void func_ov127_02299868(unsigned short *p, unsigned short val);
void func_ov127_02299858(void *base, unsigned short mask);
int func_ov127_02299818(unsigned int index);
int func_ov127_022997d8(unsigned int idx);

int func_ov127_02299d20(int unused, int a, int b)
{
    int x = a - 0x80;
    int y = b - 0x60;
    unsigned char i = 0;

    while (i < 4) {
        if (func_02088d34(&data_ov127_0229b614[i], x, y, 2, 2)) {
            return i;
        }
        i = (unsigned char) (i + 1);
    }

    return 4;
}

void func_ov127_02299cd8(int a, unsigned int sw, int b, int c)
{
    switch (sw) {
        case 0:
            func_ov127_02299b58((UnkStruct_02299b58 *) a, -b);
            break;
        case 1:
            func_ov127_02299b58((UnkStruct_02299b58 *) a, b);
            break;
        case 2:
            func_ov127_02299abc((UnkStruct_02299abc *) a, b, c);
            break;
        case 3:
            func_ov127_02299abc((UnkStruct_02299abc *) a, -b, c);
            break;
        default:
            break;
    }
}

void func_ov127_02299c08(struct UnkStruct_02299c08 *self, int param1, int param2)
{
    int old1 = self->unk_2828;
    int old2 = self->unk_2824;
    int old3 = self->unk_2826;
    int changed;

    func_ov127_02299cd8((int) self, (unsigned int) param1, 4, param2);
    self->unk_2834 = (unsigned char) param1;

    changed = 0;
    if (old1 != self->unk_2828 || old2 != self->unk_2824 || old3 != self->unk_2826) {
        changed = 1;
    }

    if (old3 != self->unk_2826) {
        if (self->unk_2826 == -0x18 || self->unk_2826 == 0x54) {
            changed = 0;
        }
    }

    if (changed != 0) {
        if (func_ov127_02299878((Struct_ov127_02299878 *) self, (unsigned int) 8) == 0) {
            func_ov127_02299868((unsigned short *) self, (unsigned short) 8);
            func_02004658(0x883);
        }
    } else {
        if (func_ov127_02299878((Struct_ov127_02299878 *) self, (unsigned int) 8) == 1) {
            func_ov127_02299858(self, (unsigned short) 8);
            func_02004644(0x883, 1);
        }
    }

    if (func_ov127_02299878((Struct_ov127_02299878 *) self, (unsigned int) 8) != 0 && param2 != 0) {
        func_020041bc(data_ov127_0229b5e0[param1]);
    }
}

void func_ov127_02299bbc(char *p0, int p1)
{
    if (func_ov127_02299878((Struct_ov127_02299878 *) p0, (unsigned int) 8)) {
        func_ov127_02299858((void *) p0, (unsigned short) 8);
        func_02004644(0x883, 1);
    }
    func_ov127_02299cd8((int) p0, (unsigned int) p1, 1, 0);
    *(p0 + 0x2836) = 2;
    *(p0 + 0x2835) = p1;
}

int func_ov127_02299b78(unsigned char *r0)
{
    if (r0[0x2836] != 0) {
        r0[0x2836]--;
        func_ov127_02299cd8((int) r0, (unsigned int) r0[0x2835], (int) data_ov127_0229a0fc[r0[0x2836]], 0);
    }
    if (r0[0x2836] == 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov127_02299b58(UnkStruct_02299b58 *base, int delta)
{
    base->unk_2824 = (base->unk_2824 + delta) & 0x1ff;
    func_ov127_02299868((unsigned short *) base, (unsigned short) 1);
}

int func_ov127_02299abc(UnkStruct_02299abc *s, int value, int flag)
{
    short orig26 = *(volatile short *) &s->unk_2826;

    if (flag != 0 && s->unk_2828 != 0) {
        int old28 = s->unk_2828;
        s->unk_2828 = (short) (old28 + value);
        if (s->unk_2828 < -68) {
            s->unk_2828 = -68;
        } else if (s->unk_2828 > 76) {
            s->unk_2828 = 76;
        }
        if (s->unk_2828 * old28 < 0) {
            s->unk_2828 = 0;
        }
        return 1;
    }

    s->unk_2826 = (short) (*(volatile short *) &s->unk_2826 + value);
    if (s->unk_2826 < -24) {
        s->unk_2826 = -24;
        if (flag) {
            s->unk_2828 = (short) value;
        }
    } else if (s->unk_2826 > 84) {
        s->unk_2826 = 84;
        if (flag) {
            s->unk_2828 = (short) value;
        }
    }

    func_ov127_02299868((unsigned short *) s, (unsigned short) 1);

    if (orig26 != s->unk_2826) {
        return 1;
    }
    return 0;
}

void func_ov127_02299a94(unk_struct *s, int a, int b)
{
    s->unk_2824 = (unsigned short) ((a - 0x80) & 0x1ff);
    s->unk_2826 = (unsigned short) (b - 0x60);
    func_ov127_02299abc((UnkStruct_02299abc *) s, 0, 0);
}

int func_ov127_02299a50(struct UnkStruct_02299a50 *p, int a, int b, int *out, int *out2)
{
    int x;
    int y;

    x = (a + p->unk_2824) & 0x1ff;
    y = b + p->unk_2826;

    if (y < 0 || y >= 0x100) {
        return 0;
    }

    *out = x >> 3;
    *out2 = y >> 3;
    return 1;
}

int func_ov127_02299a18(void *base, int x, int y, int arg4, int arg5)
{
    int offset = ((x >> 3) + ((y >> 3) << 5)) * 2;
    int val = *(unsigned short *) ((char *) base + offset + 0x2024);
    if ((val & 0x3ff) == 0x20) {
        return func_ov127_02299a50((struct UnkStruct_02299a50 *) base, x, y, (int *) arg4, (int *) arg5);
    }
    return 0;
}

void func_ov127_02299a00(void *self, int argument1, int argument2)
{
    func_020b0ffc((char *) self + 0x24, argument1, argument2);
    func_ov127_02299868((unsigned short *) self, (unsigned short) 2);
}

void func_ov127_022999c0(struct UnkStruct_022999c0 *obj, int a, int b)
{
    obj->unk_282A = (unsigned short) ((a - 0x80) & 0x1ff);
    obj->unk_282C = (short) (b - 0x60);
    if (obj->unk_282C < -24) {
        obj->unk_282C = -24;
    } else if (obj->unk_282C > 0x54) {
        obj->unk_282C = 0x54;
    }
    func_ov127_02299868((unsigned short *) obj, (unsigned short) 4);
}

void func_ov127_022998b4(struct UnkStruct_022998b4 *p)
{
    int a[3];
    int b[3];
    int c[3];
    int d[3];
    int e[3];
    int diff, angle, mag;

    func_ov127_02299868((unsigned short *) p, (unsigned short) 1);

    a[1] = 0;
    a[0] = (int) p->unk_2824 << 12;
    a[2] = (int) p->unk_2826 << 12;

    diff = (int) p->unk_282A - (int) p->unk_2824;
    angle = (int) p->unk_282A;
    if (diff <= -256) {
        angle += 0x200;
    } else if (diff >= 256) {
        angle -= 0x200;
    }
    b[0] = angle << 12;
    b[1] = 0;
    b[2] = (int) p->unk_282C << 12;

    func_020eaca0(d, b, a);

    c[0] = d[0];
    c[1] = d[1];
    c[2] = d[2];

    mag = func_020ea9c8(c);

    if (mag <= 0x8000) {
        func_ov127_02299858((void *) p, (unsigned short) 4);
        p->unk_2824 = p->unk_282A;
        p->unk_2826 = p->unk_282C;
        return;
    }

    diff = mag >> 1;
    if (diff < 0x8000) {
        diff = 0x8000;
    } else if (diff > 0x40000) {
        diff = 0x40000;
    }

    c[0] = FX_Div(FX_MulFunc(c[0], diff), mag);
    c[2] = FX_Div(FX_MulFunc(c[2], diff), mag);

    func_01ffd070(e, a, c);

    b[0] = e[0];
    b[1] = e[1];
    b[2] = e[2];
    p->unk_2824 = b[0] >> 12;
    p->unk_2826 = b[2] >> 12;
}

int func_ov127_022998a8(short *param0)
{
    return param0[0x1414];
}

int func_ov127_0229989c(UnkStruct_0229989c *self)
{
    return self->unk_2824;
}

short func_ov127_02299890(short *param)
{
    return param[0x1413];
}

int func_ov127_02299878(Struct_ov127_02299878 *s, unsigned int mask)
{
    if ((s->flags & mask) != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov127_02299868(unsigned short *p, unsigned short val)
{
    *((unsigned short *) ((char *) p + 0x2830)) |= val;
}

void func_ov127_02299858(void *base, unsigned short mask)
{
    *(unsigned short *) ((char *) base + 0x2830) &= ~mask;
}

int func_ov127_02299844(int argument0, int argument1)
{

    return func_ov127_02299818((unsigned int) func_020b1050(argument0, argument1));
}

int func_ov127_02299818(unsigned int index)
{
    unsigned short value = data_ov127_0229a5d8[index];
    if (((value & 0xf000) >> 12) == 1) {
        return value & 0x0fff;
    }
    return -1;
}

int func_ov127_02299804(int argument0, int argument1)
{

    return func_ov127_022997d8((unsigned int) func_020b1050(argument0, argument1));
}

int func_ov127_022997d8(unsigned int idx)
{
    unsigned short val = data_ov127_0229a5d8[idx];
    if (((val & 0xF000) >> 12) == 2) {
        return val & 0xFFF;
    } else {
        return -1;
    }
}

int func_ov127_022996e4(unsigned short *out, int x, int y)
{
    int xm = (x - 1) & 0x3f;
    int xp = (x + 1) & 0x3f;
    int ym = y - 1;
    int yp = y + 1;
    int count = 0;
    int r;

    if (ym >= 0) {
        r = func_ov127_02299804(xm, ym);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
        r = func_ov127_02299804(x, ym);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
        r = func_ov127_02299804(xp, ym);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
    }

    r = func_ov127_02299804(xm, y);
    if (r != -1) {
        out[count] = (unsigned short) r;
        count++;
    }
    r = func_ov127_02299804(xp, y);
    if (r != -1) {
        out[count] = (unsigned short) r;
        count++;
    }

    if (yp < 0x20) {
        r = func_ov127_02299804(xm, yp);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
        r = func_ov127_02299804(x, yp);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
        r = func_ov127_02299804(xp, yp);
        if (r != -1) {
            out[count] = (unsigned short) r;
            count++;
        }
    }

    if (x == 0x3e && y == 0) {
        count--;
    }

    return count;
}

unsigned char func_ov127_022996d8(unsigned int param)
{
    return data_ov127_0229a104[param * 2];
}

unsigned char func_ov127_022996c8(unsigned char a)
{
    return data_ov127_0229a104[(a << 1) + 1];
}

unsigned short *func_ov127_022996bc(int idx)
{
    return &data_ov127_0229a24c[idx];
}

int func_ov127_02299680(int param)
{
    int i;
    int j;
    int result;
    int *ptr;

    for (i = 0; i < 16; i++) {
        result = func_020b1530(i);
        if (result != 0) {
            for (j = 0; j < 16; j++) {
                if (param == *(unsigned short *) (result + (j << 1) + 0x2a)) {
                    return i;
                }
            }
        }
    }
    return -1;
}

void func_ov127_0229960c(UnkStruct_0229960c *a, u8 *out)
{
    int m;
    int i;
    int j;
    int k;
    int n;
    u8 *q;
    u8 *p;
    int id;

    for (m = 0; m < 0x11; m++) {
        out[m] = 0xff;
    }

    n = 0;
    for (i = 0; i < 0x10; i++) {
        id = a->ids[i];
        if (id == 0xffff) {
            continue;
        }
        q = (u8 *) func_ov127_022996bc((int) ((u16) id));
        for (j = 0; j < 2; j++) {
            k = 0;
            for (; k <= n; k++) {
                if (k == n) {
                    out[n] = q[j];
                    n++;
                    k = n + 1;
                } else if (out[k] == q[j]) {
                    k = n + 1;
                }
            }
        }
    }
}

int func_ov127_022995a0(void *self)
{
    int i, k, m, id;

    func_ov127_0229960c((UnkStruct_0229960c *) self, (u8 *) data_ov127_0229b6e0);

    for (i = 0; i < 0x10; i++) {
        id = func_020b1498(i);
        if (id != 0) {
            func_ov127_0229960c((UnkStruct_0229960c *) ((void *) id), (u8 *) data_ov127_0229b6f4);
            for (k = 0; k < 0x11 && data_ov127_0229b6e0[k] != 0xff; k++) {
                for (m = 0; m < 0x11 && data_ov127_0229b6f4[m] != 0xff; m++) {
                    if (data_ov127_0229b6e0[k] == data_ov127_0229b6f4[m]) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
