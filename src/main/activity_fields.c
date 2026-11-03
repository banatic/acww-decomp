/* activity_fields: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a1284 @ 0x020a1284, 0x6 bytes, Thumb
 * func_020a127c @ 0x020a127c, 0x6 bytes, Thumb
 * func_020a1274 @ 0x020a1274, 0x6 bytes, Thumb
 * func_020a126c @ 0x020a126c, 0x6 bytes, Thumb
 * func_020a1264 @ 0x020a1264, 0x6 bytes, Thumb
 * func_020a125c @ 0x020a125c, 0x6 bytes, Thumb
 * func_020a1254 @ 0x020a1254, 0x6 bytes, Thumb
 * func_020a1250 @ 0x020a1250, 0x4 bytes, Thumb
 * func_020a1248 @ 0x020a1248, 0x8 bytes, Thumb
 * func_020a1240 @ 0x020a1240, 0x8 bytes, Thumb
 * func_020a1238 @ 0x020a1238, 0x8 bytes, Thumb
 * func_020a1224 @ 0x020a1224, 0x12 bytes, Thumb
 * func_020a1210 @ 0x020a1210, 0x14 bytes, Thumb
 * func_020a1208 @ 0x020a1208, 0x8 bytes, Thumb
 * func_020a1200 @ 0x020a1200, 0x8 bytes, Thumb
 * func_020a11f8 @ 0x020a11f8, 0x8 bytes, Thumb
 * func_020a11e0 @ 0x020a11e0, 0x18 bytes, Thumb
 * func_020a11c4 @ 0x020a11c4, 0x1c bytes, Thumb
 * func_020a11b8 @ 0x020a11b8, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[212];
    unsigned short unk_D4;
} UnkStruct_020a1284;

typedef struct {
    unsigned char pad_00[215];
    unsigned char unk_D7;
} UnkStruct_020a127c;

typedef struct {
    unsigned char pad_00[228];
    unsigned char unk_E4;
} UnkStruct_020a1274;

typedef struct {
    unsigned char pad_00[229];
    unsigned char unk_E5;
} UnkStruct_020a126c;

typedef struct {
    unsigned char pad_00[230];
    unsigned char unk_E6;
} UnkStruct_020a1264;

typedef struct {
    unsigned char pad_00[217];
    unsigned char unk_D9;
} UnkStruct_020a125c;

typedef struct {
    unsigned char pad_00[218];
    unsigned char unk_DA;
} UnkStruct_020a1254;

extern unsigned char *data_021f3c3c;

void func_020a1284(UnkStruct_020a1284 *p, unsigned short v)
{
    p->unk_D4 = v;
}

void func_020a127c(UnkStruct_020a127c *p, unsigned char v)
{
    p->unk_D7 = v;
}

void func_020a1274(UnkStruct_020a1274 *p, unsigned char v)
{
    p->unk_E4 = v;
}

void func_020a126c(UnkStruct_020a126c *p, unsigned char v)
{
    p->unk_E5 = v;
}

void func_020a1264(UnkStruct_020a1264 *p, unsigned char v)
{
    p->unk_E6 = v;
}

void func_020a125c(UnkStruct_020a125c *p, unsigned char v)
{
    p->unk_D9 = v;
}

void func_020a1254(UnkStruct_020a1254 *p, unsigned char v)
{
    p->unk_DA = v;
}

int func_020a1250(int p0)
{
    return ((int) (p0) + (220));
}

void func_020a1248(int p0, int p1, int p2)
{
    *(unsigned char *) ((char *) (((int) (((int) (p0) + (p1))) + (231))) + (0)) = p2;
}

void func_020a1240(int p0, int p1, int p2)
{
    *(unsigned char *) ((char *) (((int) (((int) (p0) + (p1))) + (235))) + (0)) = p2;
}

void func_020a1238(int p0, int p1, int p2)
{
    *(unsigned char *) ((char *) (((int) (((int) (p0) + (p1))) + (239))) + (0)) = p2;
}

void func_020a1224(char *base)
{
    int i = 3;
    do {
        *(base + i + 0xEF) = 0;
    } while (--i >= 0);
}

void func_020a1210(unsigned char r0)
{
    unsigned char *r1;

    r1 = data_021f3c3c;
    if (r1 != 0) {
        r1 += 0xf3;
        *r1 = r0;
    }
}

void func_020a1208(int p0, int p1, int p2)
{
    *(unsigned char *) ((char *) (((int) (((int) (p0) + (p1))) + (244))) + (0)) = p2;
}

void func_020a1200(int p0, int p1, int p2)
{
    *(unsigned char *) ((char *) (((int) (((int) (p0) + (p1))) + (248))) + (0)) = p2;
}

void func_020a11f8(int p0, int p1, int p2)
{
    *(unsigned char *) ((char *) (((int) (((int) (p0) + (p1))) + (252))) + (0)) = p2;
}

void func_020a11e0(unsigned char arg0)
{
    unsigned char *ptr;
    unsigned char *base;

    ptr = data_021f3c3c;
    if (ptr != 0) {
        base = ptr + 0x100;
        *base = arg0;
    }
}

int func_020a11c4(void)
{
    if (data_021f3c3c) {
        return data_021f3c3c[0x100];
    } else {
        return 4;
    }
}

void func_020a11b8(unsigned char *ptr, unsigned char value)
{
    ptr[0x101] = value;
}
