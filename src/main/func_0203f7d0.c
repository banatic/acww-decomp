/* func_0203f7d0 @ 0x0203f7d0, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[4];
    unsigned char flag;
} FlagStruct;
extern FlagStruct *data_021f6948;
extern int func_020e8ed8(unsigned int a, unsigned int b);
extern int FX_MulFunc(int a, int b);
extern int FX_Sqrt(int a);
extern int func_0203f984(int a);
struct In {
    unsigned int a, b, c;
};
struct UnkStruct_0203f7d0 {
    unsigned int a, b, c;
};
int func_0203f7d0(struct UnkStruct_0203f7d0 *out, const struct In *in)
{
    unsigned int flag;
    int t;
    int s;
    int u;
    if (data_021f6948->flag == 1) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag > 0) {
        t = func_020e8ed8(in->c, in->b);
        out->a = in->a;
        s = FX_MulFunc(in->c, in->c);
        u = FX_MulFunc(in->b, in->b);
        out->b = FX_Sqrt(u + s) - 0x1f576;
        out->c = func_0203f984(t);
        return t;
    }
    out->a = in->a;
    out->b = in->b;
    out->c = in->c;
    return 0;
}
