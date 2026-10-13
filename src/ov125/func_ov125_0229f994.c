/* func_ov125_0229f994 @ 0x0229f994, 0x34 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov125_0229fb34(void *p);
extern int func_ov125_0229fb1c(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int a);

void func_ov125_0229f994(void *p)
{
    int a = func_ov125_0229fb34(p);
    int b = func_ov125_0229fb1c(p);
    func_ov002_0220a0b4((char *) p + 0x644, a, b);
    func_ov002_0220a374((char *) p + 0x644, 1);
}
