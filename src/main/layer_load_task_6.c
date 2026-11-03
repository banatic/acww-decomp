/* layer_load_task_6: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ba108 @ 0x020ba108, 0x10 bytes, Thumb
 * func_020ba0f8 @ 0x020ba0f8, 0x10 bytes, Thumb
 * func_020ba0dc @ 0x020ba0dc, 0x1c bytes, Thumb
 * func_020ba0cc @ 0x020ba0cc, 0xe bytes, Thumb
 * func_020ba0c0 @ 0x020ba0c0, 0xc bytes, Thumb
 * func_020ba0a8 @ 0x020ba0a8, 0x18 bytes, Thumb
 * func_020ba0a4 @ 0x020ba0a4, 0x4 bytes, Thumb
 * func_020ba09c @ 0x020ba09c, 0x8 bytes, Thumb
 * func_020ba07c @ 0x020ba07c, 0x1e bytes, Thumb
 * func_020ba078 @ 0x020ba078, 0x4 bytes, Thumb
 * func_020ba064 @ 0x020ba064, 0x14 bytes, Thumb
 * func_020ba040 @ 0x020ba040, 0x24 bytes, Thumb
 * func_020ba03c @ 0x020ba03c, 0x4 bytes, Thumb
 */

typedef struct {
    int unk_00;
    unsigned char unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_020ba108;

struct UnkStruct_020ba0f8 {
    int unk_00;
    unsigned char unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
};

struct UnkStruct_020ba0dc {
    unsigned int unk_00;
    unsigned char unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
};

typedef struct {
    unsigned char pad_00[0xc];
    unsigned int unk_0C;
    unsigned int unk_10;
} UnkStruct_020ba0cc;

struct UnkStruct_020ba0c0 {
    int unk_00;
    char unk_04;
    int unk_08;
    int unk_0C;
};

struct UnkStruct_020ba0a8 {
    int a;
    unsigned char b;
    int c;
    int d;
};

typedef struct {
    int unk_00;
    unsigned char unk_04;
    unsigned char pad_05[3];
    int unk_08;
} UnkStruct_020ba09c;

struct UnkStruct_020ba07c {
    void *unk_00;
    unsigned char unk_04;
    unsigned int unk_08;
};

typedef struct {
    int a;
    unsigned char b;
    int c;
    int d;
} UnkStruct_020ba064;

typedef struct {
    int unk_00;
    unsigned char unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_020ba040;

extern unsigned int func_02002a88(unsigned int, unsigned char, unsigned int, unsigned int, unsigned int);
extern int func_02002b40(int, unsigned char, int, int);
extern int func_02002bd0(void *, unsigned char, unsigned char, unsigned char, unsigned char);

void func_020ba108(UnkStruct_020ba108 *s)
{
    s->unk_00 = 0;
    s->unk_04 = 0xff;
    s->unk_08 = 0;
    s->unk_0C = 0;
    s->unk_10 = 0;
}

void func_020ba0f8(struct UnkStruct_020ba0f8 *p, int a, unsigned char b, int c, int d, int e)
{
    p->unk_00 = a;
    p->unk_04 = b;
    p->unk_08 = c;
    p->unk_0C = d;
    p->unk_10 = e;
}

unsigned int func_020ba0dc(struct UnkStruct_020ba0dc *p)
{
    return func_02002a88(p->unk_00, p->unk_04, p->unk_08, p->unk_0C, p->unk_10);
}

unsigned int func_020ba0cc(UnkStruct_020ba0cc *p)
{
    return ((p->unk_10 - p->unk_0C + 0x3f) << 18) >> 24;
}

void func_020ba0c0(struct UnkStruct_020ba0c0 *s, int a, char b, int c, int d)
{
    s->unk_00 = a;
    s->unk_04 = b;
    s->unk_08 = c;
    s->unk_0C = d;
}

void func_020ba0a8(struct UnkStruct_020ba0a8 *s)
{
    func_02002b40(s->a, s->b, s->c, s->d);
}

int func_020ba0a4(void)
{
    return 1;
}

void func_020ba09c(UnkStruct_020ba09c *p, int a, int b, int c)
{
    p->unk_00 = a;
    p->unk_04 = (unsigned char) b;
    p->unk_08 = c;
}

void func_020ba07c(struct UnkStruct_020ba07c *arg)
{
    unsigned char mask = (unsigned char) arg->unk_08;
    func_02002bd0(arg->unk_00, arg->unk_04, mask, mask, mask);
}

int func_020ba078(void *object)
{
    return 1;
}

void func_020ba064(UnkStruct_020ba064 *out, int a, unsigned char b, int c, unsigned char d)
{
    out->a = a;
    out->b = b;
    out->c = c;
    out->d = d;
}

void func_020ba040(UnkStruct_020ba040 *p)
{
    unsigned char c = (unsigned char) p->unk_08;
    unsigned char d = (unsigned char) p->unk_0C;
    func_02002bd0((void *) p->unk_00, p->unk_04, c, c, d);
}

int func_020ba03c(void)
{
    return 1;
}
