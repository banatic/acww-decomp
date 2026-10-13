/* func_ov109_0229ce78 @ 0x0229ce78, 0x30 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b8ac(char *p, int v);
extern void func_ov109_0229cd9c(char *p);
extern void func_0208e5cc(char *p);

void func_ov109_0229ce78(char *arg)
{
    if (func_ov002_0220b8ac(arg + 0x26cc, 1) != 0) {
        func_ov109_0229cd9c(arg);
        func_0208e5cc(arg + 0x2274);
    }
}
