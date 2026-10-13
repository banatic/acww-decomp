/* func_ov105_0229dd68 @ 0x0229dd68, 0x6c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a700(char *p);
extern int func_0208e4bc(char *p);
extern int func_ov002_0220a6e0(char *p);
extern int func_ov002_0220a768(char *p, int idx);
extern int func_ov002_0220a72c(char *p, int idx);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov105_0229cfc0(char *p);
extern void func_ov002_022080a0(char *p, int flag);

void func_ov105_0229dd68(char *arg)
{
    if (func_ov002_0220a700(arg + 0x5fb8) != 0) {
        if (func_0208e4bc(arg + 0x24a4) != 0) {
            int a = func_ov002_0220a6e0(arg + 0x5fb8);
            int b = func_ov002_0220a768(arg + 0x5fb8, -1);
            int c = func_ov002_0220a72c(arg + 0x5fb8, -1);
            func_ov002_0220a0b4(arg + 0x24a4, a + b, a + c);
        }
    } else {
        func_ov105_0229cfc0(arg);
        func_ov002_022080a0(arg, 1);
    }
}
