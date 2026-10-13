/* func_ov109_0229c8a4 @ 0x0229c8a4, 0x54 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229c85c(unsigned char *p);
extern int func_ov109_0229c84c(unsigned char *p);
extern void func_ov002_0220a0b4(unsigned char *a, int b, int c);
extern void func_ov002_0220a374(unsigned char *a, int b);
extern void func_ov109_0229c658(unsigned char *p);

void func_ov109_0229c8a4(unsigned char *p)
{
    int a, b;
    a = func_ov109_0229c85c(p);
    b = func_ov109_0229c84c(p);
    func_ov002_0220a0b4(p + 0x2274, a, b);
    if (p[0x29d3] == 0xf) {
        func_ov002_0220a374(p + 0x2274, 7);
    } else {
        func_ov002_0220a374(p + 0x2274, 1);
    }
    func_ov109_0229c658(p);
}
