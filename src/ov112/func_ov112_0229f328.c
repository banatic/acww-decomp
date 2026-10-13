/* func_ov112_0229f328 @ 0x0229f328, 0x34 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a000(char *dst, int a, int b, int c, int d);
extern void func_ov002_02208098(char *p, int n);

void func_ov112_0229f328(char *s, int a, int b)
{
    unsigned char *p = (unsigned char *) s;
    func_ov002_0220a000(s + 0x4448, a, b, 3, 2);
    p[0xc1] = p[0x8d];
    func_ov002_02208098(s, 7);
}
