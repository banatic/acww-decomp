/* func_0207b9e4 @ 0x0207b9e4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207ba24();
extern int func_0207ba3c(int, int, int (**)(), int);

int func_0207b9e4(int arg1, int arg2)
{
    int (*cb)() = &func_0207ba24;
    return func_0207ba3c(arg1, arg2, &cb, 0x7fffffff);
}
