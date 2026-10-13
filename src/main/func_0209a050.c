/* func_0209a050 @ 0x0209a050, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void *arg);
extern int func_02098f70(void *arg);
extern int func_02099734(int a, int b);
extern int func_02098f0c(int a, void *b, void *c, int d);

void func_0209a050(void *arg)
{
    int a;
    unsigned short b;

    a = func_020984e8(arg);
    if (func_02098f70(arg)) {
        b = 0xfff1;
        func_02098f0c(func_02099734(a, b), &b, arg, 0);
    }
}
