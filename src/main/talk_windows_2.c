/* talk_windows_2: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aa688 @ 0x020aa688, 0xe bytes, Thumb
 * func_020aa680 @ 0x020aa680, 0x6 bytes, Thumb
 * func_020aa678 @ 0x020aa678, 0x6 bytes, Thumb
 * func_020aa660 @ 0x020aa660, 0x18 bytes, Thumb
 * func_020aa5d0 @ 0x020aa5d0, 0x90 bytes, Thumb
 * func_020aa4f4 @ 0x020aa4f4, 0xda bytes, Thumb
 * func_020aa4c0 @ 0x020aa4c0, 0x32 bytes, Thumb
 * func_020aa420 @ 0x020aa420, 0x9e bytes, Thumb
 * func_020aa3f4 @ 0x020aa3f4, 0x2a bytes, Thumb
 * func_020aa360 @ 0x020aa360, 0x92 bytes, Thumb
 * func_020aa2f4 @ 0x020aa2f4, 0x6c bytes, Thumb
 * func_020aa2e4 @ 0x020aa2e4, 0x10 bytes, Thumb
 * func_020aa28c @ 0x020aa28c, 0x58 bytes, Thumb
 * func_020aa25c @ 0x020aa25c, 0x30 bytes, Thumb
 * func_020aa228 @ 0x020aa228, 0x34 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[192];
    unsigned char unk_C0;
} UnkStruct_020aa680;

typedef struct {
    unsigned char pad_00[8];
    unsigned long unk_08;
} UnkStruct_020aa678;

typedef struct {
    unsigned char pad_00[0xb4];
    int unk_B4;
    int unk_B8;
    int unk_BC;
} UnkStruct_020aa4f4;

typedef struct UnkStruct_020aa420 {
    unsigned char pad_00[0xc];
    unsigned char unk_0C;
    unsigned char pad_0D[0x77];
    unsigned char unk_84;
} UnkStruct_020aa420;

struct UnkStruct_020aa3f4 {
    char pad_00[8];
    int unk_08;
    char pad_0C[176];
    int unk_BC;
    char unk_C0;
};

typedef struct {
    char pad_00[0x0c];
    int unk_0C;        // offset 0x0c
    char pad_10[0x74]; // offset 0x10 to 0x84
    int unk_84;        // offset 0x84
    char pad_88[0x2c]; // offset 0x88 to 0xb4
    int unk_B4;        // offset 0xb4
    int unk_B8;        // offset 0xb8
    int unk_BC;        // offset 0xbc
    char unk_C0;       // offset 0xc0
} UnkStruct_020aa360;

typedef struct {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x84 - 0x10];
    int unk_84;
} UnkStruct_020aa2f4;

typedef struct UnkStruct_020aa28c {
    unsigned int unk_00;
    unsigned char pad_04[4];
    unsigned int unk_08;
    unsigned char unk_0C[0x148];
    unsigned int unk_154;
    unsigned char pad_158[0x34];
    unsigned int unk_18C;
    unsigned int unk_190;
    unsigned int unk_194;
    unsigned char unk_198;
} UnkStruct_020aa28c;

extern int func_020ac8c8(void *);
extern void func_020ab30c(void *);
extern void func_020ac444(void *);
extern void func_020ac424(void *);
extern void func_020ac3ec(void *);
extern void func_020ac8a8(void *);
extern int func_0209d368(int id, int index);
extern void func_020ac39c(void *, int, int);
extern void func_020ac384(void *);
extern void func_020ab304(char *);
extern void func_020ac1e8(void *);
extern int func_020ab270(void *);
extern void func_020ac11c(void *, int, int);
extern void func_020ab278(void *p);
extern void *func_020ab344(void *p);
extern void func_020ac1cc(void *p, void *q);
extern int func_020ab338(void *p);
extern int func_020ac240(void *p);
extern void func_020ac1d0(void *p);
extern void func_020ac1c4(void *p);
extern int func_020ac218(void *p);
extern int func_020ac198(void *p, int a);
extern void func_020ac1dc(void *p);
extern void func_020ab2fc(void *p);
extern void func_0200467c(int cmd);
extern void func_020ab2e0(void *a);
extern void func_020ac3e0(void *a);
extern int func_020ab348(void *p);
extern int func_020ab334(void *p);
extern void func_020ac46c(void *p, int x);
extern void func_020ac71c(void *p);
extern void func_020ac624(void *p);
extern void func_020ac588(void *p);
extern void func_020ac50c(void *p);
extern void func_020ac4ec(void *p);
extern void func_020aae8c(void *sub, int arg);
extern void func_020aa82c(UnkStruct_020aa28c *p);
extern void *func_020ac0ac(void *p);
extern void func_020aaeb4(void *dst, void *src);
extern int func_020aaea4(void *ptr);
extern void *func_020ac078(void *ptr);
extern void func_020aa7fc(void *ptr);
extern void func_020edb3c(void *);
extern unsigned char data_020e404c[];

void func_020aa5d0(void *self);
void func_020aa4c0(void *param);
void func_020aa3f4(struct UnkStruct_020aa3f4 *p);
void func_020aa2f4(UnkStruct_020aa2f4 *obj);

int func_020aa688(void *arg)
{
    if (*(int *) ((char *) arg + 8) == 0) {
        return 1;
    }
    return 0;
}

unsigned char func_020aa680(UnkStruct_020aa680 *p)
{
    return p->unk_C0;
}

void func_020aa678(UnkStruct_020aa678 *p)
{
    p->unk_08 = 0;
}

void func_020aa660(void *r0)
{
    if (*(unsigned char *) ((char *) r0 + 4) != 0) {
        *(unsigned char *) ((char *) r0 + 4) = 0;
        func_020aa5d0(r0);
    }
}

void func_020aa5d0(void *self)
{
    int *p = (int *) self;
    p[2] = 1;
    func_020ac8c8((char *) self + 0xc);
    func_020ab30c((char *) self + 0x84);
    func_020aa2f4((UnkStruct_020aa2f4 *) self);
    func_020ac444((char *) self + 0xc);
    func_020ac424((char *) self + 0xc);
    func_020ac3ec((char *) self + 0xc);
    func_020ac8a8((char *) self + 0xc);
    p[0x2f] = func_0209d368(0x64, 2) + 3;
    p[0x2d] = func_0209d368(0x64, 4) + 5;
    p[0x2e] = func_0209d368(0x64, 5) - 5;
    func_020ac39c((char *) self + 0xc, p[0x2d], p[0x2e]);
    func_020ac384((char *) self + 0xc);
}

void func_020aa4f4(UnkStruct_020aa4f4 *self)
{
    int flag;

    if (self->unk_BC > func_0209d368(100, 3) + 2) {
        self->unk_B4 += func_0209d368(100, 6) - 6;
        self->unk_B8 += func_0209d368(100, 7) + 6;
    } else {
        self->unk_B4 += func_0209d368(100, 8) + 1;
        self->unk_B8 += func_0209d368(100, 9) - 1;
    }

    self->unk_BC -= 1;
    flag = (self->unk_BC <= 0);

    if (flag) {
        self->unk_B4 = 0;
        self->unk_B8 = 0;
    }

    func_020ac39c((void *) ((char *) self + 0xc), self->unk_B4, self->unk_B8);

    if (flag) {
        func_020ab304((char *) self + 0x84);
        func_020aa4c0((void *) ((char *) self));
    }
}

void func_020aa4c0(void *param)
{
    int result;
    void *ptr;
    int flag;

    *(int *) ((char *) param + 8) = 2;
    func_020ac1e8((char *) param + 12);
    result = func_020ab270((char *) param + 132);
    if (result == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    ptr = (char *) param + 12;
    func_020ac11c(ptr, flag, 0);
}

void func_020aa420(UnkStruct_020aa420 *self)
{
    int cond;
    int k;
    void *q;

    func_020ab278(&self->unk_84);
    cond = (func_020ab270(&self->unk_84) == 0) ? 1 : 0;
    func_020ac11c(&self->unk_0C, cond, 1);
    q = func_020ab344(&self->unk_84);
    func_020ac1cc(&self->unk_0C, q);
    k = func_020ab338(&self->unk_84);
    if (k < 0) {
        return;
    }
    if (func_020ac240(&self->unk_0C) != 0) {
        func_020ac1d0(&self->unk_0C);
        func_020ac1c4(&self->unk_0C);
        return;
    }
    if (func_020ac218(&self->unk_0C) != 0) {
        if (func_020ac198(&self->unk_0C, k) != 0) {
            func_020ac1dc(&self->unk_0C);
            func_020ab2fc(&self->unk_84);
            func_020aa3f4((struct UnkStruct_020aa3f4 *) self);
        }
    }
}

void func_020aa3f4(struct UnkStruct_020aa3f4 *p)
{
    p->unk_08 = 3;
    p->unk_C0 = 1;
    p->unk_BC = func_0209d368(0x65, 2) + 2;
    func_0200467c(0x14);
}

void func_020aa360(UnkStruct_020aa360 *r5)
{
    int flag;

    r5->unk_B4 += func_0209d368(0x65, 3) + 0x11;
    r5->unk_B8 += func_0209d368(0x65, 4) - 0x11;

    r5->unk_BC--;
    flag = (r5->unk_BC > 0) ? 0 : 1;

    func_020ac39c(&r5->unk_0C, r5->unk_B4, r5->unk_B8);
    r5->unk_C0 = 0;

    if (flag) {
        func_020ab2e0(&r5->unk_84);
        func_020ac3e0(&r5->unk_0C);
        func_020aa678((UnkStruct_020aa678 *) r5);
    }
}

void func_020aa2f4(UnkStruct_020aa2f4 *obj)
{
    int r4 = func_020ab348(&obj->unk_84);
    func_020ac46c(&obj->unk_0C, func_020ab334(&obj->unk_84));
    if (r4 == 1) {
        func_020ac71c(&obj->unk_0C);
    } else if (r4 == 2) {
        func_020ac624(&obj->unk_0C);
    } else if (r4 == 3) {
        func_020ac588(&obj->unk_0C);
    } else if (r4 == 4) {
        func_020ac50c(&obj->unk_0C);
    } else if (r4 == 5) {
        func_020ac4ec(&obj->unk_0C);
    }
}

void func_020aa2e4(char *self, int arg)
{
    func_020aae8c(self + 0x154, arg);
}

UnkStruct_020aa28c *func_020aa28c(UnkStruct_020aa28c *p)
{
    func_020aa82c(p);
    p->unk_00 = (unsigned int) ((int *) data_020e404c);
    p->unk_08 = 0;
    func_020ac0ac(p->unk_0C);
    func_020aaeb4(&p->unk_154, &p->unk_0C);
    p->unk_18C = 0;
    p->unk_190 = 0;
    p->unk_194 = 0;
    p->unk_198 = 0;
    return p;
}

void *func_020aa25c(void *p)
{
    *(void **) p = (void *) ((int *) data_020e404c);
    func_020aaea4((char *) p + 0x154);
    func_020ac078((char *) p + 0xc);
    func_020aa7fc(p);
    return p;
}

void *func_020aa228(void *obj)
{
    *(void **) obj = data_020e404c;
    func_020aaea4((char *) obj + 0x154);
    func_020ac078((char *) obj + 0xc);
    func_020aa7fc(obj);
    func_020edb3c(obj);
    return obj;
}
