/* my_designs_3: 5 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229a2e4 @ 0x0229a2e4, 0x74 bytes, Thumb
 * func_ov121_0229a294 @ 0x0229a294, 0x50 bytes, Thumb
 * func_ov121_0229a230 @ 0x0229a230, 0x64 bytes, Thumb
 * func_ov121_0229a1e4 @ 0x0229a1e4, 0x4c bytes, Thumb
 * func_ov121_0229a1b0 @ 0x0229a1b0, 0x34 bytes, Thumb
 */

typedef struct {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0xb3 - 0x8e];
    unsigned char unk_B3;
    unsigned char unk_B4;
    char pad_B5[0x3a8 - 0xb5];
    char unk_3A8;
    char pad_3A9[0x528 - 0x3a9];
    char unk_528;
} UnkStruct_0229a294;

typedef struct Sub1 {
    int a;
} Sub1;

typedef struct Sub2 {
    int b;
} Sub2;

typedef struct Super {
    unsigned char pad_00[0xB2];
    unsigned char unk_B2;
    unsigned char unk_B3;
    unsigned char pad_B4[0x3A8 - 0xB4];
    Sub2 sub_3A8;
    unsigned char pad2[0x528 - (0x3A8 + sizeof(Sub2))];
    Sub1 sub_528;
} Super;

typedef struct {
    unsigned char pad_00[0xb3];
    unsigned char flag;
    unsigned char pad_B4[0x3a8 - 0xb3 - 1];
    char unk_3A8;
    unsigned char pad_3A9[0x528 - 0x3a8 - 1];
    char unk_528;
} UnkStruct_0229a1e4;

extern int func_ov121_02299a5c(void *p, int arg);
extern int func_ov121_0229a3a8(void *p);
extern int func_ov121_0229a37c(void *p);
extern void func_ov121_02299a3c(void *p, int arg);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char c);
extern int func_ov002_0220a08c(void *p, int a, int b, int c);
extern unsigned char func_ov002_022090e4(void *p, int v);
extern void func_0208e4c0(void *p, int v);
extern void func_ov002_0220a374(void *ptr, int a);

void func_ov121_0229a2e4(void *p)
{
    if (func_ov121_02299a5c(p, 0x10)) {
        int a = func_ov121_0229a3a8(p);
        int b = func_ov121_0229a37c(p);
        func_ov002_0220a0b4((char *) p + 0x3a8, a, b);
        func_ov121_02299a3c(p, 0x10);
    } else {
        int a = func_ov121_0229a3a8(p);
        int b = func_ov121_0229a37c(p);
        func_ov002_0220a05c((char *) p + 0x3a8, a, b, 3, 1);
        *((unsigned char *) p + 0xb4) = *((unsigned char *) p + 0x8d);
        func_ov002_02208098(p, 6);
    }
}

void func_ov121_0229a294(UnkStruct_0229a294 *self)
{
    int v1, v2;
    v1 = func_ov002_02208ae4(&self->unk_528);
    v2 = func_ov002_02208ad8(&self->unk_528, self->unk_B3);
    func_ov002_0220a08c(&self->unk_3A8, v1, v2, 2);
    self->unk_B4 = self->unk_8D;
    func_ov002_02208098(self, 6);
}

void func_ov121_0229a230(Super *self)
{
    int r4;

    self->unk_B2 = 8;
    self->unk_B3 = func_ov002_022090e4(&self->sub_528, 1);
    r4 = func_ov002_02208ae4(&self->sub_528);
    func_ov002_0220a0b4(&self->sub_3A8, r4, func_ov002_02208ad8(&self->sub_528, self->unk_B3));
    func_0208e4c0(&self->sub_3A8, 8);
    func_ov002_02208098(self, 15);
}

void func_ov121_0229a1e4(UnkStruct_0229a1e4 *s)
{
    int v1;
    int v2;
    s->flag = 0;
    v1 = func_ov002_02208ae4(&s->unk_528);
    v2 = func_ov002_02208ad8(&s->unk_528, s->flag);
    func_ov002_0220a0b4(&s->unk_3A8, v1, v2);
    func_ov002_0220a374(&s->unk_3A8, 7);
}

void func_ov121_0229a1b0(void *p)
{
    int a;
    int b;

    a = func_ov121_0229a3a8(p);
    b = func_ov121_0229a37c(p);
    func_ov002_0220a0b4((char *) p + 0x3a8, a, b);
    func_ov002_0220a374((char *) p + 0x3a8, 1);
}
