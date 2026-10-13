/* func_ov100_0229ca9c @ 0x0229ca9c, 0x34 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229cc70(void *p);
extern int func_ov100_0229cc60(void *p);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int a);

void func_ov100_0229ca9c(int *p)
{
    int a = func_ov100_0229cc70(p);
    int b = func_ov100_0229cc60(p);
    func_ov002_0220a0b4(&p[0x89D], a, b);
    func_ov002_0220a374(&p[0x89D], 1);
}
