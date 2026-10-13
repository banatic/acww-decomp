/* func_ov103_0229c720 @ 0x0229c720, 0x54 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, unsigned int);
extern void func_ov002_0220a08c(void *, int, int, int);
extern void func_ov002_02208098(void *, int);

void func_ov103_0229c720(unsigned char *p)
{
    int a;
    unsigned char flag;
    int b;

    a = func_ov002_02208ae4(p + 0x22d8);
    flag = p[0x2da9];
    b = func_ov002_02208ad8(p + 0x22d8, flag);
    func_ov002_0220a08c(p + 0x2274, a, b, 2);
    p[0x2da7] = p[0x8d];
    func_ov002_02208098(p, 11);
}
