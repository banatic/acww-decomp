/* func_ov122_0229ffac @ 0x0229ffac, 0x54 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207fc0(char *p);
extern void func_ov122_0229f2f4(char *p);
extern int func_ov002_0220a768(char *p, int n);
extern int func_ov002_0220a72c(char *p, int n);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov002_02208098(char *p, int n);

void func_ov122_0229ffac(char *p)
{
    int a, b;
    func_ov002_02207fc0(p);
    func_ov122_0229f2f4(p);
    a = func_ov002_0220a768(p + 0x4698, 4);
    b = func_ov002_0220a72c(p + 0x4698, 4);
    func_ov002_0220a0b4(p + 0x4058, a, b);
    p[0xb6] = 1;
    func_ov002_02208098(p, 0x13);
}
