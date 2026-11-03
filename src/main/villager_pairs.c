/* villager_pairs: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207ba30 @ 0x0207ba30, 0xc bytes, Thumb
 * func_0207ba24 @ 0x0207ba24, 0xc bytes, Thumb
 * func_0207ba04 @ 0x0207ba04, 0x20 bytes, Thumb
 * func_0207b9e4 @ 0x0207b9e4, 0x20 bytes, Thumb
 */

typedef int (*FuncPtr)(int, int);

extern int func_0207ba3c(unsigned int, unsigned int, FuncPtr *, unsigned int);

int func_0207ba30(int r0, int r1)
{
    if (r1 > r0) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207ba24(int r0, int r1)
{
    if (r1 < r0) {
        return 1;
    }
    return 0;
}

int func_0207ba04(unsigned int a, unsigned int b)
{
    FuncPtr fn = func_0207ba30;
    return func_0207ba3c(a, b, &fn, 0x80000000);
}

int func_0207b9e4(int arg1, int arg2)
{
    int (*cb)() = &func_0207ba24;
    return func_0207ba3c(arg1, arg2, (FuncPtr *) (&cb), 0x7fffffff);
}
