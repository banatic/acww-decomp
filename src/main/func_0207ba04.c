/* func_0207ba04 @ 0x0207ba04, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef int (*FuncPtr)(int, int);
extern int func_0207ba30(int, int);
extern int func_0207ba3c(unsigned int, unsigned int, FuncPtr *, unsigned int);

int func_0207ba04(unsigned int a, unsigned int b)
{
    FuncPtr fn = func_0207ba30;
    return func_0207ba3c(a, b, &fn, 0x80000000);
}
