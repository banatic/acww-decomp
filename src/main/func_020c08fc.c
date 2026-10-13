/* func_020c08fc @ 0x020c08fc, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x34];
    int unk_34;
    int unk_38;
    char pad_3C[0x10];
    int unk_4C;
    char pad_50[0x14];
    int unk_64;
} UnkStruct_020c08fc;

typedef struct {
    char pad_00[0x4c];
    int unk_4C;
    int unk_50;
} Res;

extern int func_020644cc(int);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern short FX_SinCosTable_[];
extern Res *func_020bdc50(void *a, int b, int c, int *d, int e);
extern char data_021f8b48;

void func_020c08fc(UnkStruct_020c08fc *p)
{
    int t;
    int n;
    int d0;
    int d;
    int t0;
    int idx;
    int vec[3];
    Res *res;

    t = p->unk_64;
    if (t <= 0) {
        return;
    }
    if (t == 1) {
        p->unk_64 = func_020644cc(2) + 1;
        n = func_020644cc(2) + 2;
        d0 = p->unk_4C;
        d = FX_Div(func_020644cc(0x10) << 12, d0);
        idx = ((unsigned short) (short) func_020644cc(0x10000) >> 4) << 1;
        t0 = p->unk_38 + FX_MulFunc(d, FX_SinCosTable_[idx]);
        vec[0] = p->unk_34 + FX_MulFunc(d, FX_SinCosTable_[idx + 1]);
        vec[1] = t0;
        vec[2] = 0;
        res = func_020bdc50(&data_021f8b48, 2, 0x3c, vec, n & 0xf);
        if (res != 0) {
            res->unk_4C = d0;
            res->unk_50 = d0;
        }
    } else {
        p->unk_64 = t - 1;
    }
}
