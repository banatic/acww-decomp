/* title_mes: 25 functions, module ov147
 * mwccarm 1.2/base -O4,s
 * func_ov147_0229a630 @ 0x0229a630, 0x4 bytes, Thumb
 * func_ov147_0229a628 @ 0x0229a628, 0x6 bytes, Thumb
 * func_ov147_0229a614 @ 0x0229a614, 0x14 bytes, Thumb
 * func_ov147_0229a608 @ 0x0229a608, 0xa bytes, Thumb
 * func_ov147_0229a594 @ 0x0229a594, 0x72 bytes, Thumb
 * func_ov147_0229a58c @ 0x0229a58c, 0x8 bytes, Thumb
 * func_ov147_0229a578 @ 0x0229a578, 0x12 bytes, Thumb
 * func_ov147_0229a4b4 @ 0x0229a4b4, 0xc4 bytes, Thumb
 * func_ov147_0229a48c @ 0x0229a48c, 0x28 bytes, Thumb
 * func_ov147_0229a468 @ 0x0229a468, 0x24 bytes, Thumb
 * func_ov147_0229a440 @ 0x0229a440, 0x28 bytes, Thumb
 * func_ov147_0229a420 @ 0x0229a420, 0x20 bytes, Thumb
 * func_ov147_0229a404 @ 0x0229a404, 0x1a bytes, Thumb
 * func_ov147_0229a3e4 @ 0x0229a3e4, 0x20 bytes, Thumb
 * func_ov147_0229a3ac @ 0x0229a3ac, 0x38 bytes, Thumb
 * func_ov147_0229a3a0 @ 0x0229a3a0, 0xc bytes, Thumb
 * func_ov147_0229a374 @ 0x0229a374, 0x2c bytes, Thumb
 * func_ov147_0229a31c @ 0x0229a31c, 0x58 bytes, Thumb
 * func_ov147_0229a300 @ 0x0229a300, 0x1c bytes, Thumb
 * func_ov147_0229a2f4 @ 0x0229a2f4, 0xa bytes, Thumb
 * func_ov147_0229a2dc @ 0x0229a2dc, 0x16 bytes, Thumb
 * func_ov147_0229a2d0 @ 0x0229a2d0, 0xa bytes, Thumb
 * func_ov147_0229a2a8 @ 0x0229a2a8, 0x28 bytes, Thumb
 * func_ov147_0229a280 @ 0x0229a280, 0x26 bytes, Thumb
 * func_ov147_0229a250 @ 0x0229a250, 0x2e bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[12];
    unsigned long unk_0C;
} UnkStruct_0229a628;

struct UnkStruct_0229a594 {
    int pad_00;
    int pad_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int pad_18;
    unsigned char unk_1C;
};

typedef struct {
    char b[0x4c];
} FSFile;

struct UnkStruct_0229a2a8 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
};

extern int func_020e98d4(unsigned int argument0);
extern void func_020e9898(int unused0);
extern void FS_InitFile(void *file);
extern int FS_OpenFile(void *file, const char *path);
extern int FS_ReadFile(int, int, int);
extern int FS_CloseFile(int);
extern void DC_FlushRange(void *, unsigned int);
extern void func_02112ba8(void *, unsigned char, unsigned int);
extern void GX_LoadBGPltt(void *dst, int size, int value);
extern void func_02112ee8(unsigned int, unsigned int, unsigned int);
extern void func_02001e34(int, int);
extern void func_02001b44(int);
extern void func_02001b34(int);
extern int func_02001b60(void);
extern int _s32_div_f(int a, int b);
extern void G2x_SetBlendAlpha_(unsigned int a, unsigned int b, unsigned int c, int d, int e);
extern short FX_SinCosTable_[];

void func_ov147_0229a48c(int a, int b, int c);
void func_ov147_0229a468(void *a0, void *a1, void *a2);
void func_ov147_0229a440(int p0, int p1, int p2);
void func_ov147_0229a420(void *arg);
void func_ov147_0229a404(void *dst);
void func_ov147_0229a3e4(unsigned int a);
void func_ov147_0229a2d0(int *p0);
void func_ov147_0229a280(int *p);

void func_ov147_0229a630(int *p0, int p1)
{
    p0[3] = p1;
}

void func_ov147_0229a628(UnkStruct_0229a628 *p)
{
    p->unk_0C = 2;
}

int func_ov147_0229a614(void *r0)
{
    if (*(unsigned int *) ((char *) r0 + 8) == 2) {
        if (*(unsigned int *) ((char *) r0 + 4) == 0) {
            return 1;
        }
    }
    return 0;
}

void func_ov147_0229a608(unsigned char *p0)
{
    ((int *) p0)[4] = 0;
    ((int *) p0)[5] = 0;
    p0[0x1c] = 0;
}

int func_ov147_0229a594(struct UnkStruct_0229a594 *self)
{
    int cond;
    int result;

    cond = (self->unk_0C == 2) ? 1 : 0;
    if (cond != 0) {
        self->unk_1C = 1;
        self->unk_14 = 0;
    }
    if (self->unk_1C != 0) {
        self->unk_10--;
        if (self->unk_10 <= 0) {
            self->unk_1C = 0;
        }
    } else {
        self->unk_10++;
        if (self->unk_10 >= 10) {
            self->unk_10 = 10;
            self->unk_14++;
            if (self->unk_14 > 5) {
                self->unk_1C = 1;
                self->unk_14 = 0;
            }
        }
    }
    result = 0;
    if (self->unk_10 > 0) {
        // result stays 0
    } else if (cond != 0) {
        result = 1;
    } else if (self->unk_08 != self->unk_0C) {
        result = 1;
    }
    return result;
}

int func_ov147_0229a58c(unsigned int argument0)
{
    return func_020e98d4(argument0);
}

void func_ov147_0229a578(int param)
{
    if (param != 0) {
        func_020e9898(param);
    }
}

void func_ov147_0229a4b4(int idx)
{

    char path1[28] = "/a_mes/a_mes_ttl_bg_ncg.bin";
    const char *tbl[2] = {"/a_mes/a_mes_ttl_a0_bg_nsc.bin", "/a_mes/a_mes_ttl_b0_bg_nsc.bin"};
    char path2[28] = "/a_mes/a_mes_ttl_bg_ncl.bin";
    FSFile file;

    void *p;

    FS_InitFile(&file);

    p = (void *) func_ov147_0229a58c(0x9e0);
    if (p != 0) {
        func_ov147_0229a48c((int) (&file), (int) path1, (int) p);
        func_ov147_0229a420(p);
        func_ov147_0229a578((int) p);
    }
    p = (void *) func_ov147_0229a58c(0x20);
    if (p != 0) {
        func_ov147_0229a468(&file, (void *) path2, p);
        func_ov147_0229a404(p);
        func_ov147_0229a578((int) p);
    }
    p = (void *) func_ov147_0229a58c(0x800);
    if (p != 0) {
        func_ov147_0229a440((int) (&file), (int) tbl[idx], (int) p);
        func_ov147_0229a3e4((unsigned int) p);
        func_ov147_0229a578((int) p);
    }
}

void func_ov147_0229a48c(int a, int b, int c)
{
    FS_OpenFile((void *) a, (const char *) b);
    FS_ReadFile(a, c, 0x9e0);
    FS_CloseFile(a);
}

void func_ov147_0229a468(void *a0, void *a1, void *a2)
{
    FS_OpenFile((void *) a0, (const char *) a1);
    FS_ReadFile((int) a0, (int) a2, 0x20);
    FS_CloseFile((int) a0);
}

void func_ov147_0229a440(int p0, int p1, int p2)
{
    FS_OpenFile((void *) p0, (const char *) p1);
    FS_ReadFile(p0, p2, 0x800);
    FS_CloseFile(p0);
}

void func_ov147_0229a420(void *arg)
{
    DC_FlushRange(arg, 0x9e0);
    func_02112ba8(arg, 0, 0x9e0);
}

void func_ov147_0229a404(void *dst)
{
    DC_FlushRange(dst, 0x20);
    GX_LoadBGPltt(dst, 0x20, 0x20);
}

void func_ov147_0229a3e4(unsigned int a)
{
    DC_FlushRange((void *) a, 0x800);
    func_02112ee8(a, 0, 0x800);
}

void func_ov147_0229a3ac(void)
{
    volatile unsigned short *reg = (volatile unsigned short *) 0x0400000e;
    unsigned short val;

    val = *reg;
    val = (unsigned short) ((val & ~(unsigned short) 3) | 1);
    *reg = val;

    val = *reg;
    val = (unsigned short) ((val & 0x43) | 0x700);
    *reg = val;

    val = *reg;
    val = (unsigned short) (val & ~(unsigned short) 0x40);
    *reg = val;

    func_02001e34(0, 0);
}

void func_ov147_0229a3a0(void)
{
    func_02001b44(8);
}

void func_ov147_0229a374(void)
{
    unsigned int v;
    unsigned int *p;
    int val;

    val = ((void) (func_02001b34(8)), func_02001b60());
    p = (unsigned int *) 0x04000000;
    v = *p & 0xffffe0ff;
    v |= (val << 8);
    *p = v;
}

void func_ov147_0229a31c(void *self)
{
    int x;
    short v;
    int w;

    x = _s32_div_f(((unsigned int *) self)[4] << 12, 10);
    x = ((unsigned short) ((x << 18) >> 16)) >> 4;
    v = FX_SinCosTable_[x * 2];
    w = ((v << 4) + 0x800) >> 12;
    if (w < 0) {
        w = 0;
    } else if (w > 16) {
        w = 16;
    }
    G2x_SetBlendAlpha_(0x04000050, 8, 0x21, w, 16 - w);
}

void func_ov147_0229a300(void *object)
{
    int local;
    local = 0;
    G2x_SetBlendAlpha_(0x04000050, 0, 0x20, 0x10, local);
}

void func_ov147_0229a2f4(int *p0)
{
    p0[1] = 0;
    p0[2] = 2;
}

void func_ov147_0229a2dc(unsigned int *r0)
{
    unsigned int r1;

    r1 = r0[3];
    if (r1 != 2) {
        r0[2] = r1;
        func_ov147_0229a2d0((int *) r0);
    }
}

void func_ov147_0229a2d0(int *p0)
{
    p0[1] = 1;
    p0[6] = 5;
}

void func_ov147_0229a2a8(struct UnkStruct_0229a2a8 *s)
{
    if (s->unk_08 != s->unk_0C) {
        func_ov147_0229a2f4((int *) s);
    } else {
        s->unk_18--;
        if (s->unk_18 > 0) {
            // do nothing
        } else {
            func_ov147_0229a280((int *) s);
        }
    }
}

void func_ov147_0229a280(int *p)
{
    p[1] = 2;
    func_ov147_0229a608((unsigned char *) p);
    func_ov147_0229a3ac();
    func_ov147_0229a4b4(p[2]);
    func_ov147_0229a3a0();
    func_ov147_0229a31c((void *) p);
}

void func_ov147_0229a250(int *arg)
{
    int r = func_ov147_0229a594((struct UnkStruct_0229a594 *) arg);
    func_ov147_0229a31c(arg);
    if (r != 0) {
        func_ov147_0229a300(arg);
        func_ov147_0229a374();
        func_ov147_0229a2f4(arg);
    }
}
