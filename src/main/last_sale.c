/* last_sale: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208725c @ 0x0208725c, 0x18 bytes, Thumb
 * func_0208724c @ 0x0208724c, 0x10 bytes, Thumb
 * func_02087234 @ 0x02087234, 0x18 bytes, Thumb
 * func_0208722c @ 0x0208722c, 0x8 bytes, Thumb
 * func_02087228 @ 0x02087228, 0x2 bytes, Thumb
 * func_020871dc @ 0x020871dc, 0x4a bytes, Thumb
 * func_020871d4 @ 0x020871d4, 0x6 bytes, Thumb
 * func_020871cc @ 0x020871cc, 0x6 bytes, Thumb
 */

typedef struct {
    char pad_00[0x1e];
    unsigned short unk_1E;
} UnkStruct_0208725c;

typedef struct Profile_02087228 {
    unsigned short profile[15];
    unsigned short item;
} Profile_02087228;

typedef struct {
    unsigned short v[6];
} UnkStruct_020871dc;

typedef struct {
    unsigned short unk_00;
    UnkStruct_020871dc a1;
    unsigned short unk_0E;
    UnkStruct_020871dc a2;
    signed char unk_1C;
    unsigned char unk_1D;
} UnkStruct_020871dc_2;

typedef struct {
    unsigned short f;
} UnkStruct_020871d4;

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned short f;
} UnkStruct_020871d4_2;

typedef struct {
    unsigned short f;
} UnkStruct_020871cc;

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned short f;
} UnkStruct_020871cc_2;

extern void *func_0209529c(void *ptr);
extern int func_0209526c(int arg);
extern void func_02095238(void *);

UnkStruct_0208725c *func_0208725c(UnkStruct_0208725c *arg)
{
    func_0209529c(arg);
    arg->unk_1E = 0xfff1;
    return arg;
}

int func_0208724c(int arg)
{
    int local = arg;
    func_0209526c(arg);
    return local;
}

void func_02087234(unsigned short *r4)
{
    unsigned short value;
    value = 0x0000fff1;
    func_02095238(r4);
    r4[0x0f] = value;
}

void func_0208722c(unsigned short *argument0)
{
    func_02087234((unsigned short *) argument0);
}

unsigned short *func_02087228(Profile_02087228 *record)
{
    return record->profile;
}

void func_020871dc(UnkStruct_020871dc_2 *d, UnkStruct_020871dc_2 *s)
{
    d->unk_00 = s->unk_00;
    d->a1 = s->a1;
    d->unk_0E = s->unk_0E;
    d->a2 = s->a2;
    d->unk_1C = s->unk_1C;
    d->unk_1D = s->unk_1D;
}

void func_020871d4(UnkStruct_020871d4_2 *dst, UnkStruct_020871d4 *src)
{
    dst->f = src->f;
}

void func_020871cc(UnkStruct_020871cc *dst, UnkStruct_020871cc_2 *src)
{
    dst->f = src->f;
}
