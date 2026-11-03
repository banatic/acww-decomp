/* field_actor_53: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022187d4 @ 0x022187d4, 0x1c bytes, Thumb
 * func_ov003_02218798 @ 0x02218798, 0x3c bytes, Thumb
 * func_ov003_02218754 @ 0x02218754, 0x44 bytes, Thumb
 * func_ov003_02218734 @ 0x02218734, 0x20 bytes, Thumb
 * func_ov003_0221871c @ 0x0221871c, 0x18 bytes, Thumb
 */

typedef struct {
    unsigned int a;
    unsigned int b;
    short c;
} UnkStruct_022187d4;

typedef struct {
    unsigned char pad_00[0x7d4];
    UnkStruct_022187d4 sub;
} UnkStruct_022187d4_2;

struct Sub_02218754 {
    int unk_00;
    int unk_04;
    short unk_08;
};

struct UnkStruct_0221871c {
    int unk_00;
    int unk_04;
    short unk_08;
    char unk_0A;
};

extern void func_0200fbc4(UnkStruct_022187d4_2 *self, unsigned int a, unsigned int b, short c);
extern void func_02010f5c(void *);
extern int func_02056f28(void *, int);
extern int func_0200f328(void *, int);
extern int func_02056f94(void *p);
extern int func_ov003_022186cc(void *a, int b, int c, int d, int e, int f, int g);
extern void func_02010d64(void *arg);

void func_ov003_022187d4(UnkStruct_022187d4_2 *self)
{
    UnkStruct_022187d4 *s;
    s = &self->sub;
    func_0200fbc4(self, s->a, s->b, s->c);
}

void func_ov003_02218798(void *p)
{
    func_02010f5c(p);
    if (func_02056f28((char *) p + 0x2d0, 8) == 0 && func_02056f28((char *) p + 0x2d0, 0xd) == 0) {
        return;
    }
    func_0200f328(p, 0x7d5);
}

void func_ov003_02218754(char *a)
{
    if (func_02056f94(a + 0x2d0)) {
        struct Sub_02218754 *p = (struct Sub_02218754 *) (a + 0x7d4);
        func_ov003_022186cc(a, 1, p->unk_00, p->unk_04, p->unk_08, 6, -1);
    }
}

void func_ov003_02218734(void *arg)
{
    func_ov003_022187d4((UnkStruct_022187d4_2 *) arg);
    func_ov003_02218798(arg);
    func_02010d64(arg);
    func_ov003_02218754((char *) arg);
}

void func_ov003_0221871c(struct UnkStruct_0221871c *out, char fA, int f0, int f4, short f8)
{
    out->unk_0A = fA;
    out->unk_00 = f0;
    out->unk_04 = f4;
    out->unk_08 = f8;
}
