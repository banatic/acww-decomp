/* talk_box_3: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02069128 @ 0x02069128, 0x3e bytes, Thumb
 * func_02069100 @ 0x02069100, 0x28 bytes, Thumb
 * func_020690ec @ 0x020690ec, 0x14 bytes, Thumb
 * func_020690d8 @ 0x020690d8, 0x14 bytes, Thumb
 * func_02069068 @ 0x02069068, 0x70 bytes, Thumb
 * func_02069004 @ 0x02069004, 0x64 bytes, Thumb
 * func_02068fa0 @ 0x02068fa0, 0x64 bytes, Thumb
 * func_02068f2c @ 0x02068f2c, 0x74 bytes, Thumb
 * func_02068ee4 @ 0x02068ee4, 0x48 bytes, Thumb
 * func_02068e78 @ 0x02068e78, 0x6c bytes, Thumb
 * func_02068e44 @ 0x02068e44, 0x34 bytes, Thumb
 * func_02068e04 @ 0x02068e04, 0x40 bytes, Thumb
 * func_02068db0 @ 0x02068db0, 0x54 bytes, Thumb
 * func_02068d98 @ 0x02068d98, 0x16 bytes, Thumb
 * func_02068d80 @ 0x02068d80, 0x16 bytes, Thumb
 * func_02068d74 @ 0x02068d74, 0xc bytes, Thumb
 * func_02068d44 @ 0x02068d44, 0x30 bytes, Thumb
 * func_02068d38 @ 0x02068d38, 0xc bytes, Thumb
 * func_02068d2c @ 0x02068d2c, 0xc bytes, Thumb
 * func_02068d20 @ 0x02068d20, 0xc bytes, Thumb
 * func_02068d14 @ 0x02068d14, 0xc bytes, Thumb
 */

typedef struct UnkStruct_02069128 {
    int a;
    int b;
    int c;
    char subA[0x44];
    char subB[0x24];
    int unk_74;
    int g;
    int h;
} UnkStruct_02069128;

typedef struct {
    char pad_00[0xc];
    char unk_0C;
    char pad_0D[0x43];
    char unk_50;
} UnkStruct_02069100;

typedef struct {
    int pad_00;
    int unk_04;
} UnkStruct_02069004;

typedef struct {
    char pad_00[8];
    int unk_08;
} UnkStruct_02068fa0;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_02068db0;

typedef struct {
    unsigned char pad_00[0x74];
    int unk_74;
    int unk_78;
} UnkStruct_02068d44;

extern void *func_0208a448(char *p, int arg);
extern void *func_0208fd88(char *p);
extern void func_0208a2b0(char *p);
extern void func_0208fc04(char *p);
extern void func_0208fc00(void *);
extern void *func_0208fd68(void *);
extern void *func_0208a41c(void *);
extern void func_02068cf0(int arg);
extern void func_02068be4(int arg);
extern void func_02068cdc(void *arg);
extern int func_02068bd8(void *arg);
extern int FS_OpenFile(const void *src, const void *data);
extern int FS_ReadFile(const void *src, void *dst, int size);
extern int FS_CloseFile(const void *src);
extern unsigned char data_020df100[];
extern unsigned char data_020df11c[];
extern int func_020e98d4(int);
extern unsigned char data_020df0e8[];
extern int data_020df0d0;
extern const unsigned char data_020cce90[];
extern void FS_InitFile(void *);
extern void func_020e9898(void *ptr);
extern void func_02001da0(int);
extern void func_02001d1c(int);
extern void DC_FlushRange(unsigned int param1, unsigned int param2);
extern void GX_LoadBGPltt(unsigned int param1, unsigned int param2, unsigned int param3);
extern void GX_LoadBG2Char(unsigned int param1, unsigned int param2, unsigned int param3);
extern void GX_LoadBG2Scr(unsigned int param1, unsigned int param2, unsigned int param3);
extern void func_02001b44(int);
extern void func_02001bb4(int);
extern void func_02001b34(int);
extern void func_02001ba4(int);
extern void func_02001e54(int a, int b);
extern void func_02001cc4(int a, int b, int c, int d);
extern void func_0208a238(void *p, int x);

