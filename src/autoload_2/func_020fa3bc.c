/* func_020fa3bc @ 0x020fa3bc, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020fa3e4(int, int (*)(unsigned int, int));
extern int func_020fab6c(int a, int b);

int func_020fa3bc(int arg)
{
    return func_020fa3e4(arg, (int (*)(unsigned int, int)) func_020fab6c);
}
