/* donation_list_4: 7 functions, module ov145
 * mwccarm 1.2/base -O4,s
 * func_ov145_0229a034 @ 0x0229a034, 0x24 bytes, Thumb
 * func_ov145_0229a010 @ 0x0229a010, 0x24 bytes, Thumb
 * func_ov145_02299fec @ 0x02299fec, 0x24 bytes, Thumb
 * func_ov145_02299fc8 @ 0x02299fc8, 0x24 bytes, Thumb
 * func_ov145_02299f7c @ 0x02299f7c, 0x4c bytes, Thumb
 * func_ov145_02299f30 @ 0x02299f30, 0x4c bytes, Thumb
 * func_ov145_02299eec @ 0x02299eec, 0x44 bytes, Thumb
 */

struct UnkStruct_02299fc8 {
    unsigned char pad_00[0xbc];
    unsigned short unk_BC;
};

struct UnkStruct_02299f7c {
    char _dummy;
};

typedef struct UnkStruct_02299f7c UnkStruct_02299f7c;

typedef struct SomeObj {
    unsigned char pad_00[0xc2];
    unsigned char flag;
    unsigned char pad_C3[5];
    UnkStruct_02299f7c sub;
} SomeObj;

typedef struct {
    unsigned char pad_00[0xc2];
    unsigned char mode;
} Func_ov145_02299eec_Struct;

extern int func_ov145_0229a058(char *a, char *b, int c, int d);
extern int func_ov145_0229a06c(void *a, void *b, int c, int d);
extern void func_ov145_02299e44(void *obj);
extern void func_ov002_0220a0b4(void *sub, int a, int b);
extern void func_ov002_0220a374(void *sub, int v);
extern int func_ov002_0220a768(char *ptr, int param);
extern int func_ov002_0220a4f8(char *ptr);
extern int func_ov002_0220a72c(void *p, int a);
extern int func_ov002_0220a4d4(void *p);

int func_ov145_02299f30(char *arg);
int func_ov145_02299eec(Func_ov145_02299eec_Struct *self);

void func_ov145_0229a034(char *p)
{
    *(unsigned short *) (p + 0xbe) = func_ov145_0229a058(p, p + 0xb44, 0x450c, 0x34);
}

void func_ov145_0229a010(unsigned char *base)
{
    *(unsigned short *) (base + 0xb8) = (unsigned short) func_ov145_0229a058((char *) base, (char *) (base + 0x0c8c), 0x3894, 0x14);
}

void func_ov145_02299fec(void *self)
{
    unsigned short *p;
    p = (unsigned short *) ((char *) self + 0xba);
    *p = (unsigned short) func_ov145_0229a06c(self, (char *) self + 0xbac, 0x12e8, 0x38);
}

void func_ov145_02299fc8(struct UnkStruct_02299fc8 *self)
{
    self->unk_BC = (unsigned short) func_ov145_0229a06c(self, (char *) self + 0x0c1c, 0x12b0, 0x38);
}

void func_ov145_02299f7c(SomeObj *obj)
{
    int a, b;
    a = func_ov145_02299f30((char *) obj);
    b = func_ov145_02299eec((Func_ov145_02299eec_Struct *) obj);
    func_ov002_0220a0b4(&obj->sub, a, b);
    if (obj->flag == 4) {
        func_ov002_0220a374(&obj->sub, 7);
    } else {
        func_ov002_0220a374(&obj->sub, 1);
    }
    func_ov145_02299e44(obj);
}

int func_ov145_02299f30(char *arg)
{
    unsigned char b;

    b = *(unsigned char *) (arg + 0xc2);
    if (b <= 3) {
        return -36 * b + 0x94;
    }
    switch (b) {
        case 4:
            return func_ov002_0220a768(arg + 0x174, 6);
        case 5:
            return func_ov002_0220a4f8(arg + 0x12c);
        default:
            return 0x80;
    }
}

int func_ov145_02299eec(Func_ov145_02299eec_Struct *self)
{
    if (self->mode <= 3) {
        return 0xAD;
    }
    switch (self->mode) {
        case 4:
            return func_ov002_0220a72c((char *) self + 0x174, 6);
        case 5:
            return func_ov002_0220a4d4((char *) self + 0x12c);
        default:
            return 0x60;
    }
}
