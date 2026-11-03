/* talk_spinner_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208fdc0 @ 0x0208fdc0, 0x8 bytes, Thumb
 * func_0208fdb8 @ 0x0208fdb8, 0x6 bytes, Thumb
 * func_0208fd88 @ 0x0208fd88, 0x30 bytes, Thumb
 * func_0208fd68 @ 0x0208fd68, 0x20 bytes, Thumb
 * func_0208fd44 @ 0x0208fd44, 0x24 bytes, Thumb
 * func_0208fc7c @ 0x0208fc7c, 0xc8 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x13];
    unsigned char unk_13;
    unsigned char pad_14[8];
    int unk_1C;
} UnkStruct_0208fdc0;

typedef struct {
    unsigned char pad_00[19];
    unsigned char unk_13;
} UnkStruct_0208fdb8;

struct UnkStruct_0208fd88 {
    void *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    short unk_10;
    char unk_12;
    char unk_13;
    int unk_14;
    int unk_18;
    int unk_1C;
    char unk_20;
};

struct UnkStruct_0208fd68 {
    unsigned int unk_00;
};

struct UnkStruct_0208fd44 {
    unsigned int unk_00;
};

struct GObj {
    int unk_00;
};

struct UnkStruct_0208fc7c {
    struct GObj *unk_00;
    unsigned char pad_04[0x10 - 4];
    int *unk_10;
};

struct UnkStruct_0208fc7c_2 {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned short unk_10;
    unsigned char unk_12;
    unsigned char pad_13[1];
    int unk_14;
    int unk_18;
};

extern void func_0208af30(void *);
extern void func_0208fb24(struct UnkStruct_0208fd68 *p);
extern void func_0208af00(struct UnkStruct_0208fd68 *p);
extern unsigned char data_020e23e4[];
extern void func_020edb3c(struct UnkStruct_0208fd44 *p);
extern struct UnkStruct_0208fc7c data_020d71cc;
extern int func_0208aef0(void *);
extern int func_0208aeec(void *);
extern void func_02088df8(int a0, int a1, int a2, int a3, int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7);

void func_0208fdc0(UnkStruct_0208fdc0 *p, int a)
{
    p->unk_13 = 1;
    p->unk_1C = a;
}

void func_0208fdb8(UnkStruct_0208fdb8 *p)
{
    p->unk_13 = 0;
}

struct UnkStruct_0208fd88 *func_0208fd88(struct UnkStruct_0208fd88 *arg)
{
    func_0208af30(arg);
    arg->unk_00 = ((int *) data_020e23e4);
    arg->unk_0C = 0;
    arg->unk_10 = 0;
    arg->unk_12 = 0;
    arg->unk_13 = 0;
    arg->unk_14 = 0;
    arg->unk_18 = 0;
    arg->unk_1C = 0;
    arg->unk_20 = 0;
    return arg;
}

struct UnkStruct_0208fd68 *func_0208fd68(struct UnkStruct_0208fd68 *p)
{
    p->unk_00 = (unsigned int) data_020e23e4;
    func_0208fb24(p);
    func_0208af00(p);
    return p;
}

struct UnkStruct_0208fd44 *func_0208fd44(struct UnkStruct_0208fd44 *self)
{
    self->unk_00 = (unsigned int) data_020e23e4;
    func_0208fb24((struct UnkStruct_0208fd68 *) self);
    func_0208af00((struct UnkStruct_0208fd68 *) self);
    func_020edb3c(self);
    return self;
}

void func_0208fc7c(struct UnkStruct_0208fc7c_2 *self)
{
    int r4, r6, r7, v20;

    if (self->unk_0C == 0) {
        return;
    }

    r4 = self->unk_14 + func_0208aef0(self);
    r6 = self->unk_18 + func_0208aeec(self);

    r7 = data_020d71cc.unk_00->unk_00;
    v20 = *data_020d71cc.unk_10;

    func_02088df8(0, r7, r4, r6, -1, -1, 0x1000, 0x1000, self->unk_10, -1, 0, 0);
    func_02088df8(0, v20, r4, r6, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);

    if (self->unk_12 != 0) {
        func_02088df8(0, r7, r4, r6, -1, -1, 0x1000, 0x1000, self->unk_10, 2, 0, 0);
        func_02088df8(0, v20, r4, r6, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
    }
}
