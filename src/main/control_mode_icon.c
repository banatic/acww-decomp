/* control_mode_icon: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208ffd8 @ 0x0208ffd8, 0xc bytes, Thumb
 * func_0208ffcc @ 0x0208ffcc, 0xc bytes, Thumb
 * func_0208ffc0 @ 0x0208ffc0, 0xc bytes, Thumb
 * func_0208ffac @ 0x0208ffac, 0x14 bytes, Thumb
 * func_0208ff98 @ 0x0208ff98, 0x14 bytes, Thumb
 * func_0208ff88 @ 0x0208ff88, 0x10 bytes, Thumb
 * func_0208ff78 @ 0x0208ff78, 0x10 bytes, Thumb
 * func_0208ff68 @ 0x0208ff68, 0x10 bytes, Thumb
 * func_0208ff58 @ 0x0208ff58, 0x10 bytes, Thumb
 * func_0208fedc @ 0x0208fedc, 0x7c bytes, Thumb
 * func_0208feb0 @ 0x0208feb0, 0x2c bytes, Thumb
 * func_0208fe80 @ 0x0208fe80, 0x30 bytes, Thumb
 * func_0208fe5c @ 0x0208fe5c, 0x24 bytes, Thumb
 * func_0208fe34 @ 0x0208fe34, 0x28 bytes, Thumb
 * func_0208fe1c @ 0x0208fe1c, 0x16 bytes, Thumb
 * func_0208fe18 @ 0x0208fe18, 0x2 bytes, Thumb
 * func_0208fe14 @ 0x0208fe14, 0x2 bytes, Thumb
 * func_0208fdc8 @ 0x0208fdc8, 0x4c bytes, Thumb
 */

typedef struct {
    char pad_00[0xc];
    int unk_0C;
} UnkStruct_021d369c;

struct data_021d369c {
    unsigned char pad_00[0xC];
    unsigned int unk_0C;
};

struct UnkStruct_0208ff98 {
    char pad_00[0xc];
    int unk_0C;
};

struct UnkStruct_0208feb0 {
    char pad_00[0x0c];
    int unk_0C;
    int unk_10;
    char unk_14[0x14];
    unsigned char flag_28;
};

typedef struct {
    void *unk_00;
    char pad_04[8];
    unsigned int unk_0C;
    unsigned int unk_10;
    char unk_14[0x14];
    char unk_28;
} UnkStruct_0208fe80;

struct UnkStruct_0208fe5c {
    void *unk_00;
    char pad_04[0x10];
    char sub;
};

struct UnkStruct_0208fe34 {
    void *vtable;
    unsigned char pad_04[0x10];
    char unk_14;
};

typedef struct {
    char pad_00[12];
    int unk_0C;
    char pad_10[4];
    char unk_14[20];
    char unk_28;
} UnkStruct_0208fdc8;

extern unsigned int data_021d369c[4];
extern int func_0208a1d0(void *);
extern int func_0208aef0(void *);
extern int func_0208a1b0(void *, int);
extern int func_0208aeec(void *);
extern int func_0208a198(void *, int);
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);
extern void func_0208a0c8(void *p);
extern void func_0208af30(void *);
extern void func_0208a1f8(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern char data_020e246c[];
extern void func_020edb3c(void *);
extern int func_0203e340(void);
extern void func_0208a1f0(void *a, void *b);
extern void func_0208a1ec(void *a, int b);
extern void *func_0208a144(void *a);
extern char data_020d6fcc[];

void func_0208fedc(unsigned char *self);
void func_0208feb0(struct UnkStruct_0208feb0 *p);
int func_0208fe1c(void *object);
void func_0208fe18(void *object);
void func_0208fe14(void *object);
void func_0208fdc8(UnkStruct_0208fdc8 *self);

void func_0208ffd8(void)
{
    (*(struct { int pad[3]; int val; } *) data_021d369c).val = 0;
}

void func_0208ffcc(void)
{
    (*(UnkStruct_021d369c *) data_021d369c).unk_0C = 1;
}

void func_0208ffc0(void)
{
    data_021d369c[3] = 2;
}

int func_0208ffac(void)
{
    return ((*(struct data_021d369c *) data_021d369c).unk_0C == 1);
}

int func_0208ff98(void)
{
    if ((*(struct UnkStruct_0208ff98 *) data_021d369c).unk_0C != 2) {
        return 0;
    }
    return 1;
}

void func_0208ff88(void)
{
    func_0208fe18((void *) ((unsigned char *) data_021d369c));
}

void func_0208ff78(void)
{
    func_0208fe14((void *) ((int) ((int *) data_021d369c)));
}

void func_0208ff68(void)
{
    func_0208feb0((struct UnkStruct_0208feb0 *) ((void *) ((unsigned char *) data_021d369c)));
}

void func_0208ff58(void)
{
    func_0208fedc((unsigned char *) ((void *) ((unsigned char *) data_021d369c)));
}

void func_0208fedc(unsigned char *self)
{
    int a, b, c, d;

    if (self[0x28] != 0 && func_0208fe1c(self) == 0) {
        a = func_0208a1d0(self + 0x14);
        b = func_0208aef0(self);
        b += func_0208a1b0(self + 0x14, -1);
        c = func_0208aeec(self);
        d = c + func_0208a198(self + 0x14, -1);
        func_02088df8(3, a, b, d, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}

void func_0208feb0(struct UnkStruct_0208feb0 *p)
{
    if (p->flag_28 != 0) {
        func_0208a0c8(&p->unk_14[0]);
    }
    if (p->unk_0C != p->unk_10) {
        func_0208fdc8((UnkStruct_0208fdc8 *) p);
        p->unk_10 = p->unk_0C;
    }
}

void *func_0208fe80(void *obj)
{
    UnkStruct_0208fe80 *s = (UnkStruct_0208fe80 *) obj;
    func_0208af30(s);
    s->unk_00 = ((unsigned char *) data_020e246c);
    s->unk_0C = 0;
    s->unk_10 = 0;
    func_0208a1f8(s->unk_14);
    s->unk_28 = 0;
    return s;
}

struct UnkStruct_0208fe5c *func_0208fe5c(struct UnkStruct_0208fe5c *self)
{
    self->unk_00 = ((char *) data_020e246c);
    func_0208a1f4(&self->sub);
    func_0208af00(self);
    return self;
}

void *func_0208fe34(void *arg)
{
    struct UnkStruct_0208fe34 *obj = (struct UnkStruct_0208fe34 *) arg;
    obj->vtable = data_020e246c;
    func_0208a1f4(&obj->unk_14);
    func_0208af00(obj);
    func_020edb3c(obj);
    return obj;
}

int func_0208fe1c(void *object)
{
    int r4;
    int r0;

    r4 = 0;
    r0 = func_0203e340();
    if (r0 != 0) {
        r4 = 1;
    }
    r0 = r4;
    return r0;
}

void func_0208fe18(void *object) {}

void func_0208fe14(void *object) {}

void func_0208fdc8(UnkStruct_0208fdc8 *self)
{
    int field_c = self->unk_0C;
    if (field_c == 0) {
        self->unk_28 = 0;
        return;
    }
    {
        int code = (field_c == 1) ? 0x43 : 0x44;
        func_0208a1f0(&self->unk_14, data_020d6fcc + (code << 3));
        func_0208a1ec(&self->unk_14, 1);
        func_0208a144(&self->unk_14);
        self->unk_28 = 1;
    }
}
