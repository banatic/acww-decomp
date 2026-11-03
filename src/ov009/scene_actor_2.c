/* scene_actor_2: 16 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_02263344 @ 0x02263344, 0x68 bytes, Thumb
 * func_ov009_02263320 @ 0x02263320, 0x24 bytes, Thumb
 * func_ov009_0226331c @ 0x0226331c, 0x2 bytes, Thumb
 * func_ov009_02263318 @ 0x02263318, 0x2 bytes, Thumb
 * func_ov009_02263314 @ 0x02263314, 0x2 bytes, Thumb
 * func_ov009_022632c8 @ 0x022632c8, 0x4c bytes, Thumb
 * func_ov009_0226321c @ 0x0226321c, 0xac bytes, Thumb
 * func_ov009_022631b4 @ 0x022631b4, 0x68 bytes, Thumb
 * func_ov009_0226314c @ 0x0226314c, 0x68 bytes, Thumb
 * func_ov009_02263148 @ 0x02263148, 0x4 bytes, Thumb
 * func_ov009_02263144 @ 0x02263144, 0x4 bytes, Thumb
 * func_ov009_02263140 @ 0x02263140, 0x4 bytes, Thumb
 * func_ov009_0226313c @ 0x0226313c, 0x4 bytes, Thumb
 * func_ov009_022630e4 @ 0x022630e4, 0x58 bytes, Thumb
 * func_ov009_022630b4 @ 0x022630b4, 0x30 bytes, Thumb
 * func_ov009_022630a0 @ 0x022630a0, 0x14 bytes, Thumb
 */

struct UnkStruct_02263344 {
    char pad_00[0x12c];
    int unk_12C;
    char pad_130[6];
    unsigned short unk_136;
};

typedef struct {
    char pad_00[0xEC];
    char sub[0x1E];
    char flag;
} UnkStruct_02263320;

typedef struct {
    long long unk_00;
    long long unk_08;
    long long unk_10;
    long long unk_18;
    long long unk_20;
    long long unk_28;
} UnkStruct_022632c8;

typedef struct UnkStruct_0226321c {
    unsigned char pad_00[0x28];
    int unk_28;
    unsigned char pad1[4];
    int unk_30;
} UnkStruct_0226321c;

typedef struct UnkStruct_0226321c_2 {
    unsigned char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    unsigned char pad1[0x28c - 0x68];
    UnkStruct_0226321c *unk_28C;
    unsigned char flag290;
} UnkStruct_0226321c_2;

typedef struct {
    char pad_00[0x136];
    unsigned short unk_136;
} InputStruct;

typedef struct {
    unsigned char pad_00[0x136];
    unsigned short unk_136;
} UnkStruct_0226314c;

typedef struct {
    char data[10];
} Elem;

typedef struct {
    char pad_00[0x134];
    unsigned char unk_134;
} UnkStruct_022630a0;

extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern void func_020676c4(int, int);
extern void func_020a8164(void *a, void *b);
extern unsigned char data_ov009_02265a18[];
extern void func_ov009_022646b8(void *p, int v);
extern void func_0205510c(void *p, int v);
extern void func_ov009_022645b8(void *p, void *s);
extern int func_020e8ed8(int, int);
extern int FX_MulFunc(int, int);
extern void func_01ffd070(int *, int, int *);
extern int func_02032754(void *);
extern char data_020d1f24[];
extern void func_020b2a68(char *dst, char *src);
extern int func_020b2a50(char *buf);
extern void func_020b2a64(char *buf);
extern int func_020b2a4c(void *buf);
extern int func_ov009_02264e30(void *p);
extern int func_ov009_02264d60(void *p);
extern int func_ov009_02264dc8(void *p);
extern int data_021c67d0[];
extern int data_021c67a4;

void func_ov009_02263344(struct UnkStruct_02263344 *self)
{
    int result;
    if (func_0204bcdc(&self->unk_136) != 0) {
        unsigned short local = 0x500a;
        result = (func_0204bc64(&self->unk_136) == func_0204bc64(&local));
    } else {
        result = (self->unk_136 == 0x500a);
    }
    if (!result) {
        func_020676c4(self->unk_12C, 100);
    }
}

void func_ov009_02263320(UnkStruct_02263320 *self)
{
    volatile long long unused;
    (void) &unused;
    func_020a8164(&self->sub, (void *) data_ov009_02265a18);
    self->flag = 0;
}

