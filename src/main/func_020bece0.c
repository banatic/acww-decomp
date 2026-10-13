/* func_020bece0 @ 0x020bece0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern void func_020becbc(int *ptr, int value, signed char *data);
extern signed char data_020d2d8c[];

void func_020bece0(int *ptr)
{
    *ptr = func_020644cc(5);
    func_020becbc(ptr, data_020d2d8c[0x1d], data_020d2d8c);
}
