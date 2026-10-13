/* func_020b7d3c @ 0x020b7d3c, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b7ebc(int a, int b, int c, int d, int e, int f);
extern void func_020b7d6c(int a, int b);

void func_020b7d3c(int a, int b, int c, int d, int e, int f, unsigned char g)
{
    int local_f = f;
    int local_g = g;
    func_020b7ebc(b, c, d, e, local_f, local_g);
    func_020b7d6c(a, b);
}