void func_ov009_0226331c(void *object) {}

void func_ov009_02263318(void *object) {}

void func_ov009_02263314(void *object) {}

void func_ov009_022632c8(void *p)
{
    if (*(int *) ((char *) p + 0x198) != 0) {
        UnkStruct_022632c8 local;
        func_ov009_022646b8(p, 0);
        func_0205510c((char *) p + 0x13c, 0);
        local = *(UnkStruct_022632c8 *) ((char *) p + 0x1a0);
        func_ov009_022645b8(p, &local);
    }
}

int func_ov009_0226321c(UnkStruct_0226321c_2 *self, int *out, short *b)
{
    if (self->unk_28C && self->flag290) {
        int v;
        int arr[4];
        int dest[3];

        v = func_020e8ed8(self->unk_28C->unk_28, self->unk_28C->unk_30);
        arr[0] = FX_MulFunc(0x1000, self->unk_28C->unk_30);
        arr[1] = FX_MulFunc(0x1000, self->unk_28C->unk_28);
        arr[2] = 0;
        arr[3] = arr[0];

        if (b) {
            *b = (short) (v + 0x8000);
        }

        if (out) {
            func_01ffd070(dest, func_02032754(self->unk_28C), &arr[1]);
            out[0] = dest[0];
            out[1] = dest[1];
            out[2] = dest[2];
            out[1] = 0x200;
            out[2] -= 0x200;
        }

        return 1;
    } else {
        out[0] = self->unk_5C;
        out[1] = self->unk_60;
        out[2] = self->unk_64;
        return 0;
    }
}

int func_ov009_022631b4(InputStruct *input)
{
    int flag = 0;
    unsigned short val = input->unk_136;
    unsigned int idx;
    char *ptr;
    char local[16];
    int result;

    if (val >= 0x5000u && val <= 0x5021u) {
        flag = 1;
    }
    if (flag != 0) {
        idx = val & 0xFFF;
    } else {
        idx = -1;
    }
    if (idx < 0x22u) {
        ptr = data_020d1f24 + idx * 10;
    } else {
        ptr = data_020d1f24;
    }
    func_020b2a68(local, ptr);
    result = func_020b2a50(local);
    func_020b2a64(local);
    return result;
}

int func_ov009_0226314c(UnkStruct_0226314c *param)
{
    int local[4];
    int flag = 0;
    unsigned int value;
    unsigned int v;
    Elem *ptr;
    int ret;

    value = param->unk_136;
    if (value >= 0x5000 && value <= 0x5021) {
        flag = 1;
    }

    if (flag != 0) {
        v = value & 0xfff;
    } else {
        v = 0xffffffff;
    }

    if (v < 0x22) {
        ptr = &((Elem *) data_020d1f24)[v];
    } else {
        ptr = ((Elem *) data_020d1f24);
    }

    func_020b2a68((char *) local, (char *) ptr);
    ret = func_020b2a4c(local);
    func_020b2a64((char *) local);
    return ret;
}

int func_ov009_02263148(void *object)
{
    return 0;
}

int func_ov009_02263144(void *object)
{
    return 1;
}

int func_ov009_02263140(void *object)
{
    return 1;
}

int func_ov009_0226313c(void *object)
{
    return 0;
}

int func_ov009_022630e4(void *self)
{
    int dx, dy, *g2;
    if (data_021c67a4 == 0) {
        goto r1b;
    }
    g2 = data_021c67d0;
    dx = *(int *) ((char *) self + 0x5c) - g2[0];
    if (dx < 0) {
        dx = -dx;
    }
    dy = *(int *) ((char *) self + 0x64) - g2[2];
    if (dx > func_ov009_02264e30(self)) {
        goto r1;
    }
    if (dy > func_ov009_02264d60(self)) {
        goto r1;
    }
    if (dy >= -func_ov009_02264dc8(self)) {
        goto r0;
    }
r1:
    return 1;
r0:
    return 0;
r1b:
    return 1;
}

void func_ov009_022630b4(void *ptr)
{
    ((unsigned char *) ptr)[0x235] &= ~1;
    if (func_ov009_022630e4(ptr)) {
        ((unsigned char *) ptr)[0x235] |= 1;
    }
}

int func_ov009_022630a0(UnkStruct_022630a0 *self)
{
    if (self->unk_134 == 0) {
        return 1;
    } else {
        return 0;
    }
}
