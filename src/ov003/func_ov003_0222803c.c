/* func_ov003_0222803c @ 0x0222803c, 0x3e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int FX_MulFunc(int a, int b);
void func_02034270(void *buf, void *p, int a, int b);
void func_0203423c(void *buf);

void func_ov003_0222803c(int *out, int a)
{
    int buf[17];
    func_02034270(buf, out, 0, 0);
    out[0] = out[0] + FX_MulFunc(a, buf[9]);
    out[2] = out[2] + FX_MulFunc(a, buf[11]);
    func_0203423c(buf);
}
