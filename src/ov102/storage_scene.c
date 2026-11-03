/* storage_scene: 12 functions, module ov102
 * mwccarm 1.2/base -O4,s
 * func_ov102_0229c560 @ 0x0229c560, 0x124 bytes, Thumb
 * func_ov102_0229c534 @ 0x0229c534, 0x2c bytes, Thumb
 * func_ov102_0229c504 @ 0x0229c504, 0x30 bytes, Thumb
 * func_ov102_0229c4c0 @ 0x0229c4c0, 0x44 bytes, Thumb
 * func_ov102_0229c460 @ 0x0229c460, 0x60 bytes, Thumb
 * func_ov102_0229c3bc @ 0x0229c3bc, 0xa4 bytes, Thumb
 * func_ov102_0229c364 @ 0x0229c364, 0x58 bytes, Thumb
 * func_ov102_0229c318 @ 0x0229c318, 0x4c bytes, Thumb
 * func_ov102_0229c2c0 @ 0x0229c2c0, 0x58 bytes, Thumb
 * func_ov102_0229c2a8 @ 0x0229c2a8, 0x18 bytes, Thumb
 * func_ov102_0229c298 @ 0x0229c298, 0x10 bytes, Thumb
 * func_ov102_0229c288 @ 0x0229c288, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229c560 {
    char pad_00;
} UnkStruct_0229c560;

typedef struct UnkStruct_0229c560_2 {
    char pad_00[0x2274];
    UnkStruct_0229c560 unk_2274;
    char pad1[0x25a5 - 0x2274 - sizeof(UnkStruct_0229c560)];
    unsigned char unk_25A5;
} UnkStruct_0229c560_2;

typedef struct {
    char pad_00[0x23f4];
    char arr[2][0x6c];
    char pad_24CC[0xdc];
    char flag;
} UnkStruct_0229c534;

struct UnkStruct_0229c460 {
    char pad_00[0x25a9];
    unsigned char unk_25A9;
};

typedef struct {
    u8 pad_00[0x24d4];
    void *unk_24D4;
    u8 pad_24D8[0x25aa - (0x24d4 + 4)];
    u8 unk_25AA;
} Param;

struct UnkStruct_0229c364 {
    char pad_00[0x25aa];
    unsigned char unk_25AA;
};

typedef struct UnkStruct_0229c318 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0x218c - 0x8d];
    unsigned char unk_218C;
    unsigned char pad_218D[0x25aa - 0x218d];
    unsigned char unk_25AA;
} UnkStruct_0229c318;

typedef struct {
    unsigned char pad_00[0x25aa];
    unsigned char data;
} UnkStruct_0229c2c0;

typedef struct {
    unsigned short pad_00;
    unsigned short flags;
} GlobalFlags;

extern int func_ov102_0229d464(UnkStruct_0229c560_2 *p, int byte);
extern int func_ov102_0229d454(UnkStruct_0229c560_2 *p, int byte);
extern int func_ov102_0229d444(UnkStruct_0229c560_2 *p, int byte);
extern int func_ov102_0229d438(UnkStruct_0229c560_2 *p, int byte);
extern void func_ov102_0229c8bc(UnkStruct_0229c560_2 *p, int a, int b);
extern void func_ov102_0229c790(UnkStruct_0229c560_2 *p, int a, int b);
extern void func_ov102_0229c740(UnkStruct_0229c560_2 *p, int a);
extern void func_ov102_0229c684(UnkStruct_0229c560_2 *p, int a, int b);
extern void func_ov002_0220a374(UnkStruct_0229c560 *p, int arg);
extern void func_ov002_0220a314(UnkStruct_0229c560 *p);
extern void func_ov002_0220a2b4(UnkStruct_0229c560 *p);
extern void func_0208e4c0(UnkStruct_0229c560 *p, int arg);
extern void func_02070b84(void *);
extern void func_02070adc(int, int, int, int, int, int, int);
extern int func_0207094c(int, int);
extern void func_02070a04(int, int, int);
extern void func_0200467c(int n);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_0206fc4c(int n);
extern int func_020984e8(void);
extern void *func_0209898c(int object);
extern unsigned short *func_0203a674(void *record);
extern void MI_CpuCopy8(void *addr, void *v, int n);
extern int func_020896b8(int a, void *b, int c, void *d, int e, int f, int g);
extern u8 data_ov102_0229eac0[];
extern int func_02088d34(unsigned short *, int, int, int, int);
extern int func_ov002_02207d24(void *, int);
extern void func_ov102_0229cb50(UnkStruct_0229c318 *);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern unsigned short data_ov102_0229e95c[];
extern GlobalFlags data_021fbe40;

void func_ov102_0229c298(unsigned int *p, unsigned int mask);
void func_ov102_0229c288(unsigned int arg0, unsigned int arg1);

int func_ov102_0229c560(UnkStruct_0229c560_2 *self, int a, int b)
{
    unsigned char state;
    state = self->unk_25A5;
    func_ov102_0229c288((unsigned int) self, 0x30);
    func_ov102_0229c288((unsigned int) self, 0x100);
    if (a == 0) {
        return 0;
    }

    if (func_ov102_0229d464(self, self->unk_25A5)) {
        func_ov102_0229c8bc(self, a, b);
    } else if (func_ov102_0229d454(self, self->unk_25A5)) {
        func_ov102_0229c790(self, a, b);
        if (b == 1) {
            if (func_ov102_0229d444(self, self->unk_25A5)) {
                func_ov002_0220a374(&self->unk_2274, 1);
            }
        }
    } else if (func_ov102_0229d438(self, self->unk_25A5)) {
        func_ov102_0229c740(self, a);
    } else if (func_ov102_0229d444(self, self->unk_25A5)) {
        func_ov102_0229c684(self, a, b);
        if (b == 1) {
            if (!func_ov102_0229d444(self, self->unk_25A5)) {
                func_0208e4c0(&self->unk_2274, 4);
            }
        }
    }

    if (func_ov102_0229d438(self, self->unk_25A5) != func_ov102_0229d438(self, state)) {
        if (func_ov102_0229d438(self, self->unk_25A5)) {
            func_ov002_0220a314(&self->unk_2274);
        } else {
            func_ov002_0220a2b4(&self->unk_2274);
        }
        func_ov102_0229c298((unsigned int *) self, 0x100);
    }

    if (state != self->unk_25A5) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov102_0229c534(UnkStruct_0229c534 *self)
{
    int i;

    self->flag = 0;

    for (i = 0; i < 2; i++) {
        func_02070b84(self->arr[i]);
    }
}

unsigned char *func_ov102_0229c504(unsigned char *base)
{
    unsigned char v = base[0x25a8];
    if (v >= 2) {
        return base + 0x2460;
    }
    v++;
    base[0x25a8] = v;
    return base + 0x23f4 + (base[0x25a8] - 1) * 0x6c;
}

void func_ov102_0229c4c0(int param1, int param2)
{
    int r5;
    int r4;
    int sp[3];

    r5 = 1;
    if (param2 != 0) {
        r5 = 15;
    }
    r4 = (int) func_ov102_0229c504((unsigned char *) param1);
    sp[0] = r5;
    sp[1] = 9;
    sp[2] = 0;
    func_02070adc(r4, 4, 0x1d6, 6, sp[0], sp[1], sp[2]);
    func_0207094c(r4, 0x88);
    func_02070a04(r4, 1, 1);
}

void func_ov102_0229c460(struct UnkStruct_0229c460 *self, int flag)
{
    unsigned short *v;

    func_0200467c(0x27);
    if (flag) {
        self->unk_25A9 = 5;
    } else {
        self->unk_25A9 = 0;
    }
    func_ov002_02208098(self, 0xf);
    func_ov102_0229c4c0((int) self, 1);
    func_0206fc4c(1);
    v = func_0203a674(func_0209898c(func_020984e8()));
    MI_CpuCopy8((char *) self + 0x24e8, v, 0xb4);
}

void func_ov102_0229c3bc(Param *p)
{
    u8 *r6 = (u8 *) p->unk_24D4 + 0x60;
    int i = 0;
    int j = i;
    int m1 = ~i;
    u8 *tmp10;
    int tmp14;
    int local18 = i;
    int local1c = i;
    int local20 = i;

    do {
        if (i == p->unk_25AA) {
            tmp10 = r6 + 2;
            tmp14 = 4;
        } else {
            tmp10 = r6;
            tmp14 = 5;
        }

        func_020896b8(1, &data_ov102_0229eac0[j * 8], 0x80, tmp10, m1, 1, local18);
        func_020896b8(1, &data_ov102_0229eac0[(j + 1) * 8], 0x80, tmp10, tmp14, 1, local1c);
        func_020896b8(1, &data_ov102_0229eac0[(j + 2) * 8], 0x80, r6, m1, 1, local20);

        i++;
        j += 3;
    } while (i < 6);
}

int func_ov102_0229c364(struct UnkStruct_0229c364 *p0, int p1, int p2)
{
    int a = p1 - 0x80;
    int b = p2 - 0x60;
    int i = 0;
    int j = 0;

    while (i < 6) {
        if (i != p0->unk_25AA) {
            if (func_02088d34(&((unsigned short *) data_ov102_0229eac0)[j * 4], a, b, 2, 2) != 0) {
                p0->unk_25AA = (unsigned char) i;
                return 1;
            }
        }
        i++;
        j += 3;
    }
    return 0;
}

void func_ov102_0229c318(UnkStruct_0229c318 *obj)
{
    func_ov002_02207d24(&obj->unk_218C, 1);
    func_ov102_0229cb50(obj);
    obj->unk_8C = 7;
    func_ov002_022080a0(obj, 1);
    func_0200467c(data_ov102_0229e95c[obj->unk_25AA]);
    func_ov102_0229c298((unsigned int *) obj, 0x40);
}

int func_ov102_0229c2c0(UnkStruct_0229c2c0 *p)
{
    int flag;
    unsigned short fl;

    flag = 0;
    fl = data_021fbe40.flags;

    if (fl & 0x200) {
        flag = -1;
    } else if (fl & 0x100) {
        flag = 1;
    }

    if (flag != 0) {
        flag = flag + p->data;

        if (flag < 0) {
            flag = 5;
        } else if (flag >= 6) {
            flag = 0;
        }

        p->data = (unsigned char) flag;
        func_ov102_0229c318((UnkStruct_0229c318 *) ((void *) p));
    }

    return 0;
}

int func_ov102_0229c2a8(unsigned int *base, unsigned int mask)
{
    if ((base[0x933] & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov102_0229c298(unsigned int *p, unsigned int mask)
{
    *((unsigned int *) ((char *) p + 0x24cc)) |= mask;
}

void func_ov102_0229c288(unsigned int arg0, unsigned int arg1)
{
    *(unsigned int *) ((char *) 0x24cc + arg0) &= ~arg1;
}
