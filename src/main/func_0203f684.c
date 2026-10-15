/* func_0203f684 @ 0x0203f684, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short func_0203c57c(void *);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int data_021c67a4;
extern int data_021c748c;

typedef struct {
    unsigned char pad_00[4];
    unsigned char flag;
} FlagStruct;
extern FlagStruct *data_021f6948;

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
