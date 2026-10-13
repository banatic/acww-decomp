/* func_ov121_0229a1b0 @ 0x0229a1b0, 0x34 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov121_0229a3a8(void *p);
extern int func_ov121_0229a37c(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int a);

void func_ov121_0229a1b0(void *p)
{
    int a;
    int b;

    a = func_ov121_0229a3a8(p);
    b = func_ov121_0229a37c(p);
    func_ov002_0220a0b4((char *) p + 0x3a8, a, b);
    func_ov002_0220a374((char *) p + 0x3a8, 1);
}
