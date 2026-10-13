/* func_020c14bc @ 0x020c14bc, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct In3 {
    int a;
    int b;
    int c;
};
struct Mid {
    int a;
    int b;
    int c;
};
struct Global48 {
    int data[12];
};

extern struct Global48 data_021fbe48;
extern int data_021c67a4;
extern void *func_0203ab20(void *p0, void *p1);
extern void func_0203f844(struct Mid *a, struct In3 *b);
extern void MTX_MultVec43(struct Mid *a, struct Global48 *b, int *c);
extern int func_0203c53c(int a);
extern int FX_Div(int a, int b);
extern void func_020eabc8(int *a, int b);

void func_020c14bc(int *out, struct In3 *in_arg)
{
    struct Global48 *src;
    struct In3 in;
    struct Mid mid;
    int out2[3];
    int r, res1, res2;

    src = (struct Global48 *) func_0203ab20(out, in_arg);
    data_021fbe48 = *src;

    in.a = in_arg->a;
    in.b = in_arg->b;
    in.c = in_arg->c;

    func_0203f844(&mid, &in);
    MTX_MultVec43(&mid, &data_021fbe48, out2);

    r = func_0203c53c(data_021c67a4);
    res1 = -FX_Div(0x00060000, r);
    res2 = FX_Div(res1, out2[2]);
    func_020eabc8(out2, res2);

    out[0] = out2[0] + 0x00080000;
}
