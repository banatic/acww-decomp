/* caution_window_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02038424 @ 0x02038424, 0x20 bytes, Thumb
 * func_020383c4 @ 0x020383c4, 0x60 bytes, Thumb
 * func_0203837c @ 0x0203837c, 0x48 bytes, Thumb
 * func_02038368 @ 0x02038368, 0x12 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xCA];
    unsigned char unk_CA;
    unsigned char pad_CB[5];
    unsigned int unk_D0;
    unsigned int unk_D4;
    unsigned int unk_D8;
    unsigned int unk_DC;
} Func02038424Struct;

struct UnkStruct_020383c4 {
    char pad_00[0xca];
    unsigned char ca;
    unsigned char cb;
    char pad_CC[0x0d0 - 0xcc];
    int d0;
    int d4;
    int d8;
    int dc;
};

typedef struct {
    unsigned char pad_00[0xca];
    unsigned char flag;
    unsigned char other;
    unsigned char pad_CC[4];
    void *p0;
    void *p1;
    void *p2;
    void *p3;
} UnkStruct_0203837c;

extern int func_02001b60(void);
extern int func_02001b28(void);
extern int func_02001bd0(void);
extern int func_02001b98(void);
extern void func_02001b54(int);
extern void func_02001b1c(int);
extern void func_02001bc4(int);
extern void func_02001b8c(int);
extern void func_020b0334(void);
extern void func_020046b4(void);

void func_02038424(Func02038424Struct *p)
{
    p->unk_CA = 0;
    p->unk_D0 = 0;
    p->unk_D4 = 0;
    p->unk_D8 = 0;
    p->unk_DC = 0;
}

void func_020383c4(struct UnkStruct_020383c4 *self)
{
    if (self->ca == 0) {
        self->ca = 1;
        self->d0 = func_02001b60();
        self->d4 = func_02001b28();
        self->d8 = func_02001bd0();
        self->dc = func_02001b98();
        func_02001b54(1);
        func_02001b1c(0);
        func_02001bc4(0);
        func_02001b8c(0);
        self->cb = 1;
    }
}

void func_0203837c(UnkStruct_0203837c *self)
{
    if (self->flag) {
        self->flag = 0;
        func_02001b54((int) self->p0);
        func_02001b1c((int) self->p1);
        func_02001bc4((int) self->p2);
        func_02001b8c((int) self->p3);
        self->other = 1;
    }
}

void func_02038368(void *receiver)
{
    func_020b0334();
    func_020046b4();
}
