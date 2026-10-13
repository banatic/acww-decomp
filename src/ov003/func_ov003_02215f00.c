/* func_ov003_02215f00 @ 0x02215f00, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *, const int *, int, int);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov003_02215f4c(int *, const int *);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

int func_ov003_02215f00(void *obj, const int *src, int a, int b)
{
    char ctx[12];
    int out[4];
    int tmp[3];
    int ret;

    func_0200e92c(ctx, src, a, b);
    func_0200e90c(ctx, 0x4d, a, b);
    tmp[0] = src[0];
    tmp[1] = src[1];
    tmp[2] = src[2];
    func_ov003_02215f4c(out, tmp);
    ret = func_0200e894(obj, ctx);
    func_0200e91c(ctx);
    return ret;
}
