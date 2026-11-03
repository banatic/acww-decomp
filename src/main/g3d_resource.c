/* g3d_resource: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02057b08 @ 0x02057b08, 0x2c bytes, Thumb
 * func_02057ac0 @ 0x02057ac0, 0x48 bytes, Thumb
 * func_02057a98 @ 0x02057a98, 0x26 bytes, Thumb
 * func_02057a8c @ 0x02057a8c, 0xc bytes, Thumb
 * func_02057a7c @ 0x02057a7c, 0x10 bytes, Thumb
 * func_02057a60 @ 0x02057a60, 0x1c bytes, Thumb
 * func_02057a50 @ 0x02057a50, 0x10 bytes, Thumb
 * func_02057a4c @ 0x02057a4c, 0x4 bytes, Thumb
 * func_02057a40 @ 0x02057a40, 0xc bytes, Thumb
 * func_02057a20 @ 0x02057a20, 0x1e bytes, Thumb
 * func_020579f0 @ 0x020579f0, 0x30 bytes, Thumb
 * func_020579c4 @ 0x020579c4, 0x2c bytes, Thumb
 * func_020579b8 @ 0x020579b8, 0xc bytes, Thumb
 * func_02057988 @ 0x02057988, 0x30 bytes, Thumb
 * func_02057970 @ 0x02057970, 0x16 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02057a50;

typedef struct {
    char pad_00[0x34];
    unsigned short unk_34;
} UnkStruct_020579b8;

extern unsigned short data_020dd19c[];
extern __arm unsigned char *strcpy(void *dst, const char *src);
extern __arm int NNS_G3dGetResDictIdxByName(void *arg, void *buf);

void *func_020579f0(unsigned char *b, int k);

int func_02057b08(unsigned int param)
{
    return data_020dd19c[(param & 0x00700000) >> 20] * data_020dd19c[(param & 0x03800000) >> 23];
}

unsigned int func_02057ac0(unsigned int arg)
{
    unsigned int result;

    result = (unsigned int) func_02057b08(arg);
    switch ((arg & 0x1c000000) >> 26) {
        case 2:
            result >>= 2;
            break;
        case 3:
            result >>= 1;
            break;
        case 5:
            result >>= 2;
            break;
        case 7:
            result <<= 1;
            break;
        default:
            break;
    }
    return result;
}

int func_02057a98(void *arg, const char *name)
{
    unsigned int buf[4];
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    strcpy(buf, name);
    return NNS_G3dGetResDictIdxByName(arg, buf);
}

unsigned int func_02057a8c(void *param)
{
    return func_02057ac0((unsigned int) (*(void **) ((char *) param + 0x14)));
}

unsigned int func_02057a7c(unsigned int *p)
{
    return (p[5] & 0xffff) << 3;
}

unsigned int func_02057a60(void *arg0)
{
    unsigned int val;
    unsigned short val2;
    unsigned int val3;

    val3 = *(unsigned int *) ((int) arg0 + 0x14) & 0x1c000000;
    if ((val3 >> 0x1a) == 2) {
        val2 = *(unsigned short *) ((int) arg0 + 0x1c);
        val = (unsigned int) val2 << 3;
    } else {
        val2 = *(unsigned short *) ((int) arg0 + 0x1c);
        val = (unsigned int) val2 << 4;
    }
    return val;
}

int func_02057a50(UnkStruct_02057a50 *p, const char *name)
{
    return func_02057a98((char *) p + p->unk_08 + 4, name);
}

int func_02057a4c(int *p0)
{
    return p0[5];
}

int func_02057a40(void *ptr, const char *name)
{
    return func_02057a98((char *) ptr + 0x3c, name);
}

void *func_02057a20(void *p0, int p1)
{
    int r = func_02057a40(p0, (const char *) p1);
    if (r == -1) {
        return 0;
    }
    return func_020579f0((unsigned char *) p0, r);
}

void *func_020579f0(unsigned char *b, int k)
{
    unsigned char *table = b + 0x3c;
    unsigned short off = *(unsigned short *) (b + 0x42);
    unsigned char *base = b + *(unsigned int *) (b + 0x14);
    unsigned short stride = *(unsigned short *) (table + off);
    unsigned char *entry = table + off + stride * k;
    unsigned int w = *(unsigned int *) (entry + 4);

    return base + ((w & 0xffff) << 3);
}

int func_020579c4(char *p, int n)
{
    char *q;
    unsigned short a;
    unsigned short b;
    if (n == (-1)) {
        return 0;
    }
    q = p + 60;
    a = *((unsigned short *) (p + 66));
    b = *((unsigned short *) (q + a));
    return (int) func_02057ac0(*((int *) (((q + a) + (b * n)) + 4)));
}

int func_020579b8(UnkStruct_020579b8 *self, const char *name)
{
    return func_02057a98((char *) self + self->unk_34, name);
}

char *func_02057988(char *p, int i)
{
    unsigned short h1;
    char *q;
    unsigned short h2;
    char *r;
    int offset;
    char *base;
    unsigned short val;
    char *addr;
    unsigned short f;

    if (i == -1) {
        return 0;
    }

    h1 = *(unsigned short *) (p + 0x34);
    q = p + h1;
    h2 = *(unsigned short *) (q + 6);
    r = q + h2;
    offset = *(int *) (p + 0x38);
    base = p + offset;
    val = *(unsigned short *) r;
    addr = r + (val * i);
    f = *(unsigned short *) (addr + 4);
    return base + (f << 3);
}

int func_02057970(int arg, const char *name)
{
    int tmp;
    tmp = func_020579b8((UnkStruct_020579b8 *) arg, name);
    return (int) func_02057988((char *) arg, tmp);
}
