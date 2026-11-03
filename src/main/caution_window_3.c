/* caution_window_3: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02038758 @ 0x02038758, 0xd0 bytes, Thumb
 * func_020386fc @ 0x020386fc, 0x5c bytes, Thumb
 * func_020386c4 @ 0x020386c4, 0x38 bytes, Thumb
 * func_02038680 @ 0x02038680, 0x44 bytes, Thumb
 * func_0203864c @ 0x0203864c, 0x34 bytes, Thumb
 */

#define REG (&data_027e0148)
#define BLK (&data_027e02c8)
#define HWREG1 (*(volatile unsigned short *) 0x04000050)
#define HWREG2 (*(volatile unsigned short *) 0x04001050)

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    unsigned char pad_00[0xc8];
    unsigned char c8;
} UnkStruct_02038758;

typedef struct {
    unsigned char pad_00[0x7c];
    unsigned int unk_7C;
} UnkStruct_02038758_2;

typedef struct {
    unsigned char pad_00[0x40];
    Vec3 a, b, c;
} UnkStruct_02038758_3;

struct UnkStruct_020386fc {
    unsigned char pad_00[0xca];
    unsigned char unk_CA;
    unsigned char unk_CB;
    unsigned short unk_CC;
    unsigned short unk_CE;
};

typedef struct {
    unsigned long long data[6];
} Data48;

extern void G3i_PerspectiveW_(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f,
                              unsigned int g, void *h);
extern void G3i_LookAt_(Vec3 *a, Vec3 *b, Vec3 *c, int d, void *e);
extern int FX_MulFunc(int a, int b);
extern void func_02055e7c(void *p, Vec3 *v);
extern Vec3 data_021fbee8;
extern UnkStruct_02038758_2 data_027e0148;
extern UnkStruct_02038758_3 data_027e02c8;
extern char data_027e00d0[];
extern char data_027e0114[];
extern Data48 data_021fbe48;
extern void func_020e96c8(Data48 *, int, int, int, int, int, int);
extern int func_02057a7c(void *arg);
extern int func_020b9f80(void *arg1, void *arg2, int arg3, int arg4, int arg5);
extern void MI_CpuFill8(void *param1, int param2, int param3);

void func_02038758(UnkStruct_02038758 *self)
{
    Vec3 pos;
    Vec3 tgt;
    Vec3 up;
    Vec3 scale;
    int m;

    if (self->c8 == 0) {
        return;
    }
    G3i_PerspectiveW_(0x424, 0xf74, 0x1548, 0xf6, 0x0003e800, 0x1000, 0, data_027e00d0);
    REG->unk_7C = REG->unk_7C & ~0x50;
    pos.x = data_021fbee8.x;
    pos.y = data_021fbee8.y;
    pos.z = data_021fbee8.z;
    tgt.x = 0;
    tgt.y = 0;
    tgt.z = 0xfffff000;
    up.x = 0;
    up.y = 0x1000;
    up.z = 0;
    BLK->a.x = pos.x;
    BLK->a.y = pos.y;
    BLK->a.z = pos.z;
    BLK->b.x = up.x;
    BLK->b.y = up.y;
    BLK->b.z = up.z;
    BLK->c.x = tgt.x;
    BLK->c.y = tgt.y;
    BLK->c.z = tgt.z;
    G3i_LookAt_(&pos, &up, &tgt, 0, data_027e0114);
    REG->unk_7C = REG->unk_7C & ~0xe8;
    m = FX_MulFunc(0xb7, 0xf6d);
    scale.x = m;
    scale.y = m;
    scale.z = 0x1000;
    func_02055e7c((char *) self + 4, &scale);
}

void func_020386fc(struct UnkStruct_020386fc *p)
{
    if (p->unk_CB == 0) {
        return;
    }

    if (p->unk_CA != 0) {
        p->unk_CC = HWREG1;
        p->unk_CE = HWREG2;
        HWREG1 = 0;
        HWREG2 = 0;
    } else {
        HWREG1 = p->unk_CC;
        HWREG2 = p->unk_CE;
    }

    p->unk_CB = 0;
}

void func_020386c4(unsigned char *self)
{
    func_020e96c8(&data_021fbe48, 0, 0, 0xfffff000, 0, 0, 0xfffff000);
    {
        Data48 *dst = (Data48 *) (self + 0x68);
        *dst = data_021fbe48;
    }
}

void func_02038680(void *s, int n)
{
    char *p = *(char **) ((char *) s + 0x60);
    char *q = p + *(int *) (p + 8);
    char *r = q + *(unsigned short *) (q + 0xa);
    char *t = q + *(int *) (r + 8);
    int a = func_02057a7c(t);
    func_020b9f80((char *) s + 0xa0, (char *) s + 0x2e4, a + (n << 11), 0x800, 2);
}

void func_0203864c(void *param1)
{
    int i;
    void *ptr;

    ptr = (void *) ((char *) param1 + 0x2e4);
    MI_CpuFill8(ptr, 0x11, 0x800);
    for (i = 0; i < 4; i++) {
        func_02038680(param1, i);
    }
}
