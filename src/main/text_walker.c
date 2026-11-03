/* text_walker: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a8d90 @ 0x020a8d90, 0x28 bytes, Thumb
 * func_020a8d78 @ 0x020a8d78, 0x18 bytes, Thumb
 * func_020a8d58 @ 0x020a8d58, 0x20 bytes, Thumb
 * func_020a8d20 @ 0x020a8d20, 0x38 bytes, Thumb
 * func_020a8d10 @ 0x020a8d10, 0xe bytes, Thumb
 * func_020a8d08 @ 0x020a8d08, 0x6 bytes, Thumb
 * func_020a8cd4 @ 0x020a8cd4, 0x34 bytes, Thumb
 */

typedef struct UnkStruct_020a8d90 {
    void *vtable;      // offset 0
    char pad_04[0x28]; // offset 4 to 0x2b
    int unk_2C;        // offset 0x2c
    int unk_30;        // offset 0x30
    int unk_34;        // offset 0x34
    char unk_38;       // offset 0x38
} UnkStruct_020a8d90;

typedef struct {
    void *vtable;
} UnkStruct_020a8d58;

typedef struct UnkStruct_020a8d20 {
    void *vtable;
    char pad_04[0x28];
    int unk_2C;
    int unk_30;
    int unk_34;
    unsigned char unk_38;
} UnkStruct_020a8d20;

typedef struct {
    char pad_00[0x2c];
    unsigned int unk_2C;
    unsigned int unk_30;
    unsigned int unk_34;
    unsigned char unk_38;
} UnkStruct_020a8d10;

typedef struct {
    unsigned char pad_00[56];
    unsigned char unk_38;
} UnkStruct_020a8d08;

struct UnkStruct_020a8cd4 {
    unsigned char pad_00[4];
    int unk_04;
    unsigned char pad_08[36];
    int unk_2C;
    int unk_30;
    int unk_34;
    unsigned char unk_38;
};

extern void *func_020a92b0(void *a, int b);
extern void *func_020a9260(void *);
extern void func_020edb3c(void *self);
extern unsigned char data_020e3e04[];
extern void func_020a9218(void *);
extern void func_020a9210(void *);
extern void func_020a9354(void *, int);
extern int func_020a895c(int a, int b, int c);
extern int func_020a8910(int a, int b, int c);

UnkStruct_020a8d90 *func_020a8d90(UnkStruct_020a8d90 *a)
{
    func_020a92b0(a, 1);
    a->vtable = ((int *) data_020e3e04);
    a->unk_2C = 0;
    a->unk_30 = 0;
    a->unk_34 = 0;
    a->unk_38 = 0;
    return a;
}

void *func_020a8d78(void *arg)
{
    *(void **) arg = ((unsigned char *) data_020e3e04);
    func_020a9260(arg);
    return arg;
}

void *func_020a8d58(UnkStruct_020a8d58 *self)
{
    self->vtable = (void *) data_020e3e04;
    func_020a9260(self);
    func_020edb3c(self);
    return self;
}

void func_020a8d20(UnkStruct_020a8d20 *self, int p1, int p2, int p3, unsigned char p4)
{
    self->unk_2C = p1;
    self->unk_30 = p2;
    self->unk_34 = p3;
    self->unk_38 = 0;
    if (p4) {
        func_020a9218(self);
    } else {
        func_020a9210(self);
    }
    func_020a9354(self, p2);
}

void func_020a8d10(UnkStruct_020a8d10 *s)
{
    s->unk_2C = 0;
    s->unk_30 = 0;
    s->unk_34 = 0;
    s->unk_38 = 0;
}

unsigned char func_020a8d08(UnkStruct_020a8d08 *p)
{
    return p->unk_38;
}

void func_020a8cd4(struct UnkStruct_020a8cd4 *p)
{
    if (p->unk_2C != 0) {
        if (p->unk_34 == 0) {
            p->unk_38 = (unsigned char) func_020a895c(p->unk_2C, p->unk_30, p->unk_04);
        } else if (p->unk_34 == 1) {
            p->unk_38 = (unsigned char) func_020a8910(p->unk_2C, p->unk_30, p->unk_04);
        }
    }
}
