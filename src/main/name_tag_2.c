/* name_tag_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208e438 @ 0x0208e438, 0x4c bytes, Thumb
 * func_0208e408 @ 0x0208e408, 0x30 bytes, Thumb
 * func_0208e3d4 @ 0x0208e3d4, 0x34 bytes, Thumb
 * func_0208e354 @ 0x0208e354, 0x80 bytes, Thumb
 */

struct Sub1 {
    char data[0x14];
};

struct Sub2 {
    char data[0x34];
};

struct UnkStruct_0208e438 {
    char *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    struct Sub1 sub1;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    struct Sub2 sub2;
    int unk_6C;
    int unk_70;
    int unk_74;
    int unk_78;
    char unk_7C;
};

struct Object {
    void *unk_00;
    unsigned char pad_04[0x10];
    void *unk_14;
    unsigned char pad_18[0x20];
    void *unk_38;
};

typedef struct {
    char pad_00[0x14];
    char unk_14[4];
    char pad_18[0x28 - 0x18];
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    char pad_38[0x7c - 0x38];
    unsigned char flag;
} UnkStruct_0208e354;

extern void func_0208af30(void *);
extern void func_0208a1f8(void *);
extern void *func_0203a404(void *);
extern void func_0208e2a4(void *);
extern void *func_0203a3ec(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern unsigned char data_020e22f8[];
extern void func_020edb3c(void *);
extern int func_0208a1d0(void *p);
extern int func_0208aef0(void *self);
extern int func_0208a1b0(void *p, int x);
extern int func_0208aeec(void *self);
extern int func_0208a198(void *p, int x);
extern void func_02088df8(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);

struct UnkStruct_0208e438 *func_0208e438(struct UnkStruct_0208e438 *this)
{
    func_0208af30(this);
    this->unk_00 = ((char *) data_020e22f8);
    this->unk_0C = 0;
    this->unk_10 = 10;
    func_0208a1f8(&this->sub1);
    this->unk_28 = 0;
    this->unk_2C = 0;
    this->unk_30 = 0;
    this->unk_34 = 0;
    func_0203a404(&this->sub2);
    this->unk_6C = 0;
    this->unk_70 = 0;
    this->unk_74 = 0;
    this->unk_78 = 0;
    this->unk_7C = 0;
    return this;
}

void *func_0208e408(void *s)
{
    *(void **) s = (void *) data_020e22f8;
    func_0208e2a4(s);
    func_0203a3ec((char *) s + 0x38);
    func_0208a1f4((char *) s + 0x14);
    func_0208af00(s);
    return s;
}

void *func_0208e3d4(struct Object *self)
{
    self->unk_00 = data_020e22f8;
    func_0208e2a4(self);
    func_0203a3ec(&self->unk_38);
    func_0208a1f4(&self->unk_14);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}

void func_0208e354(void *self)
{
    UnkStruct_0208e354 *s = (UnkStruct_0208e354 *) self;

    if (s->flag == 0) {
        return;
    }

    {
        int a = func_0208a1d0((char *) self + 0x14);
        int b = func_0208aef0(self);
        int v_total = s->unk_34 + (s->unk_28 + b) + func_0208a1b0((char *) self + 0x14, -1);
        int d = func_0208aeec(self);
        int v3_total = s->unk_30 + (s->unk_2C + d) + func_0208a198((char *) self + 0x14, -1);

        func_02088df8(0, a, v_total, v3_total, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}
