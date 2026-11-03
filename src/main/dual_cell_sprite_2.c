/* dual_cell_sprite_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208ec88 @ 0x0208ec88, 0x48 bytes, Thumb
 * func_0208ec40 @ 0x0208ec40, 0x48 bytes, Thumb
 * func_0208ec14 @ 0x0208ec14, 0x2c bytes, Thumb
 * func_0208ebe4 @ 0x0208ebe4, 0x30 bytes, Thumb
 * func_0208ebb8 @ 0x0208ebb8, 0x2c bytes, Thumb
 * func_0208ea98 @ 0x0208ea98, 0x120 bytes, Thumb
 * func_0208ea78 @ 0x0208ea78, 0x20 bytes, Thumb
 * func_0208ea70 @ 0x0208ea70, 0x6 bytes, Thumb
 * func_0208ea6c @ 0x0208ea6c, 0x4 bytes, Thumb
 * func_0208e9e0 @ 0x0208e9e0, 0x8c bytes, Thumb
 */

typedef struct {
    void *unk_00;
    char pad_04[8];
    int unk_0C;
    int unk_10;
    unsigned char sub_14[20];
    unsigned char sub_28[20];
    int unk_3C;
    unsigned char unk_40;
    int unk_44;
} UnkStruct_0208ec88;

typedef struct UnkStruct_0208ec40 {
    int _dummy[5];
} UnkStruct_0208ec40;

typedef struct UnkStruct_0208ec40_2 {
    void *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    UnkStruct_0208ec40 sub_14;
    UnkStruct_0208ec40 sub_28;
    int unk_3C;
    char unk_40;
    int unk_44;
} UnkStruct_0208ec40_2;

struct UnkStruct_0208ec14 {
    void *unk_00;
};

struct UnkStruct_0208ebe4 {
    unsigned int unk_00;
    char pad_04[16];
    char sub14[20];
    char sub28[20];
};

typedef struct {
    void *unk_00;
    char pad_04[0x10];
    char unk_14;
    char pad_15[0x13];
    char unk_28;
} UnkStruct_0208ebb8;

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    int unk_10;
    unsigned char sub1[0x14];
    unsigned char sub2[0x14];
    int unk_3C;
    unsigned char unk_40;
    unsigned char pad_41[3];
    int unk_44;
} UnkStruct_0208ea98;

typedef struct {
    char pad_00[0x14];
    int unk_14;
    char pad_18[0x24];
    int unk_3C;
} UnkStruct_0208e9e0;

extern void func_0208af30(void *p);
extern void func_0208a1f8(void *p);
extern void *func_0208e95c(void *, int);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);
extern unsigned char data_020e2330[];
extern int func_0208a1d0(void *sub);
extern int func_0208a1b0(void *sub, int flag);
extern int func_0208a198(void *sub, int flag);
extern int func_0208aef0(UnkStruct_0208ea98 *self);
extern int func_0208aeec(UnkStruct_0208ea98 *self);
extern void func_02088df8(int mode, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);
extern void func_0208a0c8(void *);

void *func_0208ec88(UnkStruct_0208ec88 *p, int v)
{
    func_0208af30(p);
    p->unk_00 = (void *) ((char *) data_020e2330);
    p->unk_0C = 0;
    p->unk_10 = 0;
    func_0208a1f8(p->sub_14);
    func_0208a1f8(p->sub_28);
    p->unk_3C = 0;
    p->unk_40 = v;
    p->unk_44 = -1;
    func_0208e95c(p, 0);
    return p;
}

UnkStruct_0208ec40_2 *func_0208ec40(UnkStruct_0208ec40_2 *self, char param)
{
    func_0208af30(self);
    self->unk_00 = ((int *) data_020e2330);
    self->unk_0C = 0;
    self->unk_10 = 0;
    func_0208a1f8((void *) (&self->sub_14));
    func_0208a1f8((void *) (&self->sub_28));
    self->unk_3C = 0;
    self->unk_40 = param;
    self->unk_44 = -1;
    func_0208e95c(self, 0);
    return self;
}

struct UnkStruct_0208ec14 *func_0208ec14(struct UnkStruct_0208ec14 *obj)
{
    obj->unk_00 = ((char *) data_020e2330);
    func_0208a1f4((char *) obj + 0x28);
    func_0208a1f4((char *) obj + 0x14);
    func_0208af00(obj);
    return obj;
}

struct UnkStruct_0208ebe4 *func_0208ebe4(struct UnkStruct_0208ebe4 *s)
{
    s->unk_00 = (unsigned int) data_020e2330;
    func_0208a1f4(&s->sub28);
    func_0208a1f4(&s->sub14);
    func_0208af00(s);
    func_020edb3c(s);
    return s;
}

UnkStruct_0208ebb8 *func_0208ebb8(UnkStruct_0208ebb8 *obj)
{
    obj->unk_00 = ((char *) data_020e2330);
    func_0208a1f4(&obj->unk_28);
    func_0208a1f4(&obj->unk_14);
    func_0208af00(obj);
    return obj;
}

void func_0208ea98(UnkStruct_0208ea98 *self)
{
    if (self->unk_3C == 0) {
        return;
    }

    {
        int A = func_0208a1d0(self->sub1);
        int B = func_0208a1d0(self->sub2);
        int C = func_0208a1b0(self->sub1, -1);
        int D = func_0208a198(self->sub1, -1);
        int E = func_0208a1b0(self->sub2, -1);
        int F = func_0208a198(self->sub2, -1);
        int baseX = self->unk_0C + func_0208aef0(self);
        int baseY = self->unk_10 + func_0208aeec(self);

        if (self->unk_40) {
            func_02088df8(0, A, baseX + C, baseY + D, -1, self->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
            func_02088df8(0, B, baseX + E, baseY + F, -1, self->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        } else {
            func_02088df8(1, A, baseX + C, baseY + D, -1, self->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
            func_02088df8(1, B, baseX + E, baseY + F, -1, self->unk_44, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }
}

void func_0208ea78(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x3c) != 0) {
        func_0208a0c8((char *) arg0 + 0x14);
        func_0208a0c8((char *) arg0 + 0x28);
    }
}

void func_0208ea70(int *p, int a, int b)
{
    p[3] = a;
    p[4] = b;
}

void func_0208ea6c(int *p0, int p1)
{
    p0[17] = p1;
}

void func_0208e9e0(UnkStruct_0208e9e0 *self, int *out1, int *out2)
{
    int r4 = 0;
    int r1 = r4;
    int *p;
    int t1, t2, t3, t4;

    if (self->unk_3C == 2) {
        t1 = func_0208a1b0(&self->unk_14, -1);
        t2 = func_0208a1b0(&self->unk_14, 0);
        r4 = t1 - t2;
        t3 = func_0208a198(&self->unk_14, -1);
        p = &self->unk_14;
        t4 = func_0208a198(p, 0);
        r1 = t3 - t4;
    } else if (self->unk_3C == 3) {
        t1 = func_0208a1b0(&self->unk_14, 0);
        t2 = func_0208a1b0(&self->unk_14, -1);
        r4 = t1 - t2;
        t3 = func_0208a198(&self->unk_14, 0);
        p = &self->unk_14;
        t4 = func_0208a198(p, -1);
        r1 = t3 - t4;
    }

    *out1 = r4;
    *out2 = r1;
}
