/* save_stamp: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209fb70 @ 0x0209fb70, 0x2 bytes, Thumb
 * func_0209fb6c @ 0x0209fb6c, 0x2 bytes, Thumb
 * func_0209fb64 @ 0x0209fb64, 0x6 bytes, Thumb
 * func_0209fb5c @ 0x0209fb5c, 0x6 bytes, Thumb
 * func_0209fb54 @ 0x0209fb54, 0x6 bytes, Thumb
 * func_0209fb4c @ 0x0209fb4c, 0x6 bytes, Thumb
 * func_0209fb3c @ 0x0209fb3c, 0xe bytes, Thumb
 * func_0209fb28 @ 0x0209fb28, 0x12 bytes, Thumb
 * func_0209fafc @ 0x0209fafc, 0x2c bytes, Thumb
 * func_0209faf8 @ 0x0209faf8, 0x4 bytes, Thumb
 * func_0209faf4 @ 0x0209faf4, 0x4 bytes, Thumb
 * func_0209faf0 @ 0x0209faf0, 0x4 bytes, Thumb
 * func_0209faec @ 0x0209faec, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[2];
    unsigned char unk_02;
} UnkStruct_0209fb64;

typedef struct {
    unsigned char pad_00[2];
    unsigned char unk_02;
} UnkStruct_0209fb5c;

typedef struct {
    unsigned char pad_00[2];
    unsigned char unk_02;
} UnkStruct_0209fb54;

typedef struct {
    unsigned char pad_00[2];
    unsigned char unk_02;
} UnkStruct_0209fb4c;

struct UnkStruct_0209fb3c {
    unsigned char pad_00[2];
    unsigned char flag;
};

struct UnkStruct_0209fafc {
    char pad_00[3];
    unsigned char b;
};

extern int func_020644cc(int);

void func_0209fb70(void *self) {}

void func_0209fb6c(void *self) {}

void func_0209fb64(UnkStruct_0209fb64 *p)
{
    p->unk_02 = 2;
}

void func_0209fb5c(UnkStruct_0209fb5c *p)
{
    p->unk_02 = 0;
}

void func_0209fb54(UnkStruct_0209fb54 *p)
{
    p->unk_02 = 28;
}

void func_0209fb4c(UnkStruct_0209fb4c *p)
{
    p->unk_02 = 2;
}

int func_0209fb3c(struct UnkStruct_0209fb3c *s)
{
    if (s->flag == 2) {
        return 1;
    } else {
        return 0;
    }
}

int func_0209fb28(const unsigned char *p)
{
    if (p[2] == 2 || p[2] == 28) {
        return 0;
    }
    return 1;
}

void func_0209fafc(struct UnkStruct_0209fafc *p)
{
    unsigned char orig = p->b;
    p->b = func_020644cc(0xff);
    if (p->b == orig) {
        if (p->b < 0xff) {
            p->b++;
        } else {
            p->b--;
        }
    }
}

void func_0209faf8(unsigned char *p0, int p1)
{
    p0[3] = p1;
}

int func_0209faf4(unsigned char *p0)
{
    return p0[3];
}

void func_0209faf0(unsigned short *p0, int p1)
{
    p0[0] = p1;
}

int func_0209faec(unsigned short *p0)
{
    return p0[0];
}
