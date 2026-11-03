/* scene_motion_kinds_7: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201935c @ 0x0201935c, 0xf4 bytes, Thumb
 * func_02019304 @ 0x02019304, 0x58 bytes, Thumb
 * func_0201924c @ 0x0201924c, 0xb8 bytes, Thumb
 */

typedef struct Vec3 {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_0201935c {
    unsigned char pad_00[0x98];
    unsigned char unk_98;
    unsigned char pad_99[3];
    unsigned int unk_9C;
    short unk_A0;
} UnkStruct_0201935c;

typedef struct Profile {
    unsigned char pad_00[4];
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned char pad_14[6];
    short unk_1A;
    unsigned short unk_1C;
} Profile;

typedef struct Context {
    unsigned char pad_00[0x98];
    unsigned int unk_98;
    unsigned char pad_9C[0x350 - 0x9c];
    unsigned char unk_350[0x5a];
    unsigned char unk_3AA;
    unsigned char pad_3AB[0x628 - 0x3ab];
    unsigned int unk_628;
} Context;

struct UnkStruct_02019304 {
    char pad_00[0x98];
    char flag;
    int *ptr;
};

struct UnkStruct_02019304_2 {
    char pad_00[0x8e];
    short val;
    char pad_90[0x350 - 0x90];
    int unk_350;
};

extern Profile *func_02019de4(void *a);
extern void func_0201b044(void *a, void *b);
extern void func_0201afd4(void *a, void *b);
extern int func_0201b040(void *a);
extern int func_0201c3b0(Context *a, short *b, int c);
extern void func_0201b1a4(void *a, void *b, int c, int d, int e);
extern void func_0201aff4(void *a, short b);
extern void func_020123ec(int a, int b, int c);
extern void func_0201b350(void *a, short b);
extern void func_02019af0(void *a, int b);
extern unsigned short data_020c80f8;
extern int func_0201afec(void *);
extern int func_0201c3dc(int);
extern int func_0201afe4(void *);
extern void func_0201b188(void *, void *);
extern int func_0201aff8(void *, void *, int);
extern int func_0201afc0(void *);

int func_0201935c(UnkStruct_0201935c *self, Context *b, int c, int d)
{
    Profile *p;
    Vec3 v0, v1;
    short out;

    p = func_02019de4(self);
    {
        int t8 = p->unk_08;
        int t4 = p->unk_04;
        v0.x = t4;
        v0.y = 0;
        v0.z = t8;
    }
    {
        int t10 = p->unk_10;
        int tc = p->unk_0C;
        v1.x = tc;
        v1.y = 0;
        v1.z = t10;
    }
    self->unk_9C = c;
    self->unk_A0 = (short) d;
    func_0201b044(&b->unk_350, &v0);
    func_0201afd4(&b->unk_350, &v1);
    if (func_0201c3b0(b, &out, func_0201b040(&b->unk_350))) {
        func_0201b1a4(&b->unk_350, b, self->unk_9C, (short) p->unk_1A, (int) p->unk_1C);
        self->unk_98 = 1;
    } else {
        func_0201b1a4(&b->unk_350, b, 3, (short) p->unk_1A, (int) p->unk_1C);
        func_0201aff4(&b->unk_350, out);
        b->unk_98 = 0;
        self->unk_98 = 0;
    }
    if (b->unk_628) {
        func_020123ec(b->unk_628, (int) data_020c80f8, 0);
    }
    func_0201b350(&b->unk_3AA, self->unk_A0);
    func_02019af0(self, 0);
    return 0;
}

void func_02019304(struct UnkStruct_02019304 *a, struct UnkStruct_02019304_2 *b)
{
    if (func_0201c3dc((short) (func_0201afec(&b->unk_350) - b->val)) == 0) {
        return;
    }
    func_0201b1a4(&b->unk_350, b, (int) a->ptr, func_0201afe4(&b->unk_350), data_020c80f8);
    a->flag = 1;
}

void func_0201924c(unsigned char *p0, unsigned char *p1)
{
    short local;
    unsigned int s;
    unsigned int tmp;
    unsigned int v;

    s = (unsigned int) func_0201b040(p1 + 0x350);
    func_0201b188(p1 + 0x350, p1);
    if (func_0201aff8(p1 + 0x350, p1, 0) != 0) {
        if (func_0201afc0(p1 + 0x350) != 0) {
            func_0201afd4(p1 + 0x350, (void *) s);
        } else {
            func_02019af0(p0, 1);
        }
    } else {
        if (func_0201c3b0((Context *) p1, &local, s) == 0) {
            s = data_020c80f8;
            tmp = func_0201afe4(p1 + 0x350);
            func_0201b1a4(p1 + 0x350, p1, 3, tmp, data_020c80f8);
            func_0201aff4(p1 + 0x350, local);
            *(unsigned char *) (p0 + 0x98) = 0;
            *(unsigned int *) (p1 + 0x98) = 0;
            v = *(unsigned int *) (p1 + 0x628);
            if (v != 0) {
                func_020123ec(v, s, 0);
            }
        }
    }
}
