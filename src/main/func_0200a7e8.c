/* func_0200a7e8 @ 0x0200a7e8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(char *ptr, int size);
extern void func_0200a764(char *ptr);

void func_0200a7e8(char *arg)
{
    if (func_02056f28(arg + 0x2d0, 6)) {
        func_0200a764(arg);
    }
}
