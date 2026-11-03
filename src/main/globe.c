/* globe: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203f760 @ 0x0203f760, 0x8 bytes, Thumb
 * func_0203f758 @ 0x0203f758, 0x8 bytes, Thumb
 * func_0203f728 @ 0x0203f728, 0x30 bytes, Thumb
 * func_0203f724 @ 0x0203f724, 0x2 bytes, Thumb
 * func_0203f684 @ 0x0203f684, 0xa0 bytes, Thumb
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned short unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
} UnkStruct_0203f728;

typedef struct {
    unsigned char pad_00[4];
    unsigned char flag;
} FlagStruct;

struct In {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

struct UnkStruct_0203f684 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    short d;
    unsigned int e;
};

extern int FX_Div(int a, int b);
extern short func_0203c57c(void *);
extern int FX_MulFunc(int a, int b);
extern int data_021c67a4;
extern int data_021c748c;
extern FlagStruct *data_021f6948;

int func_0203f760(void)
{
    return 10649;
}

int func_0203f758(void)
{
    return 128374;
}

UnkStruct_0203f728 *func_0203f728(UnkStruct_0203f728 *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
    p->unk_0C = 0;
    p->unk_14 = FX_Div(0x1000, 0xA000);
    p->unk_10 = 0xE000;
    return p;
}

void func_0203f724(void *object) {}

void func_0203f684(struct UnkStruct_0203f684 *out, const struct In *in)
{
    void *tested_value0;
    unsigned int flag;
    out->a = in->a;
    out->b = in->b;
    out->c = in->c;

    if ((tested_value0 = (void *) (data_021c67a4)) != 0) {
        int v = func_0203c57c(tested_value0);
        if (v > 0x27f7) {
            v = 0x27f7;
        } else if (v < 0x21fd) {
            v = 0x21fd;
        }
        out->e = FX_MulFunc(0xffffd400, FX_Div((v - 0x27f7) << 12, 0xffa06000)) + 0xe000;
    }

    if (data_021f6948->flag == 1) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag > 0) {
        out->d = (short) ((FX_Div(out->c, data_021c748c) * 0x2999) >> 12);
    } else {
        out->d = 0;
    }
}
