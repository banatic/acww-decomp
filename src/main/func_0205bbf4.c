/* func_0205bbf4 @ 0x0205bbf4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205a370(int *a, int *b, int *c, int *d, int e);
extern int func_0205bc60(unsigned char *out, int p2, int x, int y, int z, int w, int v);

void func_0205bbf4(unsigned char *out, int p2)
{
    int a, b, c, d;
    func_0205a370(&a, &b, &c, &d, p2);
    out[0] = func_0205bc60(out, p2, a, a + 1, c, d, 1);
    out[1] = func_0205bc60(out, p2, a, b, d - 1, d, 4);
    out[2] = func_0205bc60(out, p2, b - 1, b, c, d, 2);
}
