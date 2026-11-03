/* design_info: 24 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02072fcc @ 0x02072fcc, 0x76 bytes, Thumb
 * func_02072fbc @ 0x02072fbc, 0x10 bytes, Thumb
 * func_02072fac @ 0x02072fac, 0x10 bytes, Thumb
 * func_02072f88 @ 0x02072f88, 0x22 bytes, Thumb
 * func_02072f74 @ 0x02072f74, 0x12 bytes, Thumb
 * func_02072f54 @ 0x02072f54, 0x1e bytes, Thumb
 * func_02072f38 @ 0x02072f38, 0x1a bytes, Thumb
 * func_02072eec @ 0x02072eec, 0x4a bytes, Thumb
 * func_02072ee8 @ 0x02072ee8, 0x2 bytes, Thumb
 * func_02072eb8 @ 0x02072eb8, 0x30 bytes, Thumb
 * func_02072ea4 @ 0x02072ea4, 0x14 bytes, Thumb
 * func_02072e90 @ 0x02072e90, 0x14 bytes, Thumb
 * func_02072e64 @ 0x02072e64, 0x2c bytes, Thumb
 * func_02072e50 @ 0x02072e50, 0x14 bytes, Thumb
 * func_02072e3c @ 0x02072e3c, 0x14 bytes, Thumb
 * func_02072e30 @ 0x02072e30, 0xa bytes, Thumb
 * func_02072e18 @ 0x02072e18, 0x18 bytes, Thumb
 * func_02072dd4 @ 0x02072dd4, 0x44 bytes, Thumb
 * func_02072dbc @ 0x02072dbc, 0x18 bytes, Thumb
 * func_02072da4 @ 0x02072da4, 0x18 bytes, Thumb
 * func_02072da0 @ 0x02072da0, 0x2 bytes, Thumb
 * func_02072d84 @ 0x02072d84, 0x1c bytes, Thumb
 * func_02072d58 @ 0x02072d58, 0x2c bytes, Thumb
 * func_02072d4c @ 0x02072d4c, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char low : 4;
    unsigned char high : 4;
} Nibble02072fcc;

typedef struct {
    unsigned short unk_00;
    unsigned char data[12];
    unsigned char pad_0E[0x10];
    unsigned short arr[10];
    Nibble02072fcc ver;
} Struct02072fcc;

struct BitField {
    unsigned char low : 4;
    unsigned char high : 4;
};

struct UnkStruct_02072f74 {
    unsigned char pad_00[0x32];
    struct BitField bits;
};

typedef struct {
    unsigned short v[6];
} UnkStruct_02072eec;

typedef struct {
    unsigned short unk_00;
    UnkStruct_02072eec a1;
    unsigned short unk_0E;
    UnkStruct_02072eec a2;
    signed char unk_1C;
    unsigned char unk_1D;
} UnkStruct_02072eec_2;

typedef struct {
    unsigned short data[10];
} Block;

typedef struct {
    unsigned short head[15];
    Block block;
} Record;

typedef struct {
    unsigned char pad_00[0x32];
    unsigned char lo : 4;
    unsigned char hi : 4;
} UnkStruct_02072e30;

extern int memcmp(const void *a, const void *b, unsigned int n);
extern int func_0209518c(Struct02072fcc *a, Struct02072fcc *b);
extern void *func_0209529c(int);
extern int func_0209526c(int arg);
extern int func_02072614(void);
extern int func_0207261c(int, int);
extern int func_020984e8(void);
extern int func_02099870(int);
extern void *func_02062e50(void *);
extern int func_020a8a70(void *, void *, int, int);
extern void *func_02062e00(void *);
extern void func_020a8874(void *a, void *b, int c);
extern int func_020a87e0(void *, void *);
extern int func_02062da4(void *dst, const void *src, unsigned int size);
extern void MI_CpuCopy8(int, int, int);

unsigned char func_02072f74(struct UnkStruct_02072f74 *o);
void func_02072eec(UnkStruct_02072eec_2 *d, UnkStruct_02072eec_2 *s);
void func_02072ea4(char *a, void *b);
void func_02072e50(void *a, void *b);

int func_02072fcc(Struct02072fcc *a, Struct02072fcc *b)
{
    unsigned int i;

    if (a->ver.low != b->ver.low) {
        goto fail;
    }
    if (a->ver.high != b->ver.high) {
        goto fail;
    }
    if (a->unk_00 != b->unk_00) {
        goto fail;
    }
    if (memcmp(a->data, b->data, 12) != 0) {
        goto fail;
    }
    if (func_0209518c(a, b) == 0) {
        goto fail;
    }

    for (i = 0; i < 10; i++) {
        if (a->arr[i] != b->arr[i]) {
            return 0;
        }
    }

    return 1;
fail:
    return 0;
}

int func_02072fbc(int param)
{
    func_0209529c(param);
    return param;
}

int func_02072fac(int arg)
{
    func_0209526c(arg);
    return arg;
}

int func_02072f88(int arg0)
{
    int local_0;
    int r4;
    int r5;
    int result;

    r5 = arg0;
    r4 = func_02072614();
    result = (int) func_02072f74((struct UnkStruct_02072f74 *) r5);
    result = func_0207261c(r4, result);
    return result;
}

unsigned char func_02072f74(struct UnkStruct_02072f74 *o)
{
    return (unsigned char) (o->bits.high & 0xF);
}

void func_02072f54(int a, int b)
{
    unsigned char temp = (unsigned char) (b & 0x0F);
    *((unsigned char *) (a + 0x32)) = (*((unsigned char *) (a + 0x32)) & ~0xF0) | ((temp & 0x0F) << 4);
}

void func_02072f38(int a)
{
    int b;
    b = func_02099870((int) func_020984e8());
    func_02072eec((UnkStruct_02072eec_2 *) a, (UnkStruct_02072eec_2 *) b);
}

void func_02072eec(UnkStruct_02072eec_2 *d, UnkStruct_02072eec_2 *s)
{
    d->unk_00 = s->unk_00;
    d->a1 = s->a1;
    d->unk_0E = s->unk_0E;
    d->a2 = s->a2;
    d->unk_1C = s->unk_1C;
    d->unk_1D = s->unk_1D;
}

void *func_02072ee8(void *record)
{
    return record;
}

void func_02072eb8(void *param0, void *param1)
{
    void *sp[9]; // 0x24 bytes

    func_02062e50(sp);
    func_02072ea4((char *) param0, sp);
    func_020a8a70(param1, sp, 0, 0);
    func_02062e00(sp);
}

void func_02072ea4(char *a, void *b)
{
    func_020a8874(b, a + 0x1e, 10);
}

void func_02072e90(Record *src, Block *dst)
{
    *dst = src->block;
}

void func_02072e64(void *param1, void *param2)
{
    void *sp_buffer[9]; // 0x24 bytes

    func_02062e50(sp_buffer);
    func_020a87e0(sp_buffer, param2);
    func_02072e50(param1, sp_buffer);
    func_02062e00(sp_buffer);
}

void func_02072e50(void *a, void *b)
{
    func_02062da4(b, (char *) a + 0x1e, 0xa);
}

void func_02072e3c(Record *dst, Block *src)
{
    dst->block = *src;
}

int func_02072e30(UnkStruct_02072e30 *p)
{
    return p->lo;
}

void func_02072e18(unsigned char *buf, int val)
{
    buf[0x32] = (buf[0x32] & ~0xF) | ((unsigned char) val & 0x0F);
}

int func_02072dd4(char *a, char *b)
{
    unsigned int i;
    if (func_02072fcc((Struct02072fcc *) (a + 0x200), (Struct02072fcc *) (b + 0x200)) != 0) {
        for (i = 0; i < 0x80; i++) {
            if (*(int *) a != *(int *) b) {
                return 0;
            }
            a += 4;
            b += 4;
        }
        return 1;
    }
    return 0;
}

char *func_02072dbc(char *p)
{
    func_02072fbc((int) (p + 0x200));
    return p;
}

void *func_02072da4(void *p)
{
    func_02072fac((int) ((char *) p + 0x200));
    return p;
}

void *func_02072da0(void *object)
{
    return object;
}

void func_02072d84(int a, int b)
{
    MI_CpuCopy8(b, (int) func_02072da0((void *) a), 0x200);
}

void func_02072d58(unsigned int *dest, unsigned int value)
{
    unsigned int pattern = (unsigned char) (value | (value << 4));
    unsigned int word = (pattern << 24) | ((pattern << 16) | ((pattern << 8) | pattern));
    unsigned int *p = dest;
    unsigned int *end = (unsigned int *) ((unsigned char *) dest + 0x200);
    while (p < end) {
        *p++ = word;
    }
}

unsigned int func_02072d4c(unsigned int r0)
{
    return r0 + 0x200;
}
