/* func_ov100_0229ccb8 @ 0x0229ccb8, 0x58 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229cc70(unsigned char *p);
extern int func_ov100_0229cc60(unsigned char *p);
extern int func_ov100_0229d60c(unsigned char *p, unsigned char b);
extern void func_ov100_0229ca7c(unsigned char *p);
extern void func_ov002_0220a0b4(unsigned char *p, int a, int b);
extern void func_ov002_0220a374(unsigned char *p, int v);

void func_ov100_0229ccb8(unsigned char *p)
{
    int v4;
    int v2;
    unsigned char b;

    v4 = func_ov100_0229cc70(p);
    v2 = func_ov100_0229cc60(p);
    func_ov002_0220a0b4(p + 0x2274, v4, v2);
    b = *(unsigned char *) (p + 0x2921);
    if (func_ov100_0229d60c(p, b) != 0) {
        func_ov002_0220a374(p + 0x2274, 7);
    } else {
        func_ov002_0220a374(p + 0x2274, 1);
    }
    func_ov100_0229ca7c(p);
}
