/* public_box_2: 4 functions, module ov110
 * mwccarm 1.2/base -O4,s
 * func_ov110_0229cb28 @ 0x0229cb28, 0x50 bytes, Thumb
 * func_ov110_0229cac8 @ 0x0229cac8, 0x60 bytes, Thumb
 * func_ov110_0229ca7c @ 0x0229ca7c, 0x4c bytes, Thumb
 * func_ov110_0229ca48 @ 0x0229ca48, 0x34 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0xf8 - 0x8d - 1];
    unsigned char unk_F8;
    unsigned char pad_F9[0xfa - 0xf8 - 1];
    unsigned char unk_FA;
    unsigned char pad_FB[0x22e0 - 0xfa - 1];
    char unk_22E0[1];
    unsigned char pad_22E1[0x2344 - 0x22e0 - 1];
    char unk_2344[1];
} UnkStruct_0229cb28;

typedef struct {
    unsigned char pad_00[0xfa];
    unsigned char unk_FA;
    unsigned char pad_FB[0x21e5];
    char unk_22E0;
    unsigned char pad_22E1[0x63];
    char unk_2344;
} UnkStruct_0229ca7c;

typedef struct {
    char pad_00[0x22e0];
    int unk_22E0;
} UnkStruct_0229ca48;

extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, unsigned char b);
extern int func_ov002_0220a08c(void *ptr, int a, int b, int c);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_022090e4(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_0208e4c0(void *, int);
extern void func_ov002_0220a374(const char *, int);
extern int func_ov110_0229cc14(void *self);
extern int func_ov110_0229cc04(void *self);

void func_ov110_0229cb28(UnkStruct_0229cb28 *self)
{
    int tmp1;
    int tmp2;
    tmp1 = func_ov002_02208ae4(&self->unk_2344);
    tmp2 = func_ov002_02208ad8(&self->unk_2344, self->unk_FA);
    func_ov002_0220a08c(&self->unk_22E0, tmp1, tmp2, 2);
    self->unk_F8 = self->unk_8D;
    func_ov002_02208098((void *) (self), 8);
}

void func_ov110_0229cac8(void *p)
{
    unsigned char *base = (unsigned char *) p;
    int v1;
    int v2;
    base[0xf9] = 1;
    base[0xfa] = func_ov002_022090e4(base + 0x2344, 1);
    v1 = func_ov002_02208ae4(base + 0x2344);
    v2 = func_ov002_02208ad8(base + 0x2344, base[0xfa]);
    func_ov002_0220a0b4(base + 0x22e0, v1, v2);
    func_0208e4c0(base + 0x22e0, 8);
    func_ov002_02208098((void *) (p), 0x12);
}

void func_ov110_0229ca7c(UnkStruct_0229ca7c *s)
{
    int a, b;
    s->unk_FA = 0;
    a = func_ov002_02208ae4((void *) (&s->unk_2344));
    b = func_ov002_02208ad8((void *) (&s->unk_2344), s->unk_FA);
    func_ov002_0220a0b4((void *) (&s->unk_22E0), a, b);
    func_ov002_0220a374(&s->unk_22E0, 7);
}

void func_ov110_0229ca48(UnkStruct_0229ca48 *self)
{
    int a, b;
    a = func_ov110_0229cc14(self);
    b = func_ov110_0229cc04(self);
    func_ov002_0220a0b4((void *) (&self->unk_22E0), a, b);
    func_ov002_0220a374((const char *) (&self->unk_22E0), 1);
}
