/* field_actor_motion_3: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020110a0 @ 0x020110a0, 0x14 bytes, Thumb
 * func_02011098 @ 0x02011098, 0x6 bytes, Thumb
 * func_0201108c @ 0x0201108c, 0xc bytes, Thumb
 * func_0201107c @ 0x0201107c, 0x10 bytes, Thumb
 * func_0201100c @ 0x0201100c, 0x70 bytes, Thumb
 * func_02010ff4 @ 0x02010ff4, 0x18 bytes, Thumb
 * func_02010f6c @ 0x02010f6c, 0x88 bytes, Thumb
 */

typedef struct {
    short first;
    short second;
} Pair;

typedef struct {
    unsigned char pad_00[140];
    unsigned short unk_8C;
} UnkStruct_02011098;

typedef struct {
    unsigned char pad_00[0x98];
    int unk_98;
} UnkStruct_0201107c;

typedef struct Sub5c {
    int pad_00;
    int ret;
} Sub5c;

typedef struct UnkStruct_0201100c {
    char pad_00[0x5c];
    Sub5c sub_5c;
    char pad_64[0x68 - 0x5c - 8];
    void *unk_68;
    char pad_6C[0x8e - 0x6c];
    signed short unk_8E;
    char pad_90[0x174 - 0x90];
    char unk_174;
    char pad_175[0x7a4 - 0x175];
    char unk_7A4;
    char pad_7A5[0x7f0 - 0x7a5];
    void *unk_7F0;
} UnkStruct_0201100c;

struct UnkStruct_02010ff4 {
    char pad_00[0x60];
    int unk_60;
};

struct UnkStruct_02010f6c {
    char pad_00[0x5c];
    unsigned int sub1;
    char pad_60[4];
    unsigned int sub2;
    char pad_68[0x26];
    short unk_8E;
};

extern int func_020113e0(void *p, int);
extern void func_02003260(UnkStruct_0201107c *p);
extern void func_02003300(void *, void *);
extern void *func_02032c64(void *);
extern int func_020082a0(void *, void *);
extern void func_02031288(void *, void *, void *, int, int, void *, int);
extern void *func_02032c50(void *);
extern int func_020310c8(int value);
extern int func_0200e9a8(void *a, unsigned char *b, unsigned int *c, unsigned int *d, short *e);
extern int func_020b65c4(void);
extern int func_020113bc(short *a, short b);
extern void func_02011490(unsigned int *a, unsigned int b);

void func_020110a0(void *s, short *src)
{
    Pair *current = (Pair *) ((char *) s + 0x8c);
    current->second = *src;
    *(short *) ((char *) s + 0x94) = current->second;
}

void func_02011098(UnkStruct_02011098 *p, unsigned short v)
{
    p->unk_8C = v;
}

void func_0201108c(void *p, int argument1)
{
    func_020113e0((char *) p + 0x8c, (int) argument1);
}

void func_0201107c(UnkStruct_0201107c *p, int *q)
{
    p->unk_98 = *q;
    func_02003260(p);
}

int func_0201100c(UnkStruct_0201100c *self)
{
    int result;

    char buf[0x34];
    char *p5c;
    signed short s;
    void *a0;

    p5c = (char *) self + 0x5c;
    func_02003300(self, &self->unk_174);
    func_02032c64(buf);
    s = self->unk_8E;
    if (func_020082a0(self, self->unk_7F0) == 0) {
        a0 = buf;
    } else {
        a0 = &self->unk_7A4;
    }
    func_02031288(a0, p5c, (char *) self + 0x68, s, 0xfd7, self, 0xf);
    func_02032c50(buf);
    result = func_020310c8(0);
    *(int *) (p5c + 4) = result;
    return result;
}

int func_02010ff4(struct UnkStruct_02010ff4 *s)
{
    int result;

    func_02003300((void *) s, 0);
    result = func_020310c8(0);
    s->unk_60 = result;
    return result;
}

int func_02010f6c(struct UnkStruct_02010f6c *self)
{
    unsigned char b;
    short s6, s8;
    unsigned int v1, v2;
    int ok;

    if (func_0200e9a8(self, &b, &v1, &v2, &s6) == 0) {
        return 0;
    }

    if (b != func_020b65c4()) {
        return 0;
    }

    s8 = self->unk_8E;

    ok = (func_020113bc(&s8, s6) == 0);

    func_020110a0(self, &s8);
    func_02011490(&self->sub1, v1);
    func_02011490(&self->sub2, v2);

    if (ok) {
        ok = (v1 == self->sub1 && v2 == self->sub2);
    }

    return ok;
}
