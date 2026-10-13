/* func_02073cd0 @ 0x02073cd0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int);

void func_02073cd0(int *ptr, int x, int y)
{
    ptr += 3;
    ptr[func_02077b58(x)] -= y;
}
