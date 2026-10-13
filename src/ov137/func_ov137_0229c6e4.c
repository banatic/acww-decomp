/* func_ov137_0229c6e4 @ 0x0229c6e4, 0x50 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov137_0229c574(void *arg, int n);
extern void func_ov002_0220a2b4(void *p);
extern void func_ov002_0220a314(void *p);
extern int func_ov137_0229c794(void *arg);
extern int func_ov137_0229c750(void *arg);
extern int func_ov137_0229c684(void *arg, int a, int b);

int func_ov137_0229c6e4(void *arg)
{
    if (!(func_ov137_0229c574(arg, 2) == 0 && ((unsigned char *) arg)[0x2b77] == 2)) {
        func_ov002_0220a2b4((char *) arg + 0x94);
    } else {
        func_ov002_0220a314((char *) arg + 0x94);
    }
    {
        int a = func_ov137_0229c794(arg);
        int b = func_ov137_0229c750(arg);
        return func_ov137_0229c684(arg, a, b);
    }
}
