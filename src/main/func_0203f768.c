/* func_0203f768 @ 0x0203f768, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int pad_00;
    unsigned char unk_04;
} FlagStruct;
extern FlagStruct *data_021f6948;

typedef struct Arg {
    int unk_00;
    int unk_04;
    int unk_08;
} Arg;

extern int FX_MulFunc(int, int);
extern int FX_Sqrt(int, int);
extern int func_020e8ed8(int, int);

static __inline int is_flag(void)
{
    return data_021f6948->unk_04 == 1 ? 1 : 0;
}

int func_0203f768(Arg *arg)
{
    int cond = is_flag();
    if (cond != 0) {
        int a, b, c, sum, prev, d, e;
        a = FX_MulFunc(arg->unk_08, arg->unk_08);
        b = FX_MulFunc(arg->unk_04, arg->unk_04);
        c = FX_MulFunc(0x0001f576, 0x0001f576);
        sum = b + a;
        prev = FX_Sqrt(sum - c, sum);
        d = func_020e8ed8(arg->unk_08, arg->unk_04);
        e = func_020e8ed8(prev, 0x0001f576);
        return (short) (d - e);
    } else {
        return 0;
    }
}
