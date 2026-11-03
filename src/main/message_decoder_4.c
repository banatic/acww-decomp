/* message_decoder_4: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b5174 @ 0x020b5174, 0x6 bytes, Thumb
 * func_020b512c @ 0x020b512c, 0x48 bytes, Thumb
 * func_020b50e0 @ 0x020b50e0, 0x4c bytes, Thumb
 * func_020b5074 @ 0x020b5074, 0x6c bytes, Thumb
 * func_020b500c @ 0x020b500c, 0x68 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[69];
    unsigned char unk_45;
} UnkStruct_020b5174;

typedef struct {
    unsigned char pad_00[0x24];
    signed char *base;
    unsigned char pad_28[0x3c - 0x28];
    int unk_3C;
    int count;
    unsigned char flag44;
    unsigned char flag45;
} UnkStruct_020b512c;

typedef struct {
    char pad_00[0x24];
    unsigned int unk_24;
    char pad_28[8];
    unsigned int unk_30;
    char pad_34[4];
    signed char *unk_38;
    char pad_3C[4];
    unsigned int unk_40;
    char pad_44[1];
    unsigned char unk_45;
} UnkStruct_020b50e0;

typedef struct {
    char pad_00[0x24];
    char *unk_24;
    char unk_28[8];
    unsigned int unk_30;
    char pad_34[0x0c];
    unsigned int unk_40;
    char pad_44;
    char unk_45;
} UnkStruct_020b5074;

typedef struct UnkStruct_020b500c {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[0x14];
    int unk_3C;
    char pad_40[0x4];
    unsigned char unk_44;
    unsigned char unk_45;
    unsigned char unk_46;
    unsigned char unk_47;
    unsigned char unk_48;
} UnkStruct_020b500c;

extern void func_020a8328(void *a, unsigned int *b, int *c, signed char **d);
extern void func_020a93e8(void *a, unsigned int b);
extern int func_020a7c98(int, int);
extern int func_02050bdc_unk(int, int);
extern int func_020b4d70(int);

unsigned char func_020b5174(UnkStruct_020b5174 *p)
{
    return p->unk_45;
}

void func_020b512c(UnkStruct_020b512c *self)
{
    int f = self->unk_3C;
    signed char b0 = (signed char) (f & 0xff);
    signed char b1 = (signed char) ((f >> 8) & 0xff);
    int count = self->count;

    if ((unsigned int) (0xa00 - count) > 2) {
        self->count = count + 1;
        *(self->base + count + 0xafc) = b0;
        count = self->count;
        self->count = count + 1;
        *(self->base + count + 0xafc) = b1;
    } else {
        self->flag45 = 0;
    }
}

void func_020b50e0(UnkStruct_020b50e0 *s)
{
    signed char *src;
    unsigned int needed;
    unsigned int i;

    src = s->unk_38;
    needed = s->unk_30 + 6;

    if (0xa00 - s->unk_40 > needed) {
        for (i = 0; i < needed; i++) {
            *((char *) s->unk_24 + s->unk_40 + i + 0xafc) = src[i];
        }
        s->unk_40 += needed;
    } else {
        s->unk_45 = 0;
    }
}

void func_020b5074(UnkStruct_020b5074 *self)
{
    unsigned int v0;
    int v1;
    signed char *v2;
    unsigned int r4;
    int r6;

    func_020a8328(&self->unk_28, &v0, &v1, &v2);

    r4 = self->unk_30 - 1;
    r6 = ((0xA00 - self->unk_40) > r4);

    func_020a93e8(self, v0 << 1);

    if (r6) {
        unsigned int i;
        for (i = 0; i < r4; i++) {
            char *p = self->unk_24 + self->unk_40 + i;
            p[0xafc] = v2[i];
        }
        self->unk_40 += r4;
    } else {
        self->unk_45 = 0;
    }
}

void func_020b500c(UnkStruct_020b500c *p)
{
    unsigned char flag47;
    unsigned char flag48;
    void *obj;
    void **vt;
    int (*method)(void *);
    int v;

    flag47 = ((unsigned char *) p)[0x47];
    if (flag47 != 0) {
        obj = *(void **) ((char *) p->unk_24 + 0x18f0);
        vt = *(void ***) obj;
        method = ((int (**)(void *)) vt)[3];
        v = func_020a7c98(method(obj), 0);
        flag48 = ((unsigned char *) p)[0x48];
        if (flag48 != 0) {
            v = func_02050bdc_unk(v, flag48);
            ((unsigned char *) p)[0x48] = 0;
        }
        if (func_020b4d70(v) != 0) {
            p->unk_3C = v;
            func_020b512c((UnkStruct_020b512c *) p);
            ((unsigned char *) p)[0x44] = 1;
        } else {
            ((unsigned char *) p)[0x45] = 0;
        }
    }
}
