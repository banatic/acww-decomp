/* func_ov096_0229dd94 @ 0x0229dd94, 0x44 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229de0c(unsigned char *p);
extern int func_ov096_0229ddfc(unsigned char *p);
extern void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
extern void func_ov002_02208098(void *p, int n);

void func_ov096_0229dd94(unsigned char *p)
{
    int v1 = func_ov096_0229de0c(p);
    int v2 = func_ov096_0229ddfc(p);
    func_ov002_0220a05c(p + 0x2500, v1, v2, 3, 1);
    p[0xba] = p[0x8d];
    func_ov002_02208098(p, 0xf);
}