void func_02068e44(void *param);
void func_02068d44(UnkStruct_02068d44 *s, int a, int b);

UnkStruct_02069128 *func_02069128(UnkStruct_02069128 *p)
{
    p->a = 0;
    p->b = 0;
    p->c = 0;
    func_0208a448(p->subA, 1);
    func_0208fd88(p->subB);
    p->unk_74 = 0;
    p->g = 0;
    p->h = 0;
    func_0208a2b0(p->subA);
    func_0208fc04(p->subB);
    return p;
}

void *func_02069100(UnkStruct_02069100 *self)
{
    func_0208fc00(&self->unk_50);
    func_02068e44(self);
    func_0208fd68(&self->unk_50);
    func_0208a41c(&self->unk_0C);
    return self;
}

void func_020690ec(int arg)
{
    func_02068cf0(arg);
    func_02068be4(arg);
}

void func_020690d8(void *arg)
{
    func_02068cdc(arg);
    func_02068bd8(arg);
}

int func_02069068(void **out, const void *src, int flag)
{
    const void *addr;
    int result1;
    int flag3;
    int result4;

    if (flag) {
        addr = (const void *) data_020df100;
    } else {
        addr = (const void *) data_020df11c;
    }

    result1 = FS_OpenFile(src, addr);
    *out = (void *) func_020e98d4(0x800);

    if (*out != 0) {
        if (FS_ReadFile(src, *out, 0x800) == -1) {
            flag3 = 0;
        } else {
            flag3 = 1;
        }
    } else {
        flag3 = 0;
    }

    result4 = FS_CloseFile(src);

    if (result1 != 0 && flag3 != 0 && result4 != 0 && *out != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_02069004(UnkStruct_02069004 *s, int param1)
{
    int v6;
    int flag;
    int v4;

    v6 = FS_OpenFile((const void *) param1, (const void *) ((void *) data_020df0e8));
    s->unk_04 = func_020e98d4(0x180);
    if (s->unk_04 != 0) {
        int ret = FS_ReadFile((const void *) param1, (void *) s->unk_04, 0x180);
        flag = 0;
        if (ret != -1) {
            flag = 1;
        }
    } else {
        flag = 0;
    }

    v4 = FS_CloseFile((const void *) param1);
    if (v6 != 0 && flag != 0 && v4 != 0 && s->unk_04 != 0) {
        return 1;
    }
    return 0;
}

int func_02068fa0(UnkStruct_02068fa0 *obj, void *arg1)
{
    int v6, v4, v0;

    v6 = FS_OpenFile((const void *) arg1, (const void *) (&data_020df0d0));
    obj->unk_08 = func_020e98d4(0x2800);
    if (obj->unk_08 != 0) {
        if (FS_ReadFile((const void *) arg1, (void *) obj->unk_08, 0x2800) != -1) {
            v4 = 1;
        } else {
            v4 = 0;
        }
    } else {
        v4 = 0;
    }
    v0 = FS_CloseFile((const void *) arg1);
    if (v6 != 0 && v4 != 0 && v0 != 0 && obj->unk_08 != 0) {
        return 1;
    }
    return 0;
}

extern void func_02068f2c(unsigned short **p, int a, int b)
{
    unsigned int mask;
    int y, x;
    unsigned short v;

    if (b) {
        mask = 0xb000;
    } else {
        if (a != 0) {
            goto L_mask2000;
        }
        mask = 0x1000;
        goto L_mask_end;
    L_mask2000:
        mask = 0x2000;
    L_mask_end:;
    }

    if (mask == 0x1000) {
        return;
    }

    for (y = 0xd; y <= 0x10; y++) {
        for (x = 3; x <= 0xe; x++) {
            v = *(*p + y * 32 + x);
            if ((v & 0xf000) == 0x1000) {
                *(*p + y * 32 + x) = (unsigned short) (v & 0xffff0fff) | mask;
            }
        }
    }
}

// O: inline (*pp + row*32)[col]
void func_02068ee4(unsigned short **pp, int index)
{
    int row = 15;
    int col;
    const unsigned char *p = data_020cce90 + index;

    for (; row <= 24; row++) {
        for (col = 1; col <= 30; col++) {
            unsigned short v = (*pp + row * 32)[col] & 0xffff0fff;
            (*pp + row * 32)[col] = v | ((unsigned) (p[0] << 28) >> 16);
        }
    }
}

int func_02068e78(int a, int b, int c, int d, unsigned char e)
{
    int saved_d;
    unsigned char buf[0x48];
    int ret = 0;
    int flag;

    saved_d = d;
    flag = (c == 0 && b == 0);

    FS_InitFile(buf);
    if (func_02069068((void **) a, (const void *) buf, flag) == 0) {
        goto fail;
    }
    if (func_02069004((UnkStruct_02069004 *) a, (int) buf) == 0) {
        goto fail;
    }
    if (func_02068fa0((UnkStruct_02068fa0 *) a, buf) == 0) {
        goto fail;
    }

    if (flag) {
        func_02068f2c((unsigned short **) a, saved_d, (unsigned char) e);
    } else {
        func_02068ee4((unsigned short **) a, b);
    }

    ret = 1;

fail:
    return ret;
}

void func_02068e44(void *param)
{
    void *ptr;
    void *ptr2;
    void *ptr3;

    ptr = *(void **) param;
    if (ptr != 0) {
        func_020e9898(ptr);
        *(void **) param = 0;
    }

    ptr2 = *(void **) ((char *) param + 4);
    if (ptr2 != 0) {
        func_020e9898(ptr2);
        *(void **) ((char *) param + 4) = 0;
    }

    ptr3 = *(void **) ((char *) param + 8);
    if (ptr3 != 0) {
        func_020e9898(ptr3);
        *(void **) ((char *) param + 8) = 0;
    }
}

void func_02068e04(void)
{
    volatile unsigned short *reg = (volatile unsigned short *) 0x0400000c;
    unsigned int v;

    v = *reg;
    v &= ~3;
    v |= 1;
    *reg = (unsigned short) v;

    v = *reg;
    v &= 0x43;
    v |= 0x600;
    *reg = (unsigned short) v;

    v = *reg;
    v &= ~0x40;
    *reg = (unsigned short) v;

    func_02001da0(0x1f);
    func_02001d1c(0x1b);
}

void func_02068db0(UnkStruct_02068db0 *p)
{
    unsigned int v;
    v = p->unk_04;
    DC_FlushRange(v + 2, 0x17e);
    GX_LoadBGPltt(v + 2, 2, 0x17e);
    DC_FlushRange(p->unk_08, 0x2800);
    GX_LoadBG2Char(p->unk_08, 0, 0x2800);
    DC_FlushRange(p->unk_00, 0x800);
    GX_LoadBG2Scr(p->unk_00, 0, 0x800);
}

void func_02068d98(void)
{
    func_02001b44(4);
    func_02001bb4(1);
}

void func_02068d80(void *object)
{
    func_02001b34(4);
    func_02001ba4(1);
}

void func_02068d74(int a, int b)
{
    func_02068d44((UnkStruct_02068d44 *) a, 0, b);
}

void func_02068d44(UnkStruct_02068d44 *s, int a, int b)
{
    int val, val2;
    s->unk_74 = a;
    s->unk_78 = b;
    func_02001e54(a, b);
    val = 255 - a;
    val2 = -a;
    if (val2 < 0) {
        val2 = 0;
    }
    if (val > 255) {
        val = 255;
    }
    func_02001cc4(val2, 60, val, 192);
}

void func_02068d38(void *p)
{
    func_0208a238((char *) p + 0xc, 0);
}

void func_02068d2c(unsigned char *param)
{
    func_0208a238((void *) (param + 12), 1);
}

void func_02068d20(char *ptr)
{
    func_0208a238((void *) (ptr + 12), 2);
}

void func_02068d14(void *ptr)
{
    func_0208a238((char *) ptr + 0xc, 3);
}
