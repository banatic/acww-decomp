/* func_ov003_02215e38 @ 0x02215e38, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02215ef0(void *src, int *out0, int *out1);
extern void func_ov003_02215f00(void *self, const int *data, int count, int param);

void func_ov003_02215e38(void *self, int param)
{
    int t0, t1, v;
    struct {
        int a[3];
        int b[3];
    } loc;

    func_ov003_02215ef0((char *) self + 0x8f0, &t0, &t1);
    v = *(int *) ((char *) self + 0x60);

    loc.a[0] = t0;
    loc.a[1] = v;
    loc.a[2] = t1;
    loc.b[0] = t0;
    loc.b[1] = v;
    loc.b[2] = t1;

    func_ov003_02215f00(self, loc.b, 6, param);
}
