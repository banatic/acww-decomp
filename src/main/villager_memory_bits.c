/* villager_memory_bits: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02081974 @ 0x02081974, 0x14 bytes, Thumb
 * func_02081960 @ 0x02081960, 0x14 bytes, Thumb
 * func_0208194c @ 0x0208194c, 0x14 bytes, Thumb
 * func_02081938 @ 0x02081938, 0x14 bytes, Thumb
 * func_02081924 @ 0x02081924, 0x14 bytes, Thumb
 * func_02081910 @ 0x02081910, 0x14 bytes, Thumb
 * func_020818fc @ 0x020818fc, 0x14 bytes, Thumb
 * func_020818e8 @ 0x020818e8, 0x14 bytes, Thumb
 * func_020818d4 @ 0x020818d4, 0x14 bytes, Thumb
 * func_020818c0 @ 0x020818c0, 0x14 bytes, Thumb
 * func_020818ac @ 0x020818ac, 0x14 bytes, Thumb
 * func_02081898 @ 0x02081898, 0x14 bytes, Thumb
 * func_02081888 @ 0x02081888, 0x10 bytes, Thumb
 * func_02081878 @ 0x02081878, 0x10 bytes, Thumb
 * func_02081864 @ 0x02081864, 0x14 bytes, Thumb
 */

struct UnkStruct_0208194c {
    unsigned char pad_00[0x7c];
    unsigned short unk_7C;
};

struct UnkStruct_02081910 {
    char pad_00[0x7c];
    unsigned short unk_7C;
};

typedef struct {
    unsigned char pad_00[0x7c];
    unsigned short field0 : 13;
    unsigned short field1 : 1;
} UnkStruct_020818d4;

typedef struct {
    char pad_00[0x7C];
    unsigned short unk_7C;
} UnkStruct_02081898;

typedef struct {
    unsigned char pad_00[0x7c];
    unsigned short flags;
} UnkStruct_02081878;

typedef struct {
    unsigned char pad_00[0x7c];
    unsigned short : 5;
    unsigned short target : 1;
} UnkStruct_02081864;

void func_02081974(unsigned short *r0)
{
    unsigned short r2;
    unsigned short *r1;

    r1 = (unsigned short *) ((unsigned char *) r0 + 0x7c);
    r2 = *r1;
    r2 |= 0x0800;
    r0 = (unsigned short *) ((unsigned char *) r0 + 0x7c);
    *r0 = r2;
}

void func_02081960(unsigned short *param)
{
    unsigned short value;
    unsigned short *ptr;

    ptr = (unsigned short *) ((unsigned char *) param + 0x7c);
    value = *ptr;
    value &= 0xfffff7ff;
    *ptr = value;
}

int func_0208194c(struct UnkStruct_0208194c *arg)
{
    if ((((unsigned int) arg->unk_7C << 20) >> 31) == 0) {
        return 0;
    }
    return 1;
}

void func_02081938(unsigned short *arg0)
{
    unsigned short *ptr;
    unsigned short val;

    ptr = (unsigned short *) ((unsigned char *) arg0 + 0x7c);
    val = *ptr;
    val |= 0x1000;
    *ptr = val;
}

void func_02081924(unsigned short *p)
{
    *(unsigned short *) ((char *) p + 0x7c) &= 0xffffefff;
}

int func_02081910(struct UnkStruct_02081910 *arg)
{
    if ((((unsigned int) arg->unk_7C) << 19) >> 31) {
        return 1;
    } else {
        return 0;
    }
}

void func_020818fc(char *p)
{
    unsigned short tmp;
    tmp = *(unsigned short *) (p + 0x7c);
    tmp |= 0x2000;
    *(unsigned short *) (p + 0x7c) = tmp;
}

void func_020818e8(unsigned short *arg0)
{
    unsigned short *ptr;
    unsigned short val;
    unsigned int mask;

    ptr = (unsigned short *) ((unsigned char *) arg0 + 0x7c);
    val = *ptr;
    mask = 0xffffdfff;
    val = (unsigned short) (val & mask);
    *((unsigned short *) ((unsigned char *) arg0 + 0x7c)) = val;
}

unsigned int func_020818d4(UnkStruct_020818d4 *p)
{
    if (p->field1) {
        return 1;
    } else {
        return 0;
    }
}

void func_020818c0(unsigned short *param)
{
    unsigned short *ptr;
    unsigned short value;

    ptr = (unsigned short *) ((unsigned char *) param + 0x7c);
    value = *ptr;
    value |= 0x4000;
    *ptr = value;
}

void func_020818ac(unsigned short *param)
{
    unsigned short value;
    unsigned short *ptr;

    ptr = (unsigned short *) ((unsigned char *) param + 0x7c);
    value = *ptr;
    value &= 0xffffbfff;
    *ptr = value;
}

int func_02081898(UnkStruct_02081898 *p)
{
    if (((unsigned) p->unk_7C << 17) >> 31) {
        return 1;
    } else {
        return 0;
    }
}

void func_02081888(unsigned short *arg0)
{
    arg0[0x3e] |= 0x20;
}

void func_02081878(UnkStruct_02081878 *s)
{
    s->flags &= ~0x20;
}

int func_02081864(UnkStruct_02081864 *arg)
{
    return arg->target ? 1 : 0;
}
