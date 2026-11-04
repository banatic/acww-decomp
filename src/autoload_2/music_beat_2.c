/* music_beat_2: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f9680 @ 0x020f9680, 0x30 bytes, ARM
 * func_020f9624 @ 0x020f9624, 0x5c bytes, ARM
 * func_020f95f8 @ 0x020f95f8, 0x2c bytes, ARM
 * func_020f95f0 @ 0x020f95f0, 0x8 bytes, ARM
 */

typedef struct {
    char unk_00;
    char sig[4];
    int unk_08;
    volatile int unk_0C;
    volatile int unk_10;
} UnkStruct_020f9680;

struct UnkStruct_020f9624 {
    char a;
    unsigned char pad_15[0x13];
    char b;
    char d;
    char c;
    unsigned char pad_17[1];
    short e;
    char unk_1A;
};

struct UnkStruct_020f9624_2 {
    void *vtbl;
    unsigned char pad_04[0x10];
    struct UnkStruct_020f9624 sub;
};

typedef struct {
    unsigned char pad_00[40];
    unsigned char unk_28;
} UnkStruct_020f95f0;

extern void *func_020f98e8(struct UnkStruct_020f9624_2 *self);
extern int data_0213f250;
extern struct UnkStruct_020f9624_2 *data_021fd1bc;
extern unsigned int *func_020f9868(void *self);
extern unsigned int *func_020f9848(void *self);

void func_020f9680(UnkStruct_020f9680 *s)
{
    s->sig[0] = -1;
    s->sig[1] = -1;
    s->sig[2] = -1;
    s->sig[3] = -1;
    s->unk_10 = 0;
    s->unk_0C = s->unk_10;
    s->unk_08 = s->unk_0C;
}

struct UnkStruct_020f9624_2 *func_020f9624(struct UnkStruct_020f9624_2 *self)
{
    func_020f98e8(self);
    self->vtbl = &data_0213f250;
    func_020f9680((UnkStruct_020f9680 *) (&self->sub));
    self->sub.a = -1;
    self->sub.b = 0;
    self->sub.c = 0;
    self->sub.d = 1;
    self->sub.e = -1;
    self->sub.unk_1A = 1;
    data_021fd1bc = self;
    return self;
}

void *func_020f95f8(void *self)
{
    *(void **) self = (void *) &data_0213f250;
    func_020f9868(self);
    func_020f9848(self);
    return self;
}

void func_020f95f0(UnkStruct_020f95f0 *p, unsigned char v)
{
    p->unk_28 = v;
}
