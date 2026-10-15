/* func_020f545c @ 0x020f545c, 0x28 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_020f5484(void *object, unsigned short value);
extern int func_020f5748(int, int, int, int);

int func_020f545c(int arg1, unsigned short value)
{
    return func_020f5748(arg1, func_020f5484((void *) arg1, value), 0x7f, 0);
}
