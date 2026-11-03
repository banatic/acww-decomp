/* sky_shots_3: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bec04 @ 0x020bec04, 0x10 bytes, Thumb
 * func_020bebec @ 0x020bebec, 0x16 bytes, Thumb
 * func_020bebd8 @ 0x020bebd8, 0x12 bytes, Thumb
 * func_020bebc8 @ 0x020bebc8, 0x10 bytes, Thumb
 * func_020beba4 @ 0x020beba4, 0x22 bytes, Thumb
 * func_020beb98 @ 0x020beb98, 0xc bytes, Thumb
 * func_020beb78 @ 0x020beb78, 0x20 bytes, Thumb
 * func_020beb64 @ 0x020beb64, 0x14 bytes, Thumb
 * func_020beb48 @ 0x020beb48, 0x1c bytes, Thumb
 * func_020beb3c @ 0x020beb3c, 0xa bytes, Thumb
 * func_020beb20 @ 0x020beb20, 0x1c bytes, Thumb
 * func_020beb14 @ 0x020beb14, 0xa bytes, Thumb
 * func_020beb00 @ 0x020beb00, 0x14 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned char unk_10;
    unsigned char unk_11;
} Dest;

typedef struct {
    int unk_00;
    int word1;
    int word2;
} Src;

struct unknown_s {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned char unk_10;
    unsigned char unk_11;
};

struct UnkStruct_020beb64 {
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char pad_0C[18];
    unsigned char unk_1E;
    unsigned char unk_1F;
    unsigned char unk_20;
};

typedef struct {
    int unk_00;
    void *unk_04;
} UnkStruct_020beb48;

typedef struct {
    unsigned char pad_00[12];
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned char unk_18;
} S_020beb00;

extern void func_020be758(void *arg);
extern int func_020952ec(void);
extern int func_ov003_022197c4(int arg, int);
extern void func_020be9f8(void);

void func_020bebd8(struct unknown_s *s);

void *func_020bec04(void *p)
{
    func_020bebd8((struct unknown_s *) p);
    return p;
}

void func_020bebec(Dest *dst, int val, Src *src, unsigned char byte)
{
    dst->unk_00 = val;
    dst->unk_04 = src->unk_00;
    dst->unk_08 = src->word1;
    dst->unk_0C = src->word2;
    dst->unk_10 = byte;
    dst->unk_11 = 1;
}

void func_020bebd8(struct unknown_s *s)
{
    s->unk_00 = 4;
    s->unk_04 = 0;
    s->unk_08 = 0;
    s->unk_0C = 0;
    s->unk_10 = 0;
    s->unk_11 = 0;
}

void *func_020bebc8(void *arg)
{
    func_020be758(arg);
    return arg;
}

void func_020beba4(int *r5, int r4)
{
    int r0;

    r0 = func_020952ec();
    if (r4 == r0) {
        r5[0] = 1;
        r5[1] = r4;
        r5[2] = 0x2b;
    }
}

void func_020beb98(int argument0, int argument1)
{
    func_ov003_022197c4(0, (int) argument1);
}

void func_020beb78(int param1, int param2)
{
    int *ptr;
    int local;

    ptr = (int *) param1;
    *(unsigned char *) (param1 + 0x21) = (unsigned char) param2;
    *ptr = 2;
    local = 1;
    func_ov003_022197c4(local, *(ptr + 1));
    func_020be9f8();
}

void func_020beb64(struct UnkStruct_020beb64 *p)
{
    p->unk_00 = 3;
    p->unk_08 = 2;
    p->unk_1E = 0;
    p->unk_1F = 0;
    p->unk_20 = 0;
}

void func_020beb48(UnkStruct_020beb48 *p)
{
    p->unk_00 = 4;
    func_ov003_022197c4(1, (int) p->unk_04);
    func_020be9f8();
}

void func_020beb3c(int *p)
{
    p[0] = 5;
    p[2] = 0x1e;
}

void func_020beb20(int *param)
{
    int local;
    *param = 7;
    local = 1;
    func_ov003_022197c4(local, param[1]);
    func_020be9f8();
}

void func_020beb14(int *p)
{
    p[0] = 8;
    p[2] = 0x14;
}

void func_020beb00(S_020beb00 *s, unsigned int a, unsigned int b, unsigned int c, unsigned char d)
{
    s->unk_0C = a;
    s->unk_10 = b;
    s->unk_14 = c;
    s->unk_18 = d;
}
